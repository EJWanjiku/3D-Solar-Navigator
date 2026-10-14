
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

vector<Point> drawDDA(int x1, int y1, int x2, int y2) {
    vector<Point> points;

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = max(abs(dx), abs(dy));

    // Handle a line whose starting and ending points are identical.
    if (steps == 0) {
        points.push_back({x1, y1});
        return points;
    }

    double xIncrement = static_cast<double>(dx) / steps;
    double yIncrement = static_cast<double>(dy) / steps;

    double x = x1;
    double y = y1;

    for (int i = 0; i <= steps; i++) {
        points.push_back({
            static_cast<int>(round(x)),
            static_cast<int>(round(y))
        });

        x += xIncrement;
        y += yIncrement;
    }

    return points;
}

int main() {
    int x1 = 2;
    int y1 = 3;
    int x2 = 10;
    int y2 = 7;

    vector<Point> points = drawDDA(x1, y1, x2, y2);

    cout << "DDA Line Drawing Algorithm\n";
    cout << "Start point: (" << x1 << ", " << y1 << ")\n";
    cout << "End point: (" << x2 << ", " << y2 << ")\n\n";

    cout << "Generated points:\n";

    for (const Point& point : points) {
        cout << "(" << point.x << ", " << point.y << ")\n";
    }

    return 0;
}
