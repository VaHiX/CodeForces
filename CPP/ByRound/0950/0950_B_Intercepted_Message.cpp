// Problem: CF 950 B - Intercepted Message
// https://codeforces.com/contest/950/problem/B

/*
 * Problem: B. Intercepted Message
 * 
 * Purpose: Determine the maximum number of files in an archive based on two intercepted message streams.
 *          Both messages are assumed to contain the same archive, but files may be split into different block combinations.
 *          The algorithm uses a two-pointer technique to match cumulative sums of blocks from both messages.
 * 
 * Algorithm: Two-pointer approach
 * 
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 * 
 * Techniques:
 *   - Prefix sums are precomputed to quickly calculate cumulative block sizes
 *   - Two pointers to traverse both prefix sum arrays and match cumulative sums
 *   - Greedy matching of file sizes by advancing the pointer of the smaller prefix sum
 */

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> x(n + 1, 0);
  for (long p = 1; p <= n; p++) {
    long u;
    scanf("%ld", &u);
    x[p] = x[p - 1] + u;  // Compute prefix sum for first message
  }
  std::vector<long> y(m + 1, 0);
  for (long p = 1; p <= m; p++) {
    long u;
    scanf("%ld", &u);
    y[p] = y[p - 1] + u;  // Compute prefix sum for second message
  }
  long cnt(0), indx(1), indy(1);
  while (indx <= n && indy <= m) {
    if (x[indx] == y[indy]) {
      // Found a matching file size, increment counters and file count
      ++indx;
      ++indy;
      ++cnt;
    } else if (x[indx] < y[indy]) {
      // First prefix sum is smaller, advance first pointer to try larger block
      ++indx;
    } else if (x[indx] > y[indy]) {
      // Second prefix sum is smaller, advance second pointer to try larger block
      ++indy;
    }
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/