#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood

  int neighborCount = 0;
  Vector2f velocitySum;

  for (int i = 0; i < neighborhood.size(); i++)
  {
    Vector2f difference = neighborhood[i]->getPosition() - boid->getPosition();
    // if its within the alignment radius
    if (difference.getMagnitude() <= boid->getDetectionRadius())
    {
      // add its velocity to a sum
      velocitySum += neighborhood[i]->getVelocity();
      neighborCount++;
    }

  }
  // if there are no neighbors are found within the radius return a zero vector
  if (neighborCount == 0)
  {
    return Vector2f::zero();
  }
  // otherwise calculate the average velocity and return that veloctiy scaled by the base weight multiplier
  else
  {
    averageVelocity = velocitySum / neighborCount;
    Vector2f velcoityScaled = averageVelocity * getBaseWeightMultiplier();
    return Vector2f::normalized(velcoityScaled);
  }
}