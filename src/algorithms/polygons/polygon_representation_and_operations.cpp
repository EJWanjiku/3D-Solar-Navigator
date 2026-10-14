
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    double x;
    double y;
};

void displayPolygon(const vector<Point>& vertices) {
    for (int index = 0; index < static_cast<int>(vertices.size()); index++) {
        cout << "("
             << vertices[index].x << ", "
             << vertices[index].y << ")";

        if (index < static_cast<int>(vertices.size()) - 1) {
            cout << " -> ";
        }
    }

    cout << " -> (" << vertices[0].x
         << ", " << vertices[0].y << ")\n";
}

void translatePolygon(
    vector<Point>& vertices,
    double horizontalMovement,
    double verticalMovement
) {
    for (Point& vertex : vertices) {
        vertex.x += horizontalMovement;
        vertex.y += verticalMovement;
    }
}

void scalePolygon(
    vector<Point>& vertices,
    double scaleFactor,
    Point fixedPoint
) {
    for (Point& vertex : vertices) {
        vertex.x = fixedPoint.x
            + (vertex.x - fixedPoint.x) * scaleFactor;

        vertex.y = fixedPoint.y
            + (vertex.y - fixedPoint.y) * scaleFactor;
    }
}

void rotatePolygon(
    vector<Point>& vertices,
    double angleInDegrees,
    Point fixedPoint
) {
    const double pi = acos(-1.0);
    double angleInRadians = angleInDegrees * pi / 180.0;

    double cosineValue = cos(angleInRadians);
    double sineValue = sin(angleInRadians);

    for (Point& vertex : vertices) {
        double relativeX = vertex.x - fixedPoint.x;
        double relativeY = vertex.y - fixedPoint.y;

        double rotatedX =
            relativeX * cosineValue - relativeY * sineValue;

        double rotatedY =
            relativeX * sineValue + relativeY * cosineValue;

        vertex.x = fixedPoint.x + rotatedX;
        vertex.y = fixedPoint.y + rotatedY;
    }
}

int main() {
    vector<Point> triangle = {
        {2, 2},
        {6, 2},
        {4, 5}
    };

    cout << fixed << setprecision(2);

    cout << "POLYGON REPRESENTATION AND OPERATIONS\n\n";

    cout << "Original triangle:\n";
    displayPolygon(triangle);

    translatePolygon(triangle, 3, 2);

    cout << "\nAfter translation by (3, 2):\n";
    displayPolygon(triangle);

    scalePolygon(triangle, 2.0, {3, 2});

    cout << "\nAfter scaling by factor 2 around (3, 2):\n";
    displayPolygon(triangle);

    rotatePolygon(triangle, 90, {3, 2});

    cout << "\nAfter rotating 90 degrees around (3, 2):\n";
    displayPolygon(triangle);

    return 0;
}
