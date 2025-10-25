// Problem: CF 1475 B - New Year's Number
// https://codeforces.com/contest/1475/problem/B

/*
B. New Year's Number
Algorithms/Techniques: Mathematical analysis, modular arithmetic
Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1)

The problem asks whether a given number n can be expressed as a sum of 
some number of 2020s and 2021s. 

Key insight:
Let x = number of 2020s, y = number of 2021s.
Then: n = 2020 * x + 2021 * y
Rearranging: n = 2020 * (x + y) + y
So: n % 2020 = y

If we divide n by 2020, we get:
- x = n / 2020 (integer division)
- y = n % 2020 (remainder)

For a valid solution to exist, y must be such that we can use exactly y copies of 2021 
and (x - y) copies of 2020. Since we are not allowed to have negative counts, we need:
- x >= y (we should not use more 2021s than we have 2020s to compensate for)
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    const long A = 2020;  // Base value
    long n;
    scanf("%ld", &n);
    long x = n / A;       // Quotient: number of 2020s we can use in the best case
    long y = n % A;       // Remainder: how many extra units we need to cover with 2021s
    puts(x >= y ? "YES" : "NO");  // If we have enough 2020s to make up for remainder, answer is YES
  }
}


// https://github.com/VaHiX/codeForces/