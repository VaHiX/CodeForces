// Problem: CF 873 C - Strange Game On Matrix
// https://codeforces.com/contest/873/problem/C

/*
Algorithm/Techniques: Dynamic Programming, Prefix Sums
Time Complexity: O(n * m)
Space Complexity: O(n * m)

This code solves a game where Ivan wants to maximize his score by selecting 
the best rows to start counting 1s from in each column. The score is calculated 
by taking the topmost 1 in each column and counting up to k elements below it. 
We use prefix sums to efficiently calculate the number of 1s in any subarray. 
For each column, we iterate through all possible start positions for the k-element window, 
compute the maximum sum (score) achievable, and track the minimum replacements needed.
*/

#include <cstdio>
#include <vector>
int main() {
  long n, m, k;
  scanf("%ld %ld %ld", &n, &m, &k);
  std::vector<std::vector<int>> a(n, std::vector<int>(m, 0));
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < m; col++) {
      scanf("%d", &a[row][col]);
    }
  }
  long total(0), count(0);
  for (long col = 0; col < m; col++) {
    // Build prefix sum array for the column
    std::vector<long> b(n, 0);
    b[0] = a[0][col];
    for (long row = 1; row < n; row++) {
      b[row] = b[row - 1] + a[row][col];
    }
    long maxSum(0), chg(0);
    // Try each possible starting row for the k-window
    for (long row = 0; row < n; row++) {
      if (a[row][col] == 0) {
        continue; // Skip if there's no 1 at this row
      }
      // Calculate the sum of 1s in the k-element window starting at 'row'
      long s = (row > 0) ? b[row - 1] : 0;  // Sum before the start
      long f = (row + k - 1 <= n - 1) ? b[row + k - 1] : b[n - 1];  // Sum up to end of window
      long sum = f - s;  // Total 1s in the k-window
      if (sum > maxSum) {
        chg = s;  // Number of 0s (replacements needed) before window
        maxSum = sum;  // Best score for this column
      }
    }
    total += maxSum;  // Add best score for this column to total
    count += chg;  // Add minimum required changes for this column to total
  }
  printf("%ld %ld\n", total, count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/