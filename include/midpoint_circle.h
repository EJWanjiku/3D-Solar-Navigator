
#ifndef MIDPOINT_CIRCLE_H
#define MIDPOINT_CIRCLE_H

#include <set>
#include <utility>

inline std::set<std::pair<int, int>> drawMidpointCircle(
    int centerX,
    int centerY,
    int radius
) {
    std::set<std::pair<int, int>> circlePoints;

    if (radius < 0) {
        return circlePoints;
    }

    int x = 0;
    int y = radius;
    int decisionParameter = 1 - radius;

    while (x <= y) {
        circlePoints.insert({centerX + x, centerY + y});
        circlePoints.insert({centerX - x, centerY + y});
        circlePoints.insert({centerX + x, centerY - y});
        circlePoints.insert({centerX - x, centerY - y});

        circlePoints.insert({centerX + y, centerY + x});
        circlePoints.insert({centerX - y, centerY + x});
        circlePoints.insert({centerX + y, centerY - x});
        circlePoints.insert({centerX - y, centerY - x});

        x++;

        if (decisionParameter < 0) {
            decisionParameter += 2 * x + 1;
        } else {
            y--;
            decisionParameter += 2 * (x - y) + 1;
        }
    }

    return circlePoints;
}

#endif
