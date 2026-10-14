
#include <iostream>
#include <set>
#include <utility>

using namespace std;

set<pair<int, int>> drawMidpointCircle(
    int centerX,
    int centerY,
    int radius
) {
    set<pair<int, int>> circlePoints;

    if (radius < 0) {
        return circlePoints;
    }

    int horizontalOffset = 0;
    int verticalOffset = radius;
    int decisionParameter = 1 - radius;

    while (horizontalOffset <= verticalOffset) {
        circlePoints.insert({centerX + horizontalOffset, centerY + verticalOffset});
        circlePoints.insert({centerX - horizontalOffset, centerY + verticalOffset});
        circlePoints.insert({centerX + horizontalOffset, centerY - verticalOffset});
        circlePoints.insert({centerX - horizontalOffset, centerY - verticalOffset});

        circlePoints.insert({centerX + verticalOffset, centerY + horizontalOffset});
        circlePoints.insert({centerX - verticalOffset, centerY + horizontalOffset});
        circlePoints.insert({centerX + verticalOffset, centerY - horizontalOffset});
        circlePoints.insert({centerX - verticalOffset, centerY - horizontalOffset});

        horizontalOffset++;

        if (decisionParameter < 0) {
            decisionParameter += 2 * horizontalOffset + 1;
        } else {
            verticalOffset--;
            decisionParameter +=
                2 * (horizontalOffset - verticalOffset) + 1;
        }
    }

    return circlePoints;
}

int main() {
    int centerX = 10;
    int centerY = 10;
    int radius = 5;

    set<pair<int, int>> circlePoints =
        drawMidpointCircle(centerX, centerY, radius);

    cout << "MIDPOINT CIRCLE DRAWING ALGORITHM\n";
    cout << "Center: (" << centerX << ", " << centerY << ")\n";
    cout << "Radius: " << radius << "\n\n";

    cout << "Generated circle coordinates:\n";

    for (const auto& point : circlePoints) {
        cout << "(" << point.first << ", "
             << point.second << ")\n";
    }

    cout << "\nTotal unique points: " << circlePoints.size() << "\n";

    return 0;
}
