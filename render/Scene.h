#pragma once

#include <string>
#include <SDL.h>
#include <vector>
#include "../math/math.h"
#include "Circle.h"
#include "Point2D.h"

class Scene {
public:
    void load(const std::string& sceneName);
    void render(const Renderer& renderer) const;

private:
    std::vector<Line2D> lines_;
    std::vector<Point2D> points_;
    std::vector<Circle> circles_;
};