#pragma once
#include "Core/Application.h"

namespace nkentseu
{
    class Count : public Application {
        public:
            Count(const ApplicationProperties& props);

        public:
        float R=100;
        math::Vector2 position;
        const float gravity=9.81;
        float friction=20;

        public:
            void Setup() ;
            void Update(float deltaTime);
            void Draw();
    };
} // namespace nkentseu

