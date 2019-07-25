#include <string>
#include "Point2D.h"
#include "Renderer.h"
#include "Scene.h"

void Scene::load(const std::string& sceneName) 
{
    // TODO: Load scene from file

    // TODO: Load from JSON scene description
    this->points_.push_back(Point2D({Vector2D(100, 100), COLOR_RED}));
}

void Scene::render(const Renderer& renderer) const
{
    // Draw points
    for(std::vector<Point2D>::const_iterator point = this->points_.begin(); point != this->points_.end(); ++point) 
    {
        renderer.drawPoint(*point);
    }
}
