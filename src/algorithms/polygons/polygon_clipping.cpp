
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    double x;
    double y;
};

enum class ClippingBoundary {
    LEFT,
    RIGHT,
    BOTTOM,
    TOP
};

bool isInside(Point point, ClippingBoundary boundary,
              double boundaryValue) {
    switch (boundary) {
        case ClippingBoundary::LEFT:
            return point.x >= boundaryValue;

        case ClippingBoundary::RIGHT:
            return point.x <= boundaryValue;

        case ClippingBoundary::BOTTOM:
            return point.y >= boundaryValue;

        case ClippingBoundary::TOP:
            return point.y <= boundaryValue;
    }

    return false;
}

Point findIntersection(Point startingPoint, Point endingPoint,
                       ClippingBoundary boundary,
                       double boundaryValue) {
    double differenceX = endingPoint.x - startingPoint.x;
    double differenceY = endingPoint.y - startingPoint.y;

    if (boundary == ClippingBoundary::LEFT ||
        boundary == ClippingBoundary::RIGHT) {
        double parameter =
            (boundaryValue - startingPoint.x) / differenceX;

        return {
            boundaryValue,
            startingPoint.y + parameter * differenceY
        };
    }

    double parameter =
        (boundaryValue - startingPoint.y) / differenceY;

    return {
        startingPoint.x + parameter * differenceX,
        boundaryValue
    };
}

vector<Point> clipAgainstBoundary(
    const vector<Point>& polygon,
    ClippingBoundary boundary,
    double boundaryValue
) {
    vector<Point> clippedPolygon;

    if (polygon.empty()) {
        return clippedPolygon;
    }

    Point previousPoint = polygon.back();
    bool previousInside =
        isInside(previousPoint, boundary, boundaryValue);

    for (const Point& currentPoint : polygon) {
        bool currentInside =
            isInside(currentPoint, boundary, boundaryValue);

        if (currentInside) {
            if (!previousInside) {
                clippedPolygon.push_back(
                    findIntersection(previousPoint, currentPoint,
                                     boundary, boundaryValue)
                );
            }

            clippedPolygon.push_back(currentPoint);
        } else if (previousInside) {
            clippedPolygon.push_back(
                findIntersection(previousPoint, currentPoint,
                                 boundary, boundaryValue)
            );
        }

        previousPoint = currentPoint;
        previousInside = currentInside;
    }

    return clippedPolygon;
}

vector<Point> sutherlandHodgmanClip(
    vector<Point> polygon,
    double minimumX,
    double minimumY,
    double maximumX,
    double maximumY
) {
    polygon = clipAgainstBoundary(
        polygon, ClippingBoundary::LEFT, minimumX
    );

    polygon = clipAgainstBoundary(
        polygon, ClippingBoundary::RIGHT, maximumX
    );

    polygon = clipAgainstBoundary(
        polygon, ClippingBoundary::BOTTOM, minimumY
    );

    polygon = clipAgainstBoundary(
        polygon, ClippingBoundary::TOP, maximumY
    );

    return polygon;
}

void displayPolygon(const vector<Point>& polygon) {
    if (polygon.empty()) {
        cout << "No polygon remains inside the clipping window.\n";
        return;
    }

    for (size_t index = 0; index < polygon.size(); index++) {
        cout << "(" << polygon[index].x
             << ", " << polygon[index].y << ")";

        if (index + 1 < polygon.size()) {
            cout << " -> ";
        }
    }

    cout << " -> (" << polygon[0].x
         << ", " << polygon[0].y << ")\n";
}

int main() {
    vector<Point> polygon = {
        {2, 2},
        {8, 2},
        {8, 7},
        {5, 10},
        {2, 7}
    };

    double minimumX = 3;
    double minimumY = 3;
    double maximumX = 7;
    double maximumY = 8;

    cout << "SUTHERLAND-HODGMAN POLYGON CLIPPING\n\n";

    cout << "Original polygon:\n";
    displayPolygon(polygon);

    cout << "\nClipping window:\n";
    cout << "Minimum X: " << minimumX << "\n";
    cout << "Minimum Y: " << minimumY << "\n";
    cout << "Maximum X: " << maximumX << "\n";
    cout << "Maximum Y: " << maximumY << "\n\n";

    vector<Point> clippedPolygon = sutherlandHodgmanClip(
        polygon, minimumX, minimumY, maximumX, maximumY
    );

    cout << "Clipped polygon:\n";
    displayPolygon(clippedPolygon);

    return 0;
}
