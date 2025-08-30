/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  int numPoints, numPapers;
  scanf("%d %d\n", &numPoints, &numPapers);
  double distance = 0;
  int oldX = 0, oldY = 0, newX = 0, newY = 0;
  scanf("%d %d\n", &oldX, &oldY);
  while (--numPoints) {
    scanf("%d %d\n", &newX, &newY);
    distance +=
        sqrt((newX - oldX) * (newX - oldX) + (newY - oldY) * (newY - oldY));
    oldX = newX;
    oldY = newY;
  }
  const int speed = 50;
  printf("%.9lf\n", numPapers * distance / speed);
  return 0;
}
