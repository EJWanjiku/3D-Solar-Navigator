
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    double x;
    double y;
};

struct Edge {
    double minimumY;
    double maximumY;
    double currentX;
    double inverseSlope;
};

vector<Edge> buildEdgeTable(const vector<Point>& polygon) {
    vector<Edge> edges;

    for (size_t index = 0; index < polygon.size(); index++) {
        Point startingPoint = polygon[index];
        Point endingPoint = polygon[(index + 1) % polygon.size()];

        // Horizontal edges do not contribute scan-line intersections.
        if (startingPoint.y == endingPoint.y) {
            continue;
        }

        if (startingPoint.y > endingPoint.y) {
            swap(startingPoint, endingPoint);
        }

        double inverseSlope =
            (endingPoint.x - startingPoint.x) /
            (endingPoint.y - startingPoint.y);

        edges.push_back({
            startingPoint.y,
            endingPoint.y,
            startingPoint.x,
            inverseSlope
        });
    }

    return edges;
}

void fillPolygon(const vector<Point>& polygon) {
    if (polygon.size() < 3) {
        cout << "A polygon must have at least three vertices.\n";
        return;
    }

    vector<Edge> edges = buildEdgeTable(polygon);

    int minimumY = static_cast<int>(ceil(polygon[0].y));
    int maximumY = static_cast<int>(ceil(polygon[0].y));

    for (const Point& vertex : polygon) {
        minimumY = min(minimumY, static_cast<int>(ceil(vertex.y)));
        maximumY = max(maximumY, static_cast<int>(ceil(vertex.y)));
    }

    cout << "Filled scan-line spans:\n";

    for (int scanY = minimumY; scanY < maximumY; scanY++) {
        vector<double> intersections;

        for (const Edge& edge : edges) {
            if (scanY >= edge.minimumY &&
                scanY < edge.maximumY) {
                double intersectionX =
                    edge.currentX +
                    (scanY - edge.minimumY) * edge.inverseSlope;

                intersections.push_back(intersectionX);
            }
        }

        sort(intersections.begin(), intersections.end());

        cout << "Y = " << scanY << ": ";

        if (intersections.size() < 2) {
            cout << "No fill span\n";
            continue;
        }

        for (size_t index = 0;
             index + 1 < intersections.size();
             index += 2) {

            int startingX =
                static_cast<int>(ceil(intersections[index]));

            int endingX =
                static_cast<int>(floor(intersections[index + 1]));

            cout << "X = " << startingX
                 << " to " << endingX;

            if (index + 2 < intersections.size()) {
                cout << ", ";
            }
        }

        cout << "\n";
    }
}

int main() {
    vector<Point> polygon = {
        {2, 2},
        {8, 2},
        {8, 7},
        {5, 10},
        {2, 7}
    };

    cout << "SCAN-LINE POLYGON FILLING ALGORITHM\n\n";

    cout << "Polygon vertices:\n";

    for (const Point& vertex : polygon) {
        cout << "(" << vertex.x << ", "
             << vertex.y << ")\n";
    }

    cout << "\n";

    fillPolygon(polygon);

    return 0;
}
