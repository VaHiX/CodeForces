// Problem: CF 1743 A - Password
// https://codeforces.com/contest/1743/problem/A

#include <cstdio>
int T, n;
int main() {
  // Flowerbox:
  // Purpose: Calculate the number of valid 4-digit passwords under constraints.
  // Algorithm: The password uses exactly two distinct digits, each appearing exactly twice.
  // We are given n digits that are definitely NOT used in the password.
  // Available digits = 10 - n
  // Number of ways to pick 2 distinct digits from available = C(available, 2)
  // Each pair can be arranged in 4!/(2!*2!) = 6 ways (since we have two pairs of identical digits)
  // So total = C(available, 2) * 6
  // Time Complexity: O(1) per test case (constant time operations)
  // Space Complexity: O(1) (only using a few variables)
  
  for (scanf("%d", &T); T--;)
    for (scanf("%d", &n), printf("%d\n", 3 * (10 - n) * (9 - n)); n--;)
      scanf("%*d");
}


// https://github.com/VaHiX/codeForces/