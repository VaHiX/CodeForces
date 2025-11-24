// Problem: CF 1266 B - Dice Tower
// https://codeforces.com/contest/1266/problem/B

#include <cstdio>
typedef long long ll;
/*
B. Dice Tower

Purpose:
This program determines whether it's possible to construct a tower of dice such that the total number of visible pips equals a given target value. Each die has 6 faces with values 1 through 6, and only certain faces are visible depending on how the dice are stacked.

Algorithm:
- Any die contributes at most 24 visible pips (when all visible faces sum to 24).
- A die can contribute 6 to 24 pips, based on orientation.
- If a tower uses `d` full dice (with 24 visible pips each) and one more partial die with `m` visible pips:
    - We try to express the target as: d * 24 + m where 1 <= m <= 6
    - So we compute d = n / 24 and m = n % 24, then return YES if d >= 1 and 1 <= m <= 6
- This approach works for all valid cases due to mathematical properties of dice configurations.

Time Complexity: O(t), where t is the number of test cases.
Space Complexity: O(1).
*/
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll d = n / 14; // Number of full dice that can contribute to the total
    ll m = (n % 14); // Remaining pips after accounting for full dice
    ll ans = (d >= 1) && (1 <= m) && (m <= 6);
    puts(ans ? "YES" : "NO");
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/