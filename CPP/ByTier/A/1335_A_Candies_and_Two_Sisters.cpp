// Problem: CF 1335 A - Candies and Two Sisters
// https://codeforces.com/contest/1335/problem/A

/*
Code Purpose:
This program calculates the number of ways to distribute 'n' indistinguishable candies between two sisters, Alice and Betty, such that:
- Alice gets more candies than Betty (a > b)
- Both sisters get at least one candy (a > 0, b > 0)
- All candies are distributed (a + b = n)

Algorithm:
The problem reduces to counting integer pairs (a, b) where:
1. a + b = n
2. a > b > 0
3. a, b are integers

By substituting b = n - a into the inequality a > b:
a > n - a => 2a > n => a > n/2

Also, since a > 0 and b > 0:
a < n (because b = n - a > 0 => a < n)
a > 0

So: n/2 < a < n and a is integer.
Thus: a ranges from floor(n/2) + 1 to n - 1 => number of valid values = (n - 1) / 2

For even n: n/2 is integer, so a can be from n/2 + 1 to n - 1 = (n - 2) / 2 values
For odd n: n/2 is not integer, so a can be from (n+1)/2 to n - 1 = (n - 1) / 2 values
This simplifies to (n - 1) / 2 for both cases.

Time Complexity: O(1) - constant time per test case
Space Complexity: O(1) - constant space usage
*/

#include <iostream>
int T, n;
int main() {
  for (std::cin >> T; T--; endl(std::cout << ((n - 1) / 2)))
    std::cin >> n;
}


// https://github.com/VaHiX/CodeForces/