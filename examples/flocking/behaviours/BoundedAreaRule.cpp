#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Return a force proportional to the proximity of the boids with the bounds, and opposed to it
  Vector2f force = Vector2f::zero();  // zero

  // todo: add here your code code here do make the boid follow the bounded box rule
  // hint: use this->world->engine->window->size() and desiredDistance
  // get the window size
  auto windowSize = this->world->engine->window->size();

  float leftBoundary =   boid->getPosition().x - 0;
  float topBoundary =   windowSize.y - boid->getPosition().y;

  float rightBoundary =   windowSize.x - boid->getPosition().x;
  float bottomBoundary =   boid->getPosition().y - 0;

  Vector2f repulsionDirection = Vector2f::zero();

  // if the boid approaches a specific side of the boundary calculate an appriate force and magnitude to apply to the boid
   if (rightBoundary < desiredDistance) {

      repulsionDirection = Vector2f(-1, 0);
      float repulsionMagnitude = getBaseWeightMultiplier() / rightBoundary;
      force += repulsionDirection * repulsionMagnitude;
   }

  if (leftBoundary < desiredDistance) {
    repulsionDirection = Vector2f(1, 0);
    float repulsionMagnitude = getBaseWeightMultiplier() / leftBoundary;
    force += repulsionDirection * repulsionMagnitude;
  }

  if (topBoundary < desiredDistance) {
    repulsionDirection = Vector2f(0, -1);
    float repulsionMagnitude = getBaseWeightMultiplier() / topBoundary;
    force += repulsionDirection * repulsionMagnitude;
  }

  if (bottomBoundary < desiredDistance) {
    repulsionDirection = Vector2f(0, 1);
    float repulsionMagnitude = getBaseWeightMultiplier() / bottomBoundary;
    force += repulsionDirection * repulsionMagnitude;
  }
  return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Gray);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Gray);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Gray);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Gray);                    // LEFT
}