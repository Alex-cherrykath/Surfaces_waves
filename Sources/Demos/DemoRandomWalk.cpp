#include "DemoRandomWalk.h"
#include "Core/Log.h"
#include <algorithm>
#include <cmath>
#include "Core/Events/Mouse.h" //pour gerer lq souris
namespace nkentseu {

    DemoRandomWalk::DemoRandomWalk(const ApplicationProperties& props) 
        : Application(props) {
        ProcessCommandLineArgs(props.commandLineArgs);
    }

    void DemoRandomWalk::Setup() {
        SetWindowTitle("Random Walk Demo - Nature of Code Chapter 0");
        SetWindowSize(1024, 768);
        
        Log.Info("Random Walk Demo Started");
        Log.Info("Walker Type: {0}", static_cast<int>(currentType));
        Log.Info("Walker Count: {0}", walkerCount);
        Log.Info("Step Size: {0}", stepSize);

    ApplicationProperties props = GetProperty();
    walker.position = math::Vector2(math::Vector2(props.windowWidth / 2.0f, props.windowHeight/2.0f));

    // Initialiser l'histogramme (largeur = largeur de la fenêtre)
    histogram.resize(static_cast<size_t>(props.windowWidth), 0);
    }

    void DemoRandomWalk::ProcessCommandLineArgs(const std::vector<std::string>& args) {
        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == "--walker-type" && i + 1 < args.size()) {
                std::string type = args[i + 1];
                if (type == "traditional") currentType = WalkerType::Traditional;
                else if (type == "rightbiased") currentType = WalkerType::RightBiased;
                else if (type == "gaussian") currentType = WalkerType::Gaussian;
                else if (type == "perlin") currentType = WalkerType::Perlin;
            }
            else if (args[i] == "--step-size" && i + 1 < args.size()) {
                stepSize = std::stof(args[i + 1]);
            }
            else if (args[i] == "--walker-count" && i + 1 < args.size()) {
                walkerCount = std::stoi(args[i + 1]);
            }
            else if (args[i] == "--no-trail") {
                showTrail = false;
            }
        }
    }

    void DemoRandomWalk::Update(float deltaTime) {
        (void)deltaTime; // Supprimer l'avertissement du paramètre inutilisé

        walker.Step();
    }

    void DemoRandomWalk::Draw() {
        if (showTrail) {
            // Fond semi-transparent pour créer une traînée
            // Background(graphics::Color(0, 0, 0, 25));
        } else {
            Background(graphics::Color::Black);
        }

        int choice = math::Random::Range<int>(0, 7);
        if (choice == 0) {
            walker.position.x++;
        } else if (choice == 1) {
            walker.position.x--;
        } else if (choice == 2) {
            walker.position.y++;
        } else if(choice==3) {
            walker.position.y--;
        } else if(choice==4){ //pour que ca se deplace en diago; 
            walker.position.x++;
            walker.position.y++;
        } else if(choice==5){
            walker.position.x++;
            walker.position.y--;
        } else if(choice==6){
            walker.position.x--;
            walker.position.y--;
        } else if(choice==7){
            walker.position.x--;
            walker.position.y++;
        }

       //recupere lq position de lq souris
      math::Vector2 mousePos = events::Mouse::GetPosition();
      //calcul du deplacement du walker vers la souris
      math::Vector2 direction = mousePos - walker.position;
        direction.Normalized(); 
        float attractionStrength = 1.0f; // ajustement de la force d'attraction
        walker.position += direction * attractionStrength;
        // enregistrement de la position X visitée
        int x = static_cast<int>(walker.position.x);
        if (x >= 0 && x < static_cast<int>(histogram.size())) {
            histogram[x]++;
        }

        walker.Show(*this);

        // dessiner l'histogramme en bas de la fenêtre
        int histoHeight = 100;
        ApplicationProperties props = GetProperty();
        for (size_t i = 0; i < histogram.size(); ++i) {
            int value = histogram[i];
            // Normaliser la hauteur
            int barHeight = std::min(histoHeight, value);
            if (barHeight > 0) {
                Fill(graphics::Color::Green);
                Rect(math::Vector2(static_cast<float>(i), props.windowHeight - barHeight), math::Vector2(1.0f, static_cast<float>(barHeight)));
            }
        }

        DrawInfo();
    }

    void DemoRandomWalk::DrawInfo() {
        // Dessiner les informations à l'écran
        std::string typeStr;
        switch (currentType) {
            case WalkerType::Traditional: typeStr = "Traditional (4 directions)"; break;
            case WalkerType::RightBiased: typeStr = "Right Biased (40% right)"; break;
            case WalkerType::Gaussian: typeStr = "Gaussian Distribution"; break;
            case WalkerType::Perlin: typeStr = "Perlin Noise"; break;
        }
        
        std::string info = "Walker Type: " + typeStr + 
                          " | Walkers: " + std::to_string(walkerCount) +
                          " | Step Size: " + std::to_string(stepSize);
        
        // Utiliser le logging pour afficher les informations
        Log.Debug(info);
    }

} // namespace nkentseu