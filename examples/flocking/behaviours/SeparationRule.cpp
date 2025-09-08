#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  //    float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  //    if (!neighborhood.empty()) {
  //        Vector2f position = boid->transform.position;
  //        int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
  //    }


  Vector2f sumOfForces = Vector2f::zero();

  for(int i = 0; i < neighborhood.size(); i++)
  {
    // if i is not the current boid continue
    if (neighborhood[i] != boid)
    {
      // calculate the difference from the current boid to its neighbor
      Vector2f difference = boid->getPosition() - neighborhood[i]->getPosition();

      if (difference.getMagnitude() <= desiredMinimalDistance)
      {
        //For each neighbor, calculate a repulsion force inversely proportional to distance

        double distance = difference.getMagnitude();

        if (distance < 0.01)
        {
          distance = 0.01;
        }

        Vector2f unitVector = difference / distance;
        double repulsionMagnitude = getBaseWeightMultiplier() / distance;
        Vector2f repulsionForce = unitVector * repulsionMagnitude;

        sumOfForces += repulsionForce;

      }
    }
  }

  if (sumOfForces.getMagnitude() > desiredMinimalDistance)
  {
    Vector2f forcesNormalised = sumOfForces.normalized();
    Vector2f clampedForce = forcesNormalised * desiredMinimalDistance;
    return clampedForce;
  }
  else
    return sumOfForces;


}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
