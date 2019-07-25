#pragma once

#include <string>
#include <SDL.h>
#include <vector>
#include "Circle.h"
#include "Plane2D.h"
#include "Point2D.h"
#include "Vector2D.h"

class Scene {
public:
    void load(const std::string& sceneName);
    void render(const Renderer& renderer) const;

private:
    std::vector<Plane2D> planes_;
    std::vector<Circle> circles_;
    std::vector<Point2D> points_;
};
