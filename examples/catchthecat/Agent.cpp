#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"

#include <codecvt>
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flow field and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element don't exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we don't find a border, we have to return random points
  Point2D current = frontier.front();

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontier set
    // mark current as visited
    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontier set
    // do this up to find a visitable border and break the loop


    frontier.pop();
    visited[current] = true;

    const vector<Point2D> visitableNeighbors = getVisitableNeighbors(w, current);

    for (const Point2D neighbor : visitableNeighbors) {
      if (!visited[neighbor]) {
         if(isBorderPoint(w, neighbor)) {
            borderExit = current;
           break;
         }

        cameFrom.insert({neighbor, current});
        frontier.push(neighbor);
        frontierSet.insert(neighbor);
      }
    }
  }

  // if the border is not infinity, build the path from border to the cat using the came from map
  // if there isn't a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move

  if (borderExit != Point2D::INFINITE) {
    vector<Point2D> path;
    current = borderExit;

    while (current != w->getCat()) {
      path.push_back(current);
      current = cameFrom[current];
    }
    path.push_back(current);
    return path;
  }
  else
  {
    return {};
  }

}

// this function should return a vector of visitable neighbors
std::vector<Point2D> Agent::getVisitableNeighbors(World* w, const Point2D& current) {

  vector<Point2D> neighbors;

  vector<Point2D> offsets;
  offsets.emplace_back(1,0);
  offsets.emplace_back(1,-1);
  offsets.emplace_back(0,-1);
  offsets.emplace_back(-1,0);
  offsets.emplace_back(-1,1);
  offsets.emplace_back(0,1);

  for (auto offsetPoint : offsets) {
    const Point2D point = Point2D(current.x + offsetPoint.x, current.y + offsetPoint.y);

    if (w->isNeighbor(current,point)) {
      neighbors.push_back(point);
    }
  }
  return neighbors;
}

bool Agent::isBorderPoint(World* w, const Point2D& current) {

  vector<Point2D> offsets;
  offsets.emplace_back(1,0);
  offsets.emplace_back(1,-1);
  offsets.emplace_back(0,-1);
  offsets.emplace_back(-1,0);
  offsets.emplace_back(-1,1);
  offsets.emplace_back(0,1);


  for (auto offsetPoint : offsets) {
    const auto point = Point2D(current.x + offsetPoint.x, current.y + offsetPoint.y);

    if (!w->isValidPosition(point)) {
      return true;
    }
  }
  return false;
}
