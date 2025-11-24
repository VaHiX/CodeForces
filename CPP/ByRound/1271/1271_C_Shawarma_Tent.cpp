// Problem: CF 1271 C - Shawarma Tent
// https://codeforces.com/contest/1271/problem/C

/*
C. Shawarma Tent
Algorithms/Techniques: Greedy approach with coordinate analysis
Time Complexity: O(n)
Space Complexity: O(1)

The problem involves placing a shawarma tent at an integer coordinate to maximize the number of students who will pass by it on their way from school to home.
Each student walks along a shortest path, which means they can go either horizontally or vertically.
For any given point (px, py), if a student's house is at (x, y) and the school is at (sx, sy),
a path goes through (px, py) if:
- px is between sx and x, OR
- py is between sy and y

However, since we are trying to find the maximum number of students visiting the tent,
we can consider placing the tent just near one of the axes (left, right, up, down) relative to the school.
There are 4 directions (up/down/left/right).
We count how many students' houses fall in each direction relative to the school.

If we place the tent at (sx, sy + 1), it will intercept all students whose houses are above the school.
Similarly for all sides.

So we count the number of students in four quadrants and place the tent where we get maximum count.
This is a greedy approach since we know placing it along the axis with the most students gives the max.
*/

#include <cstdio>
int main() {
  long n, sx, sy;
  scanf("%ld %ld %ld", &n, &sx, &sy);
  long under(0), above(0), left(0), right(0); // Counters for students in each direction
  for (long p = 0; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    if (y < sy) {
      ++under;  // Student house is below school
    } else if (y > sy) {
      ++above;  // Student house is above school
    }
    if (x < sx) {
      ++left;   // Student house is to the left of school
    } else if (x > sx) {
      ++right;  // Student house is to the right of school
    }
  }
  if (under >= above && under >= left && under >= right) {
    printf("%ld\n%ld %ld\n", under, sx, sy - 1);  // Place tent just below school
  } else if (above >= under && above >= left && above >= right) {
    printf("%ld\n%ld %ld\n", above, sx, sy + 1);  // Place tent just above school
  } else if (left >= under && left >= above && left >= right) {
    printf("%ld\n%ld %ld\n", left, sx - 1, sy);   // Place tent just to the left of school
  } else if (right >= under && right >= above && right >= left) {
    printf("%ld\n%ld %ld\n", right, sx + 1, sy);  // Place tent just to the right of school
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/