// Problem: CF 1409 C - Yet Another Array Restoration
// https://codeforces.com/contest/1409/problem/C

/*
Algorithm: Brute Force Search
We are trying to find the arithmetic sequence of length n that contains x and y,
and has the minimum possible maximum element.

Approach:
1. Iterate over all possible starting points 's' and steps 'd'
2. For each pair (s, d), check if both x and y can be part of the arithmetic sequence
3. If they can, calculate the last element of the sequence and keep track of the minimum
4. Output the sequence with the minimum maximum element.

Time Complexity: O(x * (y - x))
Space Complexity: O(1)

The number of valid values for s is at most x, and for d is at most (y - x).
For each combination, we perform constant time operations.
*/
#include <cstdio>
int main() {
  const long N = 50;
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x, y;
    scanf("%ld %ld %ld", &n, &x, &y);
    long start(0), step(0), mx(1e9);
    for (long s = 1; s <= x; s++) { // Iterate over all potential starting points
      for (long d = 1; d <= y - x; d++) { // Iterate over all potential steps
        // Check if x is a term in the sequence starting at s with step d
        bool hasx = ((x - s) % d == 0) && ((x - s) / d < n);
        // Check if y is a term in the sequence starting at s with step d
        bool hasy = ((y - s) % d == 0) && ((y - s) / d < n);
        if ((!hasx) || (!hasy)) {
          continue; // Skip invalid sequences
        }
        long last = s + (n - 1) * d; // Calculate the maximum element in sequence
        if (last < mx) { // Update if this sequence has a smaller maximum
          mx = last;
          start = s;
          step = d;
        }
      }
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", start + p * step); // Print each element of the sequence
    }
    puts(""); // Print newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/