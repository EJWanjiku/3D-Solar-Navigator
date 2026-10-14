
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    double x;
    double y;
};

Point calculateCatmullRomPoint(
    Point previousPoint,
    Point startingPoint,
    Point endingPoint,
    Point nextPoint,
    double parameter
) {
    double parameterSquared = parameter * parameter;
    double parameterCubed = parameterSquared * parameter;

    Point curvePoint;

    curvePoint.x = 0.5 * (
        2 * startingPoint.x
        + (-previousPoint.x + endingPoint.x) * parameter
        + (2 * previousPoint.x - 5 * startingPoint.x
           + 4 * endingPoint.x - nextPoint.x) * parameterSquared
        + (-previousPoint.x + 3 * startingPoint.x
           - 3 * endingPoint.x + nextPoint.x) * parameterCubed
    );

    curvePoint.y = 0.5 * (
        2 * startingPoint.y
        + (-previousPoint.y + endingPoint.y) * parameter
        + (2 * previousPoint.y - 5 * startingPoint.y
           + 4 * endingPoint.y - nextPoint.y) * parameterSquared
        + (-previousPoint.y + 3 * startingPoint.y
           - 3 * endingPoint.y + nextPoint.y) * parameterCubed
    );

    return curvePoint;
}

vector<Point> generateCatmullRomSpline(
    const vector<Point>& controlPoints,
    int stepsPerSegment
) {
    vector<Point> curvePoints;

    if (controlPoints.size() < 2) {
        return curvePoints;
    }

    if (stepsPerSegment < 1) {
        stepsPerSegment = 1;
    }

    for (size_t index = 0;
         index + 1 < controlPoints.size();
         index++) {

        Point previousPoint =
            (index == 0)
            ? controlPoints[index]
            : controlPoints[index - 1];

        Point startingPoint = controlPoints[index];
        Point endingPoint = controlPoints[index + 1];

        Point nextPoint =
            (index + 2 >= controlPoints.size())
            ? controlPoints[index + 1]
            : controlPoints[index + 2];

        for (int step = 0; step < stepsPerSegment; step++) {
            double parameter =
                static_cast<double>(step) / stepsPerSegment;

            curvePoints.push_back(
                calculateCatmullRomPoint(
                    previousPoint,
                    startingPoint,
                    endingPoint,
                    nextPoint,
                    parameter
                )
            );
        }
    }

    curvePoints.push_back(controlPoints.back());

    return curvePoints;
}

int main() {
    vector<Point> controlPoints = {
        {0, 0},
        {2, 5},
        {5, 3},
        {8, 7},
        {10, 2}
    };

    vector<Point> curvePoints =
        generateCatmullRomSpline(controlPoints, 10);

    cout << fixed << setprecision(2);
    cout << "CATMULL-ROM SPLINE\n\n";

    cout << "Control points:\n";

    for (const Point& point : controlPoints) {
        cout << "(" << point.x << ", "
             << point.y << ")\n";
    }

    cout << "\nGenerated spline points:\n";

    for (const Point& point : curvePoints) {
        cout << "(" << point.x << ", "
             << point.y << ")\n";
    }

    cout << "\nTotal generated points: "
         << curvePoints.size() << "\n";

    return 0;
}
