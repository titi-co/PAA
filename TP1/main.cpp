#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <float.h>

using namespace std;

class Point
{
public:
    int x, y;

    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

Point resDC1;
Point resDC2;

// AUX FUNCTIONS

// Calculate the distance between two points
double _dist(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// SORT Functions
// sort based on X coordinate
int cmpX(const void *a, const void *b)
{
    Point *pA = (Point *)a, *pB = (Point *)b;

    return (pA->x - pB->y);
}

// sort based on  Y coordinate
int cmpY(const void *a, const void *b)
{
    Point *pA = (Point *)a, *pB = (Point *)b;

    return (pA->y - pB->y);
}

// BRUTE FORCE ALGORITHM

// The brute force algorith below has two arguments
// The first one is the set of points
// The second one is the number of points
// For each point, test the dist to all other points and return the smallest
float closestPair_BF(Point p[], int n, bool flag = false)
{
    float min = FLT_MAX;
    Point res1;
    Point res2;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (_dist(p[i].x, p[j].x, p[i].y, p[j].y) < min)
            {
                min = _dist(p[i].x, p[j].x, p[i].y, p[j].y);
            }
        }
    }

    if (flag)
        cout << "Brute Force O(n2) - Min distance between two points is: " << min << endl;

    return min;
}

// DIVIDE AND CONQUER ALGORITHM - O(NLOG2N) APROACH

// The function below finds the smallest distance between points of the strip
// Receives the set of the points in the strip and its size
// The set of points is then sorted according to the y axis
// For it to be able to calculate the min distance, it is capped on _d
// _d is the min distance found outside the strip, via brute force

float closestS_DC1(Point S[], int s, float _d)
{
    float min = _d;

    qsort(S, s, sizeof(Point), cmpY);

    // After sorting, we use brute force approach, testing all points one by one
    for (int i = 0; i < s; ++i)
    {
        for (int j = i + 1; (j < s) && ((S[j].y - S[i].y) < min); ++j)
        {
            if (_dist(S[i].x, S[j].x, S[i].y, S[j].y) < min)
            {
                min = _dist(S[i].x, S[j].x, S[i].y, S[j].y);
            }
        }
    }

    return min;
}

// Recursive function
// Receives the total set of points, sorted in the x axis
float closestRec_DC1(Point p[], int n)
{
    // if the divided set is <= to 3, we can use brute force to get the smallest dist
    if (n <= 3)
        return closestPair_BF(p, n);

    // set the middle point
    int mid = n / 2;
    Point midP = p[mid];

    // Recursive iteration to the left and right of the middle point
    // We can get the smallest dist in each half
    float left = closestRec_DC1(p, mid);
    float right = closestRec_DC1(p + mid, n - mid);

    // Check either sides to get the smallest diff
    float _d = min(left, right);

    // Now we create the strip
    // The strip is a set of points in which the distance is closer to the middle point
    // Two points with little spacing between them can be in different halfs
    // So we create an strip with this points, so we can brute force them in the strip function above
    Point S[n];
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(p[i].x - midP.x) < _d)
        {
            S[j] = p[i];
            j++;
        }
    }

    // Get the min dist
    // The min distance can either be the one found in the recursive itaration or the brute forced strip one
    // So we can check both for the answer
    return min(_d, closestS_DC1(S, j, _d));
}

// Main function
// It orders the set on the x axis and uses the recursive call
void closestPair_DC1(Point p[], int n)
{
    qsort(p, n, sizeof(Point), cmpX);

    float min = closestRec_DC1(p, n);
    cout << "Divide and Conquer O(nlog2n) - Min distance between two points is: " << min << endl;
}

// DIVIDE AND CONQUER ALGORITHM - O(NLOGN) APROACH

// The function below finds the smallest distance between points of the strip
// Receives the set of the points in the strip and its size
// For it to be abble to calculate the min distance, it is capped on _d
// _d is the min distance found outside the strip, via brute force
// The diffente here to the other strip function is that we dont have to order anymore
// The strip set is already preordered, so we dont need to sort it in every recursive call

float closestS_DC2(Point S[], int s, float _d)
{
    float min = _d;

    for (int i = 0; i < s; ++i)
    {
        for (int j = i + 1; (j < s) && ((S[j].y - S[i].y) < min); ++j)
        {
            if (_dist(S[i].x, S[j].x, S[i].y, S[j].y) < min)
            {
                min = _dist(S[i].x, S[j].x, S[i].y, S[j].y);
            }
        }
    }

    return min;
}

// Recursive function
// Receives the x and y sets, sorted according to their named axis
float closestRec_DC2(Point x[], Point y[], int n)
{
    // if the divided set is <= to 3, we can use brute force to get the smallest dist
    if (n <= 3)
        return closestPair_BF(x, n);

    // set the middle point
    int mid = n / 2;
    Point midP = x[mid];

    // We divide all y points around the mid line
    Point yLeft[mid];      // points to the left
    Point yRight[n - mid]; // points to the right
    int i_left = 0, i_right = 0;

    for (int i = 0; i < n; i++)
    {
        if ((y[i].x < midP.x || (y[i].x == midP.x && y[i].y < midP.y)) && i_left < mid)
            yLeft[i_left++] = y[i];
        else
            yRight[i_right++] = y[i];
    }

    // Recursive iteration to the left and right of the middle point
    // We can get the smallest dist in each half
    float left = closestRec_DC2(x, yLeft, mid);
    float right = closestRec_DC2(x + mid, yRight, n - mid);

    // Check either sides to get the smallest diff
    float _d = min(left, right);

    // Now we create the strip
    // The strip is a set of points in which the distance is closer to the middle point
    // Two points with little spacing between them can be in different halfs
    // So we create an strip with this points, so we can brute force them in the strip function above
    // Since the y set is already sorted to the y axis, we can use those points as the strip set
    Point S[n];
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(y[i].x - midP.x) < _d)
        {
            S[j] = y[i];
            j++;
        }
    }

    return closestS_DC2(S, j, _d);
}

// Main function
// It orders the set on the x axis and uses the recursive call
// Also order the set according to it axis
void closestPair_DC2(Point p[], int n)
{
    Point x[n];
    Point y[n];

    for (int i = 0; i < n; i++)
    {
        x[i] = p[i];
        y[i] = p[i];
    }
    qsort(x, n, sizeof(Point), cmpX);

    qsort(y, n, sizeof(Point), cmpY);

    float min = closestRec_DC2(x, y, n);
    cout << "Divide and Conquer O(nlogn) - Min distance between two points is: " << min << endl;
}

int main()
{
    Point points[] = {Point(2, 3), Point(12, 30), Point(40, 50), Point(5, 1), Point(12, 10), Point(3, 4)};

    int n = sizeof(points) / sizeof(points[0]);

    closestPair_BF(points, n, true); // O(n2)

    closestPair_DC1(points, n); // O(nlog2n)

    closestPair_DC2(points, n); // O(nlogn)
}