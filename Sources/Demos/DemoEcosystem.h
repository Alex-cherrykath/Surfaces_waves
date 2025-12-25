#pragma once
#include "Core/Application.h"
#include "Core/Math/Random.h"
#include "Core/Math/Vector2.h"
#include "Graphics/Color.h"
#include <vector>
#include <cmath>

namespace nkentseu {
 class DemoEcosystem : public Application {
 private:
 struct Creature {
	 math::Vector2 position;
	 graphics::Color color;
	 float size;
	 int type; // 0: papillon, 1: feuille, 2: insecte , 3:predator
	 float tx, ty; // Pour le bruit de Perlin
	 math::Vector2 velocity;
	 bool alive = true; // marqué false si mangé
 };

 struct Food {
	 math::Vector2 position;
	 float size;
	 graphics::Color color;
 };


 std::vector<Creature> creatures;
 std::vector<Food> foods;
 
 public:
 DemoEcosystem(const ApplicationProperties& props);
 
 protected:
 void Setup() override;
 void Update(float deltaTime) override;
 void Draw() override;
 
 private:
 void UpdateCreature(Creature& creature, float deltaTime);
 };
}