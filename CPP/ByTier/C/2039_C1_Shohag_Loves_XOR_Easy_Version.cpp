// Problem: CF 2039 C1 - Shohag Loves XOR (Easy Version)
// https://codeforces.com/contest/2039/problem/C1

/*
C1. Shohag Loves XOR (Easy Version)
Time Complexity: O(x * log(m)) per test case in worst case, but optimized in practice due to early exits and small x values.
Space Complexity: O(1)

Algorithms/Techniques:
- Brute force over all possible values of p from 1 to x-1
- For each p, compute y = x ^ p
- Check if y <= m and whether either x % p == 0 or y % p == 0
- Count such valid pairs

Input:
- t: number of test cases
- For each test case: x and m (integers)

Output:
- For each test case: count of valid y values where 1 <= y <= m, x != y, and x^y is divisible by either x or y.

Example Input:
5
6 9
5 7
2 3
6 4
4 1

Example Output:
3
2
1
1
0
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, m;
    scanf("%ld %ld", &x, &m);
    long cnt(0);
    for (long p = 1; p < x; p++) {           // Iterate through all possible divisors p
      long y = x ^ p;                        // Compute y as XOR of x and p
      if (y > m) {                           // Skip if y exceeds m
        continue;
      }
      cnt += ((x % p == 0) || (y % p == 0)); // Increment counter if p divides x or y
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/