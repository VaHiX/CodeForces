// Problem: CF 479 D - Long Jumps
// https://codeforces.com/contest/479/problem/D

/*
D. Long Jumps
Algorithms/Techniques: Set-based lookup, greedy approach with precomputed distances
Time Complexity: O(n log n) - due to set operations (insert and count) which take log n time each
Space Complexity: O(n) - for storing the marks in a set

Given a ruler with n marks at positions a1, a2, ..., an,
we need to determine the minimum number of additional marks
to be added so that we can measure distances x and y.
The goal is to check whether there exist pairs of marks such that
the difference between their positions equals x or y.
We use a set to efficiently look up previously inserted marks.
*/
#include <cstdio>
#include <set>
int main() {
  long n, len, x, y;
  scanf("%ld %ld %ld %ld\n", &n, &len, &x, &y);
  std::set<long> marks; // Store all current mark positions
  bool fx(0), fy(0), fxy(0); // Flags to indicate if x or y can be measured
  long d;
  while (n--) {
    long a;
    scanf("%ld", &a);
    marks.insert(a); // Insert current mark position into the set
    // Check if we have a pair of marks that differ by x
    if (x <= a && marks.count(a - x)) {
      fx = 1;
    }
    // Check if we have a pair of marks that differ by y
    if (y <= a && marks.count(a - y)) {
      fy = 1;
    }
    // Check if there's a way to form x + y using existing marks
    if (x + y <= a && marks.count(a - x - y)) {
      fxy = 1;
      d = a - y; // Position of the new mark needed
    }
    // Alternative check for forming x + y using current and previous marks
    if (y <= a && marks.count(a + x - y)) {
      fxy = 1;
      d = a - y;
    }
    // Another way to form x + y with a mark added at a + x position
    if (a + x <= len && marks.count(a + x - y)) {
      fxy = 1;
      d = a + x;
    }
  }
  // Output results based on what distances can be measured
  if (fx && fy) {
    puts("0"); // Both distances already measurable
  } else if (fx) {
    printf("1\n%ld\n", y); // Only x is measurable, need one more mark at distance y
  } else if (fy) {
    printf("1\n%ld\n", x); // Only y is measurable, need one more mark at distance x
  } else if (fxy) {
    printf("1\n%ld\n", d); // Can form both x and y with existing marks, output d
  } else {
    printf("2\n%ld %ld\n", x, y); // Need two new marks at distances x and y
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/