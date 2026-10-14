
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

vector<Point> drawBresenhamLine(
    int startingX,
    int startingY,
    int endingX,
    int endingY
) {
    vector<Point> points;

    int differenceX = abs(endingX - startingX);
    int differenceY = abs(endingY - startingY);

    int horizontalDirection =
        (startingX < endingX) ? 1 : -1;

    int verticalDirection =
        (startingY < endingY) ? 1 : -1;

    int decisionParameter = differenceX - differenceY;

    while (true) {
        points.push_back({startingX, startingY});

        if (startingX == endingX && startingY == endingY) {
            break;
        }

        int doubledDecisionParameter = 2 * decisionParameter;

        if (doubledDecisionParameter > -differenceY) {
            decisionParameter -= differenceY;
            startingX += horizontalDirection;
        }

        if (doubledDecisionParameter < differenceX) {
            decisionParameter += differenceX;
            startingY += verticalDirection;
        }
    }

    return points;
}

int main() {
    int startingX = 2;
    int startingY = 3;
    int endingX = 10;
    int endingY = 7;

    vector<Point> points = drawBresenhamLine(
        startingX, startingY, endingX, endingY
    );

    cout << "Bresenham's Line Drawing Algorithm\n";
    cout << "Starting point: (" << startingX
         << ", " << startingY << ")\n";

    cout << "Ending point: (" << endingX
         << ", " << endingY << ")\n\n";

    cout << "Generated points:\n";

    for (const Point& point : points) {
        cout << "(" << point.x << ", "
             << point.y << ")\n";
    }

    return 0;
}
