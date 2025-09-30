#include "JohnConway.h"


// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  //lines
  for (size_t i = 0; i < world.SideSize(); i++) {
    // columns
    for (size_t j = 0; j < world.SideSize(); j++) {
      bool  cell = world.Get(Point2D(j, i));
      int neighbors = CountNeighbors(world, Point2D(j, i));

      // if we find a cell thats alive set its coordinate values in the new buffer and check whether it has 2 or three neighbor to stay alive
      if (cell) {
        world.SetNext(Point2D(j, i), (neighbors == 2 || neighbors == 3));
      }
      // if the cell is dead but has three neighbors it can be brought back to life
      else {
        world.SetNext(Point2D(j,i), (neighbors == 3));
      }

    }
  }
  world.SwapBuffers();
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  int neighbor_y;
  int neighbor_x;

  int counter = 0;

  //loop through the offsets
  for (int y_offset = -1; y_offset <= 1; y_offset++) {

    for (int x_offset = -1; x_offset <= 1; x_offset++) {

      // initialise the neighbors
      neighbor_y = (point.y + y_offset + world.SideSize()) % world.SideSize();

      neighbor_x = (point.x + x_offset + world.SideSize()) % world.SideSize();

      //skips the middle coordinate
      if(y_offset == 0 && x_offset == 0)
      { continue;}

      // if we do find a neighbor increment the counter
      if(world.Get(Point2D(neighbor_y, neighbor_x)))
      {
        counter++;

      }

    }
  }

  return counter;
}
