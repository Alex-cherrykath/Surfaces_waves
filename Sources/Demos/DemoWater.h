#pragma once
#include "../Core/Application.h"
#include "../../waves.h"
#include <vector>

namespace nkentseu {

    class DemoWater : public Application {
    private:
        WaterSimulation simulation;
        int gridWidth = 50;  // Nombre de cellules en largeur
        int gridHeight = 50; // Nombre de cellules en hauteur
        float cellSize;      // Taille d'une cellule en pixels

    public:
        DemoWater(const ApplicationProperties& props);

    protected:
        void Setup() override;
        void Update(float deltaTime) override;
        void Draw() override;
    };

} // namespace nkentseu