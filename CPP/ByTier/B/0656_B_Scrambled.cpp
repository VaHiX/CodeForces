// Problem: CF 656 B - Scrambled
// https://codeforces.com/contest/656/problem/B

/*
Problem: B. Scrambled

Purpose:
This program computes the probability that on a randomly chosen day, at least one of the dish-washing schedules will require washing dishes.
The input consists of two arrays M and R, where for each index i, dish-washing occurs on day D if D % M[i] == R[i].
We simulate a large number of days (1e7) and count how many of those days have at least one schedule triggering.

Algorithms/Techniques:
- Brute-force simulation over a fixed number of days (MAX_DAYS)
- Modular arithmetic to determine if a day matches a schedule
- Probability calculation based on frequency of matching days

Time Complexity: O(N * MAX_DAYS) where N is the size of arrays and MAX_DAYS = 1e7.
Space Complexity: O(N) for storing the two vectors m and r.

Input Format:
- First line: integer N (size of arrays)
- Second line: N integers representing array M
- Third line: N integers representing array R

Output Format:
- Single floating-point number representing the probability
*/

#include <cstdio>
#include <vector>
int main() {
  const long MAX_DAYS = 1e7; // Total number of days to simulate
  int n;
  scanf("%d", &n); // Read number of schedules
  std::vector<int> m(n), r(n); // Declare vectors for M and R arrays
  for (int p = 0; p < n; p++) {
    scanf("%d", &m[p]); // Read M array values
  }
  for (int p = 0; p < n; p++) {
    scanf("%d", &r[p]); // Read R array values
  }
  double count(0); // Counter for days when at least one schedule triggers
  for (int day = 0; day < MAX_DAYS; day++) { // Loop through all simulated days
    for (long p = 0; p < n; p++) { // Check each schedule
      if (day % m[p] == r[p]) { // If this day matches the schedule
        ++count; // Increment counter
        break; // No need to check remaining schedules for this day
      }
    }
  }
  printf("%.6lf\n", count / MAX_DAYS); // Output probability as ratio of matching days to total days
}


// https://github.com/VaHiX/codeForces/