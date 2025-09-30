#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this

        std::vector<Point2D> neighbors;
        // if the maze is empty  and not complete then add the point 0,0 to the maze and if the maze is complete return false
        if (maze.empty()) {

          if (!complete) {
            maze.push(Point2D(0,0));
          }
          else {
            return false;
          }
        }

        if (!maze.empty()) {

            Point2D currentCell = maze.top();
            visited[currentCell.x][currentCell.y] = true;
            // make the current Pos green
            w->SetNodeColor(currentCell, Color::Green);

            std::vector<Point2D> vistableNeighbors = getVisitables(w, currentCell);

            if (!vistableNeighbors.empty()) {

                Point2D chosenNeighbor;
                // if we have vistable neighbors nitalise it witht the first viatable neighbor
                if (vistableNeighbors.size() == 1) {
                    chosenNeighbor = vistableNeighbors[0];
                }
                else  {
                  // if not choose the next neighbor randomly
                    size_t randomIndex = Random::Range(0,int(vistableNeighbors.size() - 1));
                    chosenNeighbor = vistableNeighbors[randomIndex];
                }
                // compare directions to decide which walls between the current cell and neighbor should be removed
                // up
                if (chosenNeighbor.y < currentCell.y) {

                  w->SetNorth(currentCell, false);
                  w->SetSouth(chosenNeighbor, false);
                }
                // right
                else if (chosenNeighbor.x > currentCell.x) {

                  w->SetEast(currentCell, false);
                  w->SetWest(chosenNeighbor, false);
                }
                // down
                else if (chosenNeighbor.y > currentCell.y) {

                  w->SetSouth(currentCell, false);
                  w->SetNorth(chosenNeighbor, false);

                }
                else if (chosenNeighbor.x < currentCell.x) {

                  w->SetWest(currentCell, false);
                  w->SetEast(chosenNeighbor, false);
                }

                maze.push(chosenNeighbor);
                // mark the visted path with light gray
                w->SetNodeColor(chosenNeighbor, Color::LightGray);
            }
            else {
                maze.pop();
                // mark backtracking with the color black
                w->SetNodeColor(currentCell, Color::Black);
            }

          if (maze.empty()) {
            complete = true;
            return false;
          }
        }
  return true;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();

  while (!maze.empty()) maze.pop();
  complete = false;

  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // find the visitable neighbors through comparing the given point to the sideover2 variable
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
