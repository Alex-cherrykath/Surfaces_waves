#include "Main.h"
#include "Demos/DemoWater.h"

// Déclaration des fonctions de démo
nkentseu::Application* CreateWaterDemo(const nkentseu::ApplicationProperties& props);

// Fonction pour créer la démo water
nkentseu::Application* CreateWaterDemo(const nkentseu::ApplicationProperties& props) {
    return new nkentseu::DemoWater(props);
}

// Fonction principale
nkentseu::Application* Main(nkentseu::Args args) {
    // Créer les propriétés de l'application
    auto props = nkentseu::Application::CreatePropertiesFromConfig("app.config");
    return new nkentseu::DemoWater(props);
}
