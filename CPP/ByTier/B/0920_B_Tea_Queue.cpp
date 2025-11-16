// Problem: CF 920 B - Tea Queue
// https://codeforces.com/contest/920/problem/B

/*
Purpose: This program simulates a queue for students requesting tea, determining when each student gets their tea or if they leave without it.
Algorithms/Techniques: Greedy simulation approach to manage queue and timing.
Time Complexity: O(n) per test case, where n is the number of students.
Space Complexity: O(1) - only using a few variables regardless of input size.

Input Format:
- First line contains number of test cases t.
- For each test case:
  - First line contains number of students n.
  - Next n lines contain two integers l and r, representing arrival and leave time respectively.

Output Format:
- For each test case, output n integers representing the time each student gets tea (or 0 if they don't).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x(0), g(0); // x stores result for current student, g tracks latest tea time
    for (long p = 0; p < n; p++) {
      long l, r;
      scanf("%ld %ld", &l, &r);
      if (g < l) {
        // If latest tea time is before student's arrival, student gets tea at arrival time
        g = l + 1; // Update latest tea time to next second (student uses teapot for 1 sec)
        x = l;     // Student gets tea at time l
      } else if (g <= r) {
        // If latest tea time is within student's allowed stay period
        x = g++;   // Student gets tea at current latest time (increment for next)
      } else {
        // If latest tea time is after student's allowed stay, student leaves without tea
        x = 0;
      }
      printf("%ld ", x);
    }
    puts(""); // Print newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/