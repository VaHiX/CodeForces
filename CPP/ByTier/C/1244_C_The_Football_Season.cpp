// Problem: CF 1244 C - The Football Season
// https://codeforces.com/contest/1244/problem/C

/*
Purpose: 
This program determines the number of wins (x), draws (y), and losses (z) for a football team
given the total number of games (n), total points (p), points for a win (w), and points for a draw (d).
It uses a mathematical approach to solve the system of equations:
x * w + y * d = p
x + y + z = n
where x, y, z are non-negative integers.

Algorithm:
1. Iterate through possible numbers of draws (y) up to a reasonable limit.
2. For each y, check if (p - y * d) is divisible by w to get a valid number of wins (x).
3. Ensure that x + y <= n to keep z non-negative.
4. If a valid triple (x, y, z) is found, output it.
5. If no valid triple exists, output -1.

Time Complexity: O(d) where d is the number of points for a draw. 
Space Complexity: O(1) - only using a constant amount of extra space.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll n, m, w, d;
  scanf("%lld %lld %lld %lld", &n, &m, &w, &d);
  ll x(-1);
  // Loop through possible draws (y) up to a safe limit
  for (ll y = 0; y < 100000 && y * d <= m; y++) {
    // Check if remaining points after draws can be evenly distributed as wins
    if ((m - y * d) % w == 0 && y + (m - y * d) / w <= n) {
      x = (m - y * d) / w; // Calculate number of wins
      printf("%lld %lld %lld\n", x, y, n - x - y); // Output result
      break;
    }
  }
  if (x < 0) {
    puts("-1"); // No valid solution found
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/