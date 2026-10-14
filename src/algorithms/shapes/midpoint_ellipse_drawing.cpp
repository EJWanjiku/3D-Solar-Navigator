
#include <iostream>
#include <set>
#include <utility>

using namespace std;

set<pair<int, int>> drawMidpointEllipse(
    int centerX,
    int centerY,
    int horizontalRadius,
    int verticalRadius
) {
    set<pair<int, int>> ellipsePoints;

    if (horizontalRadius < 0 || verticalRadius < 0) {
        return ellipsePoints;
    }

    long long horizontalRadiusSquared =
        1LL * horizontalRadius * horizontalRadius;

    long long verticalRadiusSquared =
        1LL * verticalRadius * verticalRadius;

    long long horizontalOffset = 0;
    long long verticalOffset = verticalRadius;

    long long decisionParameterOne =
        verticalRadiusSquared
        - horizontalRadiusSquared * verticalRadius
        + horizontalRadiusSquared / 4.0;

    long long horizontalDerivative =
        2 * verticalRadiusSquared * horizontalOffset;

    long long verticalDerivative =
        2 * horizontalRadiusSquared * verticalOffset;

    auto addSymmetricPoints = [&](int x, int y) {
        ellipsePoints.insert({centerX + x, centerY + y});
        ellipsePoints.insert({centerX - x, centerY + y});
        ellipsePoints.insert({centerX + x, centerY - y});
        ellipsePoints.insert({centerX - x, centerY - y});
    };

    // Region 1
    while (horizontalDerivative < verticalDerivative) {
        addSymmetricPoints(
            static_cast<int>(horizontalOffset),
            static_cast<int>(verticalOffset)
        );

        horizontalOffset++;

        horizontalDerivative += 2 * verticalRadiusSquared;

        if (decisionParameterOne < 0) {
            decisionParameterOne +=
                horizontalDerivative + verticalRadiusSquared;
        } else {
            verticalOffset--;
            verticalDerivative -= 2 * horizontalRadiusSquared;

            decisionParameterOne +=
                horizontalDerivative - verticalDerivative
                + verticalRadiusSquared;
        }
    }

    // Region 2
    long long decisionParameterTwo =
        verticalRadiusSquared
            * (horizontalOffset + 0.5)
            * (horizontalOffset + 0.5)
        + horizontalRadiusSquared
            * (verticalOffset - 1)
            * (verticalOffset - 1)
        - horizontalRadiusSquared * verticalRadiusSquared;

    while (verticalOffset >= 0) {
        addSymmetricPoints(
            static_cast<int>(horizontalOffset),
            static_cast<int>(verticalOffset)
        );

        verticalOffset--;

        verticalDerivative -= 2 * horizontalRadiusSquared;

        if (decisionParameterTwo > 0) {
            decisionParameterTwo +=
                horizontalRadiusSquared - verticalDerivative;
        } else {
            horizontalOffset++;
            horizontalDerivative += 2 * verticalRadiusSquared;

            decisionParameterTwo +=
                horizontalDerivative - verticalDerivative
                + horizontalRadiusSquared;
        }
    }

    return ellipsePoints;
}

int main() {
    int centerX = 15;
    int centerY = 10;
    int horizontalRadius = 8;
    int verticalRadius = 4;

    set<pair<int, int>> ellipsePoints = drawMidpointEllipse(
        centerX,
        centerY,
        horizontalRadius,
        verticalRadius
    );

    cout << "MIDPOINT ELLIPSE DRAWING ALGORITHM\n";
    cout << "Center: (" << centerX << ", " << centerY << ")\n";
    cout << "Horizontal radius: " << horizontalRadius << "\n";
    cout << "Vertical radius: " << verticalRadius << "\n\n";

    cout << "Generated ellipse coordinates:\n";

    for (const auto& point : ellipsePoints) {
        cout << "(" << point.first << ", "
             << point.second << ")\n";
    }

    cout << "\nTotal unique points: "
         << ellipsePoints.size() << "\n";

    return 0;
}
