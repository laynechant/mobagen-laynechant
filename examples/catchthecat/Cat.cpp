#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  auto currentPos = world->getCat();

  std::vector<Point2D> catsPath = generatePath(world);

  if (catsPath.size() >= 2 ) {

    auto index = catsPath.size() - 2;
    Point2D nextMove = catsPath[index];

    if (nextMove == previousPos) {
        std::vector<Point2D> neighbors = getVisitableNeighbors(world, currentPos);
      for (const auto& neighbor : neighbors) {
        if (neighbor != previousPos && !world->getContent(neighbor)) {
          nextMove = neighbor;
          break;
        }
      }
    }
    previousPos = currentPos;
    return nextMove;
}
  else {
    auto rand = Random::Range(0, 5);
    auto pos = world->getCat();
    switch (rand) {
      case 0:
        return World::NE(pos);
      case 1:
        return World::NW(pos);
      case 2:
        return World::E(pos);
      case 3:
        return World::W(pos);
      case 4:
        return World::SW(pos);
      case 5:
        return World::SE(pos);
      default:
        throw "random out of range";
    }
  }
}
