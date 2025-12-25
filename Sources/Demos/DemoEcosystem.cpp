#include "DemoEcosystem.h"
#include <algorithm>
namespace nkentseu {
 DemoEcosystem::DemoEcosystem(const ApplicationProperties& props)
 : Application(props) {}
 
 void DemoEcosystem::Setup() {
 Background(graphics::Color::White);
 
 // Créer différentes créatures
 for (int i = 0; i < 50; i++) {
 Creature c;
 c.position = math::Vector2(
 math::Random::Range(0.0f, (float)GetWindowWidth()),
 math::Random::Range(0.0f, (float)GetWindowHeight())
 );
 
 c.type = math::Random::Range(0, 3);
 c.tx = math::Random::Range(0.0f, 1000.0f);
 c.ty = math::Random::Range(0.0f, 1000.0f);
 c.velocity = math::Vector2(0, 0);
 c.alive = true;
 
 if (c.type == 0) { // Papillon - Mouvement erratique //il doit avoir une force qui fait que les insectes ne se touchent pas.
 c.color = graphics::Color(255, 200, 0, 255);
 c.size = 3.0f;
 } else if (c.type == 1) { // Feuille - Mouvement doux avec bruit de Perlin //doivent rester statiques 
 c.color = graphics::Color(0, 180, 0, 255);
 c.size = 5.0f;
 } else if(c.type ==2) { // Insecte - Petits mouvements rapides
 c.color = graphics::Color(100, 100, 100, 255);
 c.size = 2.0f;
 }else{ //predateurs.
   c.color = graphics::Color(180, 20, 20, 255);
   c.size = 6.0f;
 }
 
 creatures.push_back(c);
 }

 // Créer de la nourriture
 for (int i = 0; i < 80; i++) {
    Food f;
    f.position = math::Vector2(
       math::Random::Range(0.0f, (float)GetWindowWidth()),
       math::Random::Range(0.0f, (float)GetWindowHeight())
      );
    f.size = math::Random::Range(2.0f, 5.0f);
    f.color = graphics::Color(128, 0, 128, 128);// Color violette
    foods.push_back(f);
   }

 void DemoEcosystem::Update(float deltaTime){
 // Mettre à jour les créatures
 for (auto& creature : creatures) {
    UpdateCreature(creature, deltaTime);
 }

 // Mettre à jour les prédateurs: chasser la créature la plus proche
 const float predatorSpeed = 0.6f;
 const float predatorEat = 6.0f;

 // éviter que les predateurs se collent)
 const float predatorRepelRadius = 30.0f; // distance où la répulsion commence
 const float predatorRepelStrength = 0.8f; // intensité maximale de répulsion
 for (c.type ==3 : predators) {
    // Trouver la créature vivante la plus proche
    float bestDist = 1e9f;
    int bestIdx = -1;
    for (size_t i = 0; i < creatures.size(); ++i) {
       if (!creatures[i].alive) continue;
       math::Vector2 d = creatures[i].position - c.position;
       float dist = d.Magnitude();
       if (dist < bestDist) { bestDist = dist; bestIdx = (int)i; }
    }

      if (bestIdx != -1) {
       // Accelerer vers la proie
       math::Vector2 dir = (creatures[bestIdx].position - pred.position).Normalized();
       pred.velocity = pred.velocity + dir * predatorSpeed;
       // Limiter la vitesse
       if (pred.velocity.Magnitude() > 3.0f) c.velocity = c.velocity.Normalized() * 3.0f;
       c.position = c.position + c.velocity;

       // Si assez proche, manger
       if (bestDist < predatorEat) {
          creatures[bestIdx].alive = false;
          // Créer un peu de nourriture à l'emplacement
          Food f;
          f.position = creatures[bestIdx].position;
          f.size = math::Random::Range(2.0f, 4.0f);
          f.color = graphics::Color(200, 120, 40, 255);
          foods.push_back(f);
       }
    } else {
       // Mouvement erratique si pas de proie
       pred.velocity = pred.velocity * 0.95f;
       pred.position = pred.position + pred.velocity;
    }
     
    // Garder le prédateur dans les limites
    if (pred.position.x < 0) pred.position.x = 0;
    if (pred.position.y < 0) pred.position.y = 0;
    if (pred.position.x > GetWindowWidth()) pred.position.x = (float)GetWindowWidth();
    if (pred.position.y > GetWindowHeight()) pred.position.y = (float)GetWindowHeight();
 }

 // Nettoyer créatures mangées
 creatures.erase(std::remove_if(creatures.begin(), creatures.end(), [](const Creature& c){ return !c.alive; }), creatures.end());

 // Nettoyer nourriture consommée (taille <= 0 marque consommé)
 foods.erase(std::remove_if(foods.begin(), foods.end(), [](const Food& f){ return f.size <= 0.0f; }), foods.end());
 }
 
 void DemoEcosystem::UpdateCreature(Creature& creature, float deltaTime) {
   (void)deltaTime;
   // Paramètres de comportement
   const float foodAttractionStrength = 0.12f;
   const float foodEatDistance = 6.0f;
   const float fearRadius = 50.0f;
   const float fleeStrength = 0.6f;

   // Comportements de base selon le type
   if (creature.type == 0) {
      // Papillon: mouvement erratique avec tendance
      float r = math::Random::Value();
      if (r < 0.6f) creature.velocity.x += 0.1f;
      if (r < 0.3f) creature.velocity.y -= 0.1f;
      if (r > 0.8f) creature.velocity.x -= 0.1f;
      if (r > 0.9f) creature.velocity.y += 0.1f;
      creature.velocity = creature.velocity * 0.95f;
   } else if (creature.type == 1) {
      // Feuille: mouvement doux avec bruit de Perlin
      float noiseX = math::Random::Noise(creature.tx);
      float noiseY = math::Random::Noise(creature.ty);
      creature.velocity.x += math::Random::Map(noiseX, 0.0f, 1.0f, -0.05f, 0.05f);
      creature.velocity.y += math::Random::Map(noiseY, 0.0f, 1.0f, -0.03f, 0.07f);
      creature.tx += 0.01f;
      creature.ty += 0.01f;
      creature.velocity = creature.velocity * 0.9f;
   } else {
      // Insecte: petits mouvements rapides
      creature.velocity.x += math::Random::Range(-0.5f, 0.5f);
      creature.velocity.y += math::Random::Range(-0.5f, 0.5f);
      if (creature.velocity.Magnitude() > 2.0f) {
         creature.velocity = creature.velocity.Normalized() * 2.0f;
      }
   }

   // Attraction vers la nourriture la plus proche
   if (!foods.empty()) {
      float bestDist = 1e9f;
      int bestIdx = -1;
      for (size_t i = 0; i < foods.size(); ++i) {
         math::Vector2 d = foods[i].position - creature.position;
         float dist = d.Magnitude();
         if (dist < bestDist) { bestDist = dist; bestIdx = (int)i; }
      }
      if (bestIdx != -1) {
         math::Vector2 toFood = (foods[bestIdx].position - creature.position);
         float dist = toFood.Magnitude();
         math::Vector2 dir = toFood.Normalized();
         // Si proche, consommer la nourriture
         if (dist < foodEatDistance) {
            // marquer la nourriture comme consommée
            foods[bestIdx].size = 0.0f;
            creature.size += 0.3f;
            creature.velocity = creature.velocity * 0.5f;
         } else {
            // appliquer force d'attraction
            creature.velocity = creature.velocity + dir * (foodAttractionStrength);
         }
      }
   }

   // Fuite des prédateurs proches
   if (!predators.empty()) {
      for (const auto& pred : predators) {
         math::Vector2 d = pred.position - creature.position;
         float dist = d.Magnitude();
         if (dist < fearRadius) {
            math::Vector2 away = (creature.position - pred.position).Normalized();
            creature.velocity = creature.velocity + away * fleeStrength;
         }
      }
   }

   // Mettre à jour la position
   creature.position = creature.position + creature.velocity;

   // Garder dans les limites avec rebond
   if (creature.position.x < 0 || creature.position.x > GetWindowWidth()) {
      creature.velocity.x = -creature.velocity.x;
      creature.position.x = std::max(0.0f, std::min(creature.position.x, (float)GetWindowWidth()));
   }
   if (creature.position.y < 0 || creature.position.y > GetWindowHeight()) {
      creature.velocity.y = -creature.velocity.y;
      creature.position.y = std::max(0.0f, std::min(creature.position.y, (float)GetWindowHeight()));
   }
 }
 
 void DemoEcosystem::Draw() {
 // Effacer légèrement pour créer un effet de traînée
 Fill(graphics::Color(255, 255, 255, 10));
 NoStroke();
 Rect(math::Vector2(0, 0),
 math::Vector2(GetWindowWidth(), GetWindowHeight()));
 
 // Dessiner les créatures
 for (const auto& creature : creatures) {
    Fill(creature.color);
    NoStroke();
    Circle(creature.position, creature.size);
 }

 // Dessiner la nourriture
 for (const auto& f : foods) {
    Fill(f.color);
    NoStroke();
    Circle(f.position, f.size);
 }

 // Dessiner les prédateurs
 for (const auto& p : predators) {
    Fill(p.color);
    NoStroke();
    Circle(p.position, p.size);
 }
 }
}
// Fonction de création
nkentseu::Application* CreateEcosystemDemo(const
nkentseu::ApplicationProperties& props) {
 return new nkentseu::DemoEcosystem(props);
}}