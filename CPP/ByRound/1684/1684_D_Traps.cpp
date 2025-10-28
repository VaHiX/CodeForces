// Problem: CF 1684 D - Traps
// https://codeforces.com/contest/1684/problem/D

/*
D. Traps
Algorithms/Techniques: Greedy, Sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for the array storage

The problem is about minimizing damage when going through traps,
with the option to jump over at most k traps. When jumping, the
next traps get +1 bonus damage. We use a greedy strategy:
- First calculate the base damage assuming no jumps.
- Then sort the effective trap values (base + index) in descending order.
- Jump over the top m traps (where m is number of jumps allowed).
- Calculate the total damage by adjusting for the bonuses applied.
*/

#include <stdio.h>
#include <algorithm>

typedef long long ll;
const int N = 2e5 + 3;
int n, m, a[N];
ll ans;

int main() {
  int T;
  scanf("%d", &T);
  for (; T--;) {
    scanf("%d%d", &n, &m); // Read number of traps and max jumps
    ans = 0; // Initialize total damage
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i); // Read base damages
      ans += a[i];        // Add to base damage sum
      a[i] += i;          // Modify trap value to reflect its effective cost including bonus from jumps
    }
    std::sort(a + 1, a + 1 + n,
              [](const int &a, const int &b) { return a > b; }); // Sort descending by effective value

    for (int i = 1; i <= m; i++)
      ans += i + n - m - a[i]; // Adjust total damage considering bonus from jumps
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/