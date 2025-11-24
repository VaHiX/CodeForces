// Problem: CF 1497 B - M-arrays
// https://codeforces.com/contest/1497/problem/B

/*
B. M-arrays
Problem: Divide an array into minimum number of m-divisible arrays, where each array's adjacent elements sum to a multiple of m.

Algorithm:
- Use modular arithmetic to categorize elements by their remainder when divided by m.
- For each remainder r, we determine how many elements have that remainder.
- A key insight is that two numbers with remainders r and (m - r) can be adjacent
  if r + (m - r) = m, which is divisible by m. Special case when r = 0 or r = m/2.

Time Complexity: O(n + m)
Space Complexity: O(m)

Approach:
1. Count frequency of each remainder mod m (store in vector v).
2. For remainder 0, we need at least as many arrays as the count.
3. For other remainders, pairs of elements with remainders r and (m - r) 
   can be grouped together (with a special case handling when r == m - r).
4. The number of groups needed corresponds to how many mismatches there are in counts 
   between remainder r and (m - r), then add 1 for the difference.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> v(m, 0); // Vector to store frequency of remainders
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++v[x % m]; // Count how many elements have each remainder when divided by m
    }
    long cnt(v[0] > 0); // At least one group for elements with remainder 0
    
    // Process pairs of remainders (r, m - r)
    for (long p = 1; p <= m - p; p++) {
      if (p == m - p && v[p] > 0) {
        // Special case: when m is even and p = m / 2
        // Only one element can form a group by itself
        ++cnt;
      } else if (v[p] || v[m - p]) {
        // At least one element in either remainder group
        ++cnt; // One minimum group for this pair

        long rem = v[p] - v[m - p]; // Difference in counts
        if (rem < 0) {
          rem *= -1;
        }
        if (rem > 1) {
          cnt += rem - 1; // Add extra groups needed to balance counts
        }
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/