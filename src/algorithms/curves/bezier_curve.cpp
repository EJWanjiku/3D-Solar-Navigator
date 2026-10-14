
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    double x;
    double y;
};

Point calculateBezierPoint(
    double parameter,
    Point startingPoint,
    Point firstControlPoint,
    Point secondControlPoint,
    Point endingPoint
) {
    double remainingParameter = 1.0 - parameter;

    double startingWeight =
        remainingParameter * remainingParameter * remainingParameter;

    double firstControlWeight =
        3 * remainingParameter * remainingParameter * parameter;

    double secondControlWeight =
        3 * remainingParameter * parameter * parameter;

    double endingWeight =
        parameter * parameter * parameter;

    Point curvePoint;

    curvePoint.x =
        startingWeight * startingPoint.x
        + firstControlWeight * firstControlPoint.x
        + secondControlWeight * secondControlPoint.x
        + endingWeight * endingPoint.x;

    curvePoint.y =
        startingWeight * startingPoint.y
        + firstControlWeight * firstControlPoint.y
        + secondControlWeight * secondControlPoint.y
        + endingWeight * endingPoint.y;

    return curvePoint;
}

vector<Point> generateBezierCurve(
    Point startingPoint,
    Point firstControlPoint,
    Point secondControlPoint,
    Point endingPoint,
    int numberOfSteps
) {
    vector<Point> curvePoints;

    if (numberOfSteps < 1) {
        numberOfSteps = 1;
    }

    for (int step = 0; step <= numberOfSteps; step++) {
        double parameter =
            static_cast<double>(step) / numberOfSteps;

        Point curvePoint = calculateBezierPoint(
            parameter,
            startingPoint,
            firstControlPoint,
            secondControlPoint,
            endingPoint
        );

        curvePoints.push_back(curvePoint);
    }

    return curvePoints;
}

int main() {
    Point startingPoint = {0, 0};
    Point firstControlPoint = {2, 8};
    Point secondControlPoint = {8, 8};
    Point endingPoint = {10, 0};

    vector<Point> curvePoints = generateBezierCurve(
        startingPoint,
        firstControlPoint,
        secondControlPoint,
        endingPoint,
        20
    );

    cout << fixed << setprecision(2);
    cout << "CUBIC BEZIER CURVE\n\n";

    cout << "Control points:\n";
    cout << "P0: (" << startingPoint.x
         << ", " << startingPoint.y << ")\n";

    cout << "P1: (" << firstControlPoint.x
         << ", " << firstControlPoint.y << ")\n";

    cout << "P2: (" << secondControlPoint.x
         << ", " << secondControlPoint.y << ")\n";

    cout << "P3: (" << endingPoint.x
         << ", " << endingPoint.y << ")\n\n";

    cout << "Generated curve points:\n";

    for (const Point& point : curvePoints) {
        cout << "(" << point.x << ", "
             << point.y << ")\n";
    }

    cout << "\nTotal points: " << curvePoints.size() << "\n";

    return 0;
}
