// Problem: CF 1836 A - Destroyer
// https://codeforces.com/contest/1836/problem/A

/*
 * Problem: Destroyer
 * 
 * Purpose:
 *   Determine if a set of robots can be arranged in one or more lines such that
 *   each robot's reported number of robots in front matches the actual count.
 * 
 * Algorithm:
 *   - For each test case, we count how many robots report each value (0 to 99).
 *   - Then, we check if this count forms a non-decreasing sequence.
 *     This is because in any valid line arrangement, if a robot reports 'k',
 *     then there must be at least k other robots before it. So the number of
 *     robots reporting 0 should be >= number reporting 1, and so forth.
 * 
 * Time Complexity:
 *   O(N) per test case, where N is the number of robots. Counting takes O(N),
 *   and checking the non-decreasing property also takes O(N).
 * 
 * Space Complexity:
 *   O(1) additional space, since we use a fixed-size vector of size 101.
 */

#include <cstdio>
#include <vector>
int main() {
  const int N = 101;
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(N, 0); // Count how many robots report each value
    bool res(true);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++v[x]; // Increment count for the reported number
    }
    for (long p = 1; res && p < N; p++) {
      if (v[p - 1] < v[p]) { // If a smaller index has fewer reports than larger one, invalid
        res = false;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/