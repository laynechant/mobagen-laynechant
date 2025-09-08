#include "CohesionRule.h"

#include "../../../cmake-build-debug/_deps/glm-src/glm/gtc/constants.hpp"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

          // todo: add your code here to make a force towards the center of mass
          // hint: iterate over the neighborhood

          // find center of mass

        int neighborCount = 0;
        Vector2f positionSum;

      for (int i = 0; i < neighborhood.size(); i++) {
        
          // find the difference between the current boid and its neighbor
         Vector2f difference = boid->getPosition() - neighborhood[i]->getPosition();


          //  checks whether the differenence's magnitude is within the cohesion radius
        if (difference.getMagnitude() <= boid->getDetectionRadius())
          {

            // add the agents location into positon sum
            positionSum += neighborhood[i]->getPosition();

            neighborCount++;

          }
      }

  // if we find boids within the cohesion radius
  if (neighborCount > 0) {
    Vector2f centerOfMass = positionSum / neighborCount;
    // make a vector that points from the boids current position to the center of mass
    cohesionForce = centerOfMass - boid->getPosition();
    // normalise that vector
    Vector2f forceNormalized = cohesionForce.normalized();
    // return the normalised vector scaled by the base weight multiplier
    return forceNormalized * getBaseWeightMultiplier();

  }
  else
  {
    return Vector2f();
  }

}