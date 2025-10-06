#include "Catcher.h"
#include "World.h"
#include <unordered_map>


Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}
std::vector<Point2D> Catcher::pathAStar(World* w, Node start, Node goal) {
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>>  frontier;
  std::unordered_map<Point2D, Point2D> cameFrom;
  std::unordered_map<Point2D, int> costSoFar;
  std::unordered_map<Point2D, bool> const visited;




  frontier.push(start);

  cameFrom[start.location] = {0,0};
  costSoFar[start.location] = 0;

  while (!frontier.empty()) {
    const Node current = frontier.top();

    if (current == goal) {
      break;
    }

    const std::vector<Point2D> visitableNeighbors = getVisitableNeighbors(w, current.location);

    for (auto next : visitableNeighbors) {
      int newCost = costSoFar[current.f];
        if (!cameFrom.contains(next)) {
          frontier.push(Node(next));
          cameFrom[next] = current.location;
        }
    }
  }
}
