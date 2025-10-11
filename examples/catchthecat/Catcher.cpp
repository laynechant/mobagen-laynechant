#include "Catcher.h"
#include "World.h"
#include <unordered_map>
#include <limits>

Point2D Catcher::Move(World* world) {

  std::vector<Point> path = pathAStar(world, Point(world->getCat().x, world->getCat().y));

  int sideSize = world->getWorldSideSize();

  if (path.size() >= 2) {
    // initializes the border positions vector with valid border positions
    Point2D currentPos = {0,0};
    if (!isInitialized)
    {
      for (int x = -sideSize; x <= sideSize; x++ ) {
        for (int y = -sideSize; y <= sideSize; y++ ) {
          Point2D pos = {x,y};
          if (world->isValidPosition(pos) && isBorderPoint(world, pos)) {
            borderPositions.emplace_back(x, y);

          }
        }
      }
      isInitialized = true;
    }

    // focus on cutting off the cats closet border
    if (path.size() >= 1) {

      Point borderPath = path[0];
      Point2D borderCell = {borderPath.x, borderPath.y};

      if(!world->getContent(borderCell) && borderCell != world->getCat()) {
        return borderCell;
      }
    }
    // loops through the vector to block 40 % of the border positions
    while (borderIndex < borderPositions.size() * 0.4) {
      auto currentBorderCell = borderPositions[borderIndex];
      // if the positions are valid (not blocked and not the cats pos) block them
      if (!world->getContent(currentBorderCell) && currentBorderCell != world->getCat()) {
        borderIndex++;
        return currentBorderCell;
      }
      borderIndex++;

    }
      // third blocking stragety is to find cells along the cats escape path and work from cat towards the border
      for(int i = path.size() - 3; i >= 0; --i) {
       Point target = path.at(i);
       if(!world->getContent(Point2D(target.x, target.y)) && Point2D(target.x, target.y) != world->getCat()) {
         return {target.x, target.y};
       }
     }
        // if that fails just fall back to randomly selected cells to block
        auto side = world->getWorldSideSize() / 2;
        for (;;) {

          Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
          auto cat = world->getCat();
          if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
        }
      }
}
std::vector<Point> Catcher::pathAStar(World* w, Point start) {
  std::priority_queue<Point2DPrioritized, std::vector<Point2DPrioritized>, std::greater<Point2DPrioritized>>  frontier;
  std::unordered_map<Point, Point> cameFrom;
  std::unordered_map<Point, int> costSoFar;
  std::unordered_map<Point, bool> visited;

  Point2DPrioritized p;
  p.pos = start;
  p.priority = 0;

  frontier.push(p);

  costSoFar[start] = 0;

  Point2DPrioritized current;

  while (!frontier.empty()) {
    current = frontier.top();
    frontier.pop();

    if (visited[current.pos]) {
      continue;
    }
    visited[current.pos] = true;

    if (isBorderPoint(w, Point2D(current.pos.x, current.pos.y))) {
      break;
    }

    std::vector<Point2D> visitableNeighbors = getVisitableNeighbors(w, Point2D(current.pos.x, current.pos.y));

    Point2DPrioritized neighbor;

    // loops through all visitable neighbors to find the ones that haven't been visited or have low cost
    for (auto next : visitableNeighbors) {
      int newCost = costSoFar[current.pos] + 1;
        if ( !visited[{next.x, next.y}] && (!cameFrom.contains({next.x, next.y}) || newCost < costSoFar[{next.x, next.y}])) {
          costSoFar[{next.x, next.y}] = newCost;

          neighbor.pos = {next.x, next.y};
          neighbor.priority = newCost + heuristic(w, neighbor.pos);

          frontier.push(neighbor);
          cameFrom[{next.x, next.y}] = current.pos;
        }
    }
  }

  std::vector<Point> path;
  Point currentPath = current.pos;

  while (currentPath != start) {

    path.push_back(currentPath);
    currentPath = cameFrom[currentPath];
  }
  path.push_back(currentPath);

  return path;
}

// finds the distance from the given position to the border
int Catcher::heuristic(World* world, Point p) {
  auto side = world->getWorldSideSize() / 2;

  return (side) - std::max(abs(p.x), abs(p.y));
}


