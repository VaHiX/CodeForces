// Problem: CF 2043 B - Digits
// https://codeforces.com/contest/2043/problem/B

/*
B. Digits
time limit per test1 second
memory limit per test256 megabytes

Algorithm/Techniques: Mathematical observation and case analysis.
The problem asks to determine which odd digits (from 1 to 9) divide a number formed by repeating digit d exactly n! times.
Key observations:
- A number is divisible by an odd digit if the number itself is divisible by that digit.
- For very large numbers (like those with n! digits), direct computation isn't feasible.
- Instead, we use mathematical properties and divisibility rules.

Time Complexity: O(1) per test case — constant time due to precomputed conditions.
Space Complexity: O(1) — only a fixed-size vector is used.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    int d;
    scanf("%ld %d", &n, &d);
    std::vector<int> v(1, 1); // Always include 1
    if (d == 3 || d == 6 || d == 9 || n >= 3) {
      v.push_back(3); // Include 3 under these conditions
    }
    if (d == 5) {
      v.push_back(5); // Include 5 only when d is 5
    }
    if (d == 7 || n >= 3) {
      v.push_back(7); // Include 7 under these conditions
    }
    if (d == 9 || (d == 3 && n >= 3) || (d == 6 && n >= 3) || (n >= 6)) {
      v.push_back(9); // Include 9 under these conditions
    }
    for (int d : v) {
      printf("%ld ", d);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/