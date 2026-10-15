#include <iostream>
#include <cmath>
#include <vector>

#include "raster/raster_canvas.h"
#include "algorithms/shapes/midpoint_circle.h"
#include "algorithms/shapes/midpoint_ellipse.h"

const double PI = 3.14159265358979323846;

// Draw an ellipse for an orbital path.

void drawEllipse(
    RasterCanvas& canvas,
    int cx, int cy,
    int rx, int ry,
    unsigned char r, unsigned char g, unsigned char b
) {
    auto points = drawMidpointEllipse(cx, cy, rx, ry);

    for (const auto& point : points) {
        canvas.setPixel(point.first, point.second, r, g, b);
    }
}


// Draw a circle using the Midpoint Circle Drawing algorithm.
void drawCircle(
    RasterCanvas& canvas,
    int cx, int cy,
    int radius,
    unsigned char r, unsigned char g, unsigned char b
) {
    auto points = drawMidpointCircle(cx, cy, radius);

    for (const auto& point : points) {
        canvas.setPixel(point.first, point.second, r, g, b);
    }
}

// Draw Sun rays using straight lines.
void drawSunRays(RasterCanvas& canvas, int cx, int cy) {
    for (int angle = 0; angle < 360; angle += 30) {
        double radians = angle * PI / 180.0;

        int x1 = cx + static_cast<int>(40 * std::cos(radians));
        int y1 = cy + static_cast<int>(40 * std::sin(radians));
        int x2 = cx + static_cast<int>(55 * std::cos(radians));
        int y2 = cy + static_cast<int>(55 * std::sin(radians));

        canvas.drawLine(x1, y1, x2, y2, 255, 220, 0);
    }
}


void drawDDALine(
    RasterCanvas& canvas,
    int x1, int y1,
    int x2, int y2,
    unsigned char r, unsigned char g, unsigned char b
) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(std::abs(dx), std::abs(dy));

    if (steps == 0) {
        canvas.setPixel(x1, y1, r, g, b);
        return;
    }

    double xIncrement = static_cast<double>(dx) / steps;
    double yIncrement = static_cast<double>(dy) / steps;

    double x = x1;
    double y = y1;

    for (int i = 0; i <= steps; ++i) {
        canvas.setPixel(
            static_cast<int>(std::round(x)),
            static_cast<int>(std::round(y)),
            r, g, b
        );

        x += xIncrement;
        y += yIncrement;
    }
}

struct Planet {
    const char* name;
    int orbitX;
    int orbitY;
    int radius;
    double angle;
    unsigned char r, g, b;
};

int main() {
    const int WIDTH = 1200;
    const int HEIGHT = 800;

    RasterCanvas canvas(WIDTH, HEIGHT);

    const int sunX = WIDTH / 2;
    const int sunY = HEIGHT / 2;

    Planet planets[] = {
        {"Mercury", 100,  65,  7,  20, 180, 180, 180},
        {"Venus",   150,  95, 10,  80, 230, 170,  50},
        {"Earth",   210, 135, 11, 145,  40, 100, 255},
        {"Mars",    270, 175,  9, 210, 255,  70,  50},
        {"Jupiter", 340, 220, 19,  35, 230, 150,  70},
        {"Saturn",  410, 265, 16, 250, 240, 220, 120},
        {"Uranus",  480, 310, 13, 120,  70, 220, 220},
        {"Neptune", 550, 350, 13, 300,  70, 100, 255}
    };

    // Draw all orbital paths first.
    for (const Planet& p : planets) {
        drawEllipse(
            canvas, sunX, sunY,
            p.orbitX, p.orbitY,
            75, 75, 90
        );
    }


    // Draw the Sun.
    drawCircle(canvas, sunX, sunY, 35, 255, 220, 0);
    drawSunRays(canvas, sunX, sunY);

    // Draw planets directly on their orbits.
    // No lines connect the planets to the Sun.
    for (const Planet& p : planets) {
        double radians = p.angle * PI / 180.0;

        int x = sunX +
            static_cast<int>(p.orbitX * std::cos(radians));

        int y = sunY +
            static_cast<int>(p.orbitY * std::sin(radians));

        drawCircle(
            canvas, x, y, p.radius,
            p.r, p.g, p.b
        );

        // Add a small highlight to make the planet stand out.
        drawCircle(
            canvas, x - p.radius / 3, y - p.radius / 3,
            1, 255, 255, 255
        );

        // Saturn's rings.
        if (p.name[0] == 'S') {
            drawEllipse(
                canvas, x, y,
                p.radius + 9, p.radius / 2 + 4,
                210, 190, 130
            );
        }
    }

    if (canvas.saveBMP("solar_system_output.bmp")) {
        std::cout << "Solar System image saved successfully!\n";
        std::cout << "File: solar_system_output.bmp\n";
        std::cout << "Planets: 8\n";
        std::cout << "Circle algorithm: Midpoint Circle Drawing\n";
    } else {
        std::cerr << "Failed to save Solar System image.\n";
        return 1;
    }

    return 0;
}
