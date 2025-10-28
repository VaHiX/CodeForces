// Problem: CF 1330 A - Dreamoon and Ranking Collection
// https://codeforces.com/contest/1330/problem/A

#include <cstdio>
#include <vector>
int main() {
  const long N = 207; // Size of the boolean array to track which ranks are already achieved (up to 206)
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x); // Read number of contests and additional contests allowed
    std::vector<bool> b(N, false); // Boolean array to mark which ranks are already achieved
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      b[a] = true; // Mark the rank 'a' as achieved
    }
    long res(0); // Stores the result: largest rank that can be collected
    for (long p = 1; p < N; p++) {
      if (b[p]) {
        continue; // If rank 'p' is already achieved, skip it
      }
      if (x > 0) {
        --x; // Use one of the additional contests to achieve this rank
      } else {
        res = p - 1; // If no more contests left, return the previous rank as maximum achievable
        break;
      }
    }
    printf("%ld\n", res);
  }
  return 0;
}
/*
 * Problem: Dreamoon and Ranking Collection
 *
 * Purpose:
 *   Given a list of ranks achieved in past contests and a number of future contests,
 *   find the largest rank that can be collected (i.e., achieve all ranks from 1 up to v).
 *
 * Algorithm:
 *   - Use a boolean vector to mark ranks already achieved.
 *   - Iterate through ranks from 1 upward.
 *   - For each unmarked rank, if we have remaining contests (x > 0), use one to get it.
 *   - If no more contests are available, return the largest rank we could reach before running out.
 *
 * Time Complexity: O(n + N) where n is number of past contests and N = 207
 * Space Complexity: O(N) for the boolean vector of size N
 */

// https://github.com/VaHiX/codeForces/