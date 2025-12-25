#pragma once

#include "Core/Application.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Random.h"
#include "Graphics/Color.h"
#include <vector>
#include <string>

namespace nkentseu {

    class DemoRandomWalk : public Application {
        public:
            enum class WalkerType {
                Traditional,
                RightBiased,
                Gaussian,
                Perlin
            };
            
            struct Walker {
                math::Vector2 position;
                
                Walker() : position(0, 0) {}

                void Show(DemoRandomWalk& demo) {
                    demo.NoStroke();
                    demo.Fill(graphics::Color::White);
                    demo.Circle(position, 2);
                }

                void Step() {
                    int choice = math::Random::Range<int>(0, 7);
                    if (choice == 0) {
                        position.x++;
                    } else if (choice == 1) {
                        position.x--;
                    } else if (choice == 2) {
                        position.y++;
                    } else if(choice==3) {
                        position.y--;
                    } else if(choice==4){ //pour que ca se deplace en diago; 
                        position.x++;
                        position.y++;
                    } else if(choice==5){
                        position.x++;
                        position.y--;
                    } else if(choice==6){
                        position.x--;
                        position.y--;
                    } else if(choice==7){
                        position.x--;
                        position.y++;
                    }
                }
            };
            
        private:
            std::vector<Walker> walkers;
            Walker walker;
            WalkerType currentType = WalkerType::Traditional;
            float stepSize = 2.0f;
            int walkerCount = 50;
            bool showTrail = true;
            // float noiseIncrement = 0.01f;
            std::vector<int> histogram; // Histogramme des positions X visitées
            
        public:
            DemoRandomWalk(const ApplicationProperties& props);
            
        protected:
            void Setup() override;
            void Update(float deltaTime) override;
            void Draw() override;
            void ProcessCommandLineArgs(const std::vector<std::string>& args); 
        private:
            void DrawInfo();
    };

} // namespace nkentseu