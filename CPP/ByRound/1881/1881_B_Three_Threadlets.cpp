// Problem: CF 1881 B - Three Threadlets
// https://codeforces.com/contest/1881/problem/B

/*
B. Three Threadlets
Algorithms/Techniques: Mathematical analysis, brute force over possible divisors.
Time Complexity: O(1) per test case (since we check up to 3000 possible values for m, and each check takes constant time)
Space Complexity: O(1)

The problem asks whether we can make three threadlets of equal length by performing at most 3 operations,
where each operation cuts one threadlet into two positive integer-length threadlets.

Key insight:
- Each operation increases the number of threadlets by 1 (from 3 to 6 maximum).
- We can only cut threadlets into smaller positive integers.
- If all threadlets are divisible by some value m, and total number of threadlets after cutting is <= 6,
  then it's possible.

Approach:
1. For each test case, iterate over potential equal lengths (divisors) m which divides a, b, c.
2. If a/m + b/m + c/m <= 6 (total threadlets after full division)
3. Check if all original lengths are divisible by m.
4. If true for any such m, output YES.
5. Optimization: We only need to check divisors up to around 3000 because with at most 3 cuts,
   the final number of threadlets won't exceed 6, so maximum value of m is bounded.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    long m(a);
    m = (m < b) ? m : b;        // Find minimum of a, b, c
    m = (m < c) ? m : c;
    bool res = ((a / m) + (b / m) + (c / m) <= 6) && (a % m == 0) &&
               (b % m == 0) && (c % m == 0);
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/