// Problem: CF 2111 F - Puzzle
// https://codeforces.com/contest/2111/problem/F

/*
F. Puzzle
time limit per test2 seconds
memory limit per test512 megabytes

Algorithm/Techniques:
- Mathematical analysis to determine the shape based on perimeter-to-area ratio.
- Constructive algorithm using grid-based arrangement of pieces.
- Use of GCD to reduce fraction and then scale up for valid integer dimensions.
- Iterative computation to find minimal number of pieces needed.
- Output coordinates in a way that ensures connectivity.

Time Complexity: O(1) per test case (since p, s are bounded by 50).
Space Complexity: O(1) (no extra space beyond the output, which is not counted).

*/

#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;
#define ll long long
#define pb push_back
#define inf 0x3f3f3f3f3f3f3f3f
#define N 200005
#define F first
#define S second
typedef pair<ll, ll> pll;
int T, p, s;

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &p, &s);
    int g = __gcd(p, s); // Reduce fraction to lowest terms
    p /= g, s /= g;
    if (p % 2 == 1) // If p is odd, multiply both by 2 to make p even
      p *= 2, s *= 2;
    int x = p / 4, y = p / 2 - x, cnt = 0; // Initial guess for grid dimensions
    for (cnt = 2; x * y < s * (cnt - 1); cnt++) // Increase until area is sufficient
      x = p * cnt / 4, y = p * cnt / 2 - x;
    p *= (cnt - 1), s *= (cnt - 1); // Scale up actual values
    if (s < x + y - 1) { // Check if perimeter constraint can be met
      printf("-1\n");
      continue;
    }
    printf("%d\n", s);
    s -= (x + y - 1); // Adjust s to fit into grid structure

    // Output horizontal pieces
    for (int i = 1; i < x; i++)
      printf("%d %d\n", i, 0);
    // Output vertical pieces
    for (int i = 0; i < y; i++)
      printf("%d %d\n", 0, i);
    // Fill in remaining internal positions to meet perimeter constraint
    for (int i = 1; i < x; i++)
      for (int j = 1; j < y; j++)
        if (s)
          s--, printf("%d %d\n", i, j);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/