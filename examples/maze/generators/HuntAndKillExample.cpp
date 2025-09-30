#include "HuntAndKillExample.h"
#include "../World.h"
#include "Random.h"
#include <climits>
bool HuntAndKillExample::Step(World* w) {

  //  if the first cell hasnt been visted
  if (!visited[currentCell.x][currentCell.y]) {
    // then set it to visted
    visited[currentCell.x][currentCell.y] = true;
    // color it green to indicate that aswell
    w->SetNodeColor(currentCell, Color::Green);
  }

  // if were in the hunt phase
  if (huntPhase) {
    // create a neighbors vector with the world and a huntPos
    std::vector<Point2D> neighbors = getVisitedNeighbors(w, huntPos);

    if (!visited[huntPos.x][huntPos.y] && !neighbors.empty()) {

      Point2D chosenVisitedNeighbor = neighbors[Random::Range(0,neighbors.size() - 1)];
      // compare coordinates to decide which wall will be removed based on the direction
      if (huntPos.y < chosenVisitedNeighbor.y) {

        w->SetNorth(chosenVisitedNeighbor, false);
        w->SetSouth(huntPos, false);
      }

      else if (huntPos.x > chosenVisitedNeighbor.x) {
        w->SetEast(chosenVisitedNeighbor, false);
        w->SetWest(huntPos, false);
      }
      else if (huntPos.y > chosenVisitedNeighbor.y) {

        w->SetSouth(chosenVisitedNeighbor, false);
        w->SetNorth(huntPos, false);
      }
      else if (huntPos.x < chosenVisitedNeighbor.x) {

        w->SetWest(chosenVisitedNeighbor, false);
        w->SetEast(huntPos, false);
      }

      currentCell = huntPos;
      visited[huntPos.x][huntPos.y] = true;
      // when a huntable cell is found turn it to black
      w->SetNodeColor(huntPos, Color::Black);
      huntPos = {-w->GetSize()/2,-w->GetSize()/2};
      huntPhase = false;
    }

    else {
      if (huntPos.x < w->GetSize()/2) {
        ++huntPos.x;
      }
      else {
        huntPos.x = -w->GetSize()/2;
        ++huntPos.y;
        if (huntPos.y > w->GetSize()/2) {
          complete = true;
          return false;
        }
      }
    }
  }
  else {

    std::vector<Point2D> vistableNeighbors = getVisitables(w, currentCell);
    if (!vistableNeighbors.empty()) {

      size_t randomIndex = Random::Range(0,int(vistableNeighbors.size() - 1));

      Point2D chosenNeighbor = vistableNeighbors[randomIndex];
      // compare coordinates to decide which wall neighboring the current cell will be removed based on the direction
      if (chosenNeighbor.y < currentCell.y) {

        w->SetNorth(currentCell, false);
        w->SetSouth(chosenNeighbor, false);
      }

      else if (chosenNeighbor.x > currentCell.x) {

        w->SetEast(currentCell, false);
        w->SetWest(chosenNeighbor, false);
      }
      else if (chosenNeighbor.y > currentCell.y) {

        w->SetSouth(currentCell, false);
        w->SetNorth(chosenNeighbor, false);
      }
      else if (chosenNeighbor.x < currentCell.x) {

        w->SetWest(currentCell, false);
        w->SetEast(chosenNeighbor, false);
      }
      visited[chosenNeighbor.x][chosenNeighbor.y] = true;
      currentCell = chosenNeighbor;
      w->SetNodeColor(chosenNeighbor, Color::Green);
    }
    else {
      huntPhase = true;
    }
  }
  return true;
}
void HuntAndKillExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  currentCell = {0,0};

  huntPhase = false;
  complete = false;
  huntPos = {-sideOver2, -sideOver2};

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}
Point2D HuntAndKillExample::randomStartPoint(World* world) {
  // Todo: improve this if you want
  auto sideOver2 = world->GetSize() / 2;

  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> HuntAndKillExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: code this

  // north
  if (p.y > -sideOver2) {
    Point2D upNeighbor = Point2D(p.x, p.y -1 );
    if (!visited[upNeighbor.x][upNeighbor.y]) {
      visitables.push_back(upNeighbor);
    }
  }

  // east
  if (p.x < sideOver2) {
    Point2D rightNeighbor = Point2D(p.x + 1, p.y);
    if (!visited[rightNeighbor.x][rightNeighbor.y]) {
      visitables.push_back(rightNeighbor);
    }
  }

  // west
  if (p.x > -sideOver2) {
    Point2D leftNeighbor = Point2D(p.x - 1, p.y);
    if (!visited[leftNeighbor.x][leftNeighbor.y]) {
      visitables.push_back(leftNeighbor);
    }
  }

  // south
  if (p.y < sideOver2) {
    Point2D downNeighbor = Point2D(p.x, p.y + 1);
    if (!visited[downNeighbor.x][downNeighbor.y]) {
      visitables.push_back(downNeighbor);
    }
  }

  return visitables;
}
std::vector<Point2D> HuntAndKillExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> neighbors;

  // todo: code this
  for (auto offsets: deltas) {
    Point2D neighbor = Point2D(p.x + offsets.x, p.y + offsets.y);

    if (neighbor.x >= -sideOver2 && neighbor.x <= sideOver2 && neighbor.y >= -sideOver2 && neighbor.y <= sideOver2) {
      if (visited[neighbor.x][neighbor.y]) {
        neighbors.push_back(neighbor);
      }
    }
  }
  return neighbors;
}
