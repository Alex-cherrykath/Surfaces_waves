#include "DemoWater.h"
#include "Core/Events/Mouse.h"
#include "Graphics/Color.h"
#include <algorithm>

namespace nkentseu {

    DemoWater::DemoWater(const ApplicationProperties& props) : Application(props) {
        cellSize = static_cast<float>(GetWindowWidth()) / gridWidth;
    }

    void DemoWater::Setup() {
        // Initialiser la simulation avec quelques sources et obstacles
        simulation.AddSource(WaveSource(math::Vector2(200, 300), 20.0f, 0.5f, 100.0f)); // Source 1
        simulation.AddSource(WaveSource(math::Vector2(600, 300), 15.0f, 0.7f, 80.0f));  // Source 2
        simulation.AddObstacle(Obstacle(math::Vector2(400, 200), 10.0f, 200.0f, Obstacle::Wall)); // Mur
    }

    void DemoWater::Update(float deltaTime) {
        // Mettre à jour la simulation
        simulation.Update(deltaTime);

        // Gérer les inputs pour ajouter des sources/obstacles
        if (IsMouseButtonPressed(events::MouseButton::Left)) {
            math::Vector2 mousePos = GetMousePosition();
            // Ajouter une source à la position de la souris
            simulation.AddSource(WaveSource(mousePos, 10.0f, 1.0f, 50.0f));
        }

        if (IsMouseButtonPressed(events::MouseButton::Right)) {
            math::Vector2 mousePos = GetMousePosition();
            // Ajouter un obstacle (mur) à la position de la souris
            simulation.AddObstacle(Obstacle(mousePos, 20.0f, 100.0f, Obstacle::Wall));
        }

        // Réinitialiser avec une touche (ex. : R)
        if (IsKeyPressed(events::KeyCode::R)) {
            simulation.Reset();
            Setup(); // Réinitialiser avec les sources/obstacles de base
        }
    }

    void DemoWater::Draw() {
        // Dessiner la grille représentant la hauteur de l'eau
        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                math::Vector2 point(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2);
                float height = simulation.GetTotalHeightAt(point);

                // Colorer en fonction de la hauteur (bleu pour positif, rouge pour négatif)
                int blue = static_cast<int>(128 + height * 5); // Ajuster l'échelle
                int red = static_cast<int>(128 - height * 5);
                blue = std::max(0, std::min(255, blue));
                red = std::max(0, std::min(255, red));

                graphics::Color color(red, 0, blue, 255);
                Fill(color);
                NoStroke();
                Rect(math::Vector2(point.x - cellSize / 2, point.y - cellSize / 2), math::Vector2(cellSize, cellSize));
            }
        }

        // Dessiner les sources (cercles verts)
        for (const auto& source : simulation.GetSources()) {
            Fill(graphics::Color::Green);
            Circle(source.position, 10.0f);
        }

        // Dessiner les obstacles (rectangles rouges)
        for (const auto& obstacle : simulation.GetObstacles()) {
            Fill(graphics::Color::Red);
            Rect(math::Vector2(obstacle.position.x - obstacle.width / 2, obstacle.position.y - obstacle.height / 2), math::Vector2(obstacle.width, obstacle.height));
        }
    }

} // namespace nkentseu