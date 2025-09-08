#include "WindRule.h"
#include <imgui.h>
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f WindRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // todo: add a wind force here
  // hint: use the windAngle variable

  Vector2f magnitude = Vector2f::zero();

  Vector2f direction = Vector2f::zero();
  direction = Vector2f(cos((windAngle)), sin(windAngle));

  return direction *  getBaseWeightMultiplier();
}

bool WindRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valueHasChanged = false;

  if (ImGui::SliderAngle("Wind Direction", &windAngle, 0)) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}