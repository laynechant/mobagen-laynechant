#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"
#include "unordered_set"
#include <queue>

struct Point {
  int x;
  int y;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

struct Point2DPrioritized {

  Point pos;
  int priority;

  bool operator>(const Point2DPrioritized &other) const {
  return priority < other.priority;
}
  bool operator==(const Point2DPrioritized& other) const {
  return pos.x == other.pos.x && pos.y == other.pos.y;
}
};

template<>
struct std::hash<Point2DPrioritized> {
  size_t operator()(const Point2DPrioritized& p) const {
    return std::hash<int>()(p.pos.x) ^ std::hash<int>()(p.pos.y) << 1;
  }
};

template<>
struct std::hash<Point> {
  size_t operator()(const Point& p) const {
    return std::hash<int>()(p.x) ^ std::hash<int>()(p.y) << 1;
  }
};

class Catcher : public Agent {
public:
  explicit Catcher() : Agent(){};
  Point2D Move(World*) override;
  std::vector<Point> pathAStar(World* w , Point start);
  int heuristic(World* world, Point p);
  std::vector <Point2D> borderPositions;
  bool isInitialized = false;
  int borderIndex;
};

#endif  // CATCHER_H
