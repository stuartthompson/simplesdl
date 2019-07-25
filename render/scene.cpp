#include <string>
#include <zen-math.h>
#include "point2d.h"
#include "renderer.h"
#include "scene.h"

void Scene::load(const std::string& sceneName) 
{
    // TODO: Load scene from file

    // TODO: Load from JSON scene description
    /* Points */
    
    this->points_.push_back(Point2D({Vector2D(100, 100), COLOR_RED}));


    /* Lines */

    // Line from coord pair
    this->lines_.push_back(Line2D({Plane2D({400, 100}, {450, 120}), COLOR_RED}));

    // Line at an angle
    Vector2D start = Vector2D(400, 200);
	Vector2D end = Vector2D::fromPolar(0, 50) + start;   
	this->lines_.push_back(Line2D({Plane2D(start, end), COLOR_GREEN}));

    // Lines in various directions (starburst)
	Vector2D starburstOrigin = Vector2D({100, 100});
	for (int i = 0; i <= 360; i += 10) {
		this->lines_.push_back(Line2D({Plane2D(starburstOrigin, degreesToRadians(i), 100), COLOR_YELLOW}));
	}


    /* Circles */

    // Draw a circle
	this->circles_.push_back(Circle(Vector2D({300, 100}), 50, Color({255, 255, 128, 255}), true));


    /* Clock */
    Vector2D origin = Vector2D(400, 400);
    float radius = 75;
    int hourMarkerLength = 8;
    int hourHandLength = 40;
    int minuteHandLength = 55;
    int hours = 10;
    int minutes = 15;
    Color borderColor = COLOR_YELLOW;
    Color markerColor = COLOR_GRAY;
    Color hourHandColor = COLOR_WHITE;
    Color minuteHandColor = COLOR_GREEN;

    this->circles_.push_back(Circle({origin, radius, borderColor, false}));
	// Draw hour markers
	for (float hour = 0; hour < 12; hour++)
	{
		float angle = 180 - ((360 / 12) * hour); // Add 360/12 degrees each increment (1 marker per hour)
		Vector2D hourMarkerStart = Vector2D::fromPolar(degreesToRadians(angle), radius - hourMarkerLength) + origin;
		Vector2D hourMarkerEnd = Vector2D::fromPolar(degreesToRadians(angle), hourMarkerLength) + hourMarkerStart;
		this->lines_.push_back(Line2D({Plane2D(hourMarkerStart, hourMarkerEnd), markerColor}));
	}
	// Draw hands
	float hourHandAngle = (hours * (360 / 12)) - 90;
	// Adjust hour handle angle for partial hour
	float percentThroughHour = (float)minutes / (float)60;
	hourHandAngle = hourHandAngle + ((360 / 12) * percentThroughHour);
	this->lines_.push_back(Line2D({Plane2D(origin, Vector2D::fromPolar(degreesToRadians(hourHandAngle), hourHandLength) + origin), hourHandColor}));
	float minuteHandAngle = (minutes * (360 / 60)) - 90;
	this->lines_.push_back(Line2D({Plane2D(origin, Vector2D::fromPolar(degreesToRadians(minuteHandAngle), minuteHandLength) + origin), minuteHandColor}));
}

void Scene::render(const Renderer& renderer) const
{
    // Draw points
    for(std::vector<Point2D>::const_iterator point = this->points_.begin(); point != this->points_.end(); ++point) 
    {
        renderer.drawPoint2D(*point);
    }

    // Draw Lines
    for (std::vector<Line2D>::const_iterator line = this->lines_.begin(); line != this->lines_.end(); ++line)
    {
        renderer.drawLine2D(*line);
    }

    // Draw Circles
    for (std::vector<Circle>::const_iterator circle = this->circles_.begin(); circle != this->circles_.end(); ++circle)
    {
        renderer.drawCircle(*circle);
    }

    // Draw Text
    renderer.drawText("Hello, World!", Vector2D(200, 200), "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 18, COLOR_CYAN);
}
