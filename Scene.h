#pragma once

#include <SDL.h>
#include <vector>
#include "Circle.h"
#include "Plane2D.h"
#include "Vector2D.h"

class Scene {
public:
    void render(const SDL_Renderer& renderer);

private:
    std::vector<Plane2D> planes_;
    std::vector<Circle> circles_;
    std::vector<Vector2D> points_;
};
