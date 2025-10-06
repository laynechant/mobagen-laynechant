#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);

  static std::vector<Point2D> getVisitableNeighbors(World* w, const Point2D& current);

  static bool isBorderPoint(World* w, const Point2D& current);
};

#endif  // AGENT_H
