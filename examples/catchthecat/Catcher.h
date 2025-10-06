#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"

#include <queue>

struct Node {
  Point2D location;
  int g; // cost of the node
  int f; // the heuristic estimate

  bool operator>(const Node &other) const {
    return f > other.f;
  }
  bool operator==(const Node& node) const = default;
};

class Catcher : public Agent {
public:
  explicit Catcher() : Agent(){};
  Point2D Move(World*) override;
  std::vector<Point2D> pathAStar(World* w , Node start, Node goal);
};

#endif  // CATCHER_H
