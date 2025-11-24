// Problem: CF 2035 E - Monster
// https://codeforces.com/contest/2035/problem/E

/*
E. Monster
Algorithm: Greedy + Math + Optimization
Time Complexity: O(sqrt(z) + z/k)
Space Complexity: O(1)

Problem: Given a monster with z health and a weapon that starts with damage 0,
you can either increase the weapon's damage by 1 (costing x coins), or attack
the monster (costing y coins per attack). You cannot increase damage more than k times consecutively.
Goal is to find minimum coins to defeat the monster.

Approach:
- Enumerate possible number of damage increases up to sqrt(z).
- For each valid increment count, calculate minimal cost using greedy strategy.
- Also apply optimization for larger values by increasing damage in chunks of k.
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

using namespace std;
typedef long long ll;
#define int long long
#define endl '\n'
typedef pair<int, int> PII;

void solve() {
  int x, y, z, k;
  cin >> x >> y >> z >> k;
  int ans = x + y * z; // Worst case: increase damage by 1 and attack z times
  int z1 = z, sum = 0, sq = sqrt(z), d;

  // Loop through possible number of damage increases
  for (int i = 1; i <= sq; i++) {
    sum += x;
    if (i % k == 0) { // If we've increased damage k times consecutively, increment cost
      sum += y;
      z1 -= i;
    }
    d = z1 / i; // Number of attacks needed to finish with current damage i
    if (z1 % i != 0)
      d++; // Adjust for remainder
    ans = min(ans, sum + d * y);
  }

  int ind = sq / k * k; // Find largest multiple of k less than or equal to sqrt(z)
  sum -= (sq - ind) * x; // Remove excess increments beyond last valid group

  if (ind != 0) {
    d = z1 / ind;
    if (z1 % ind != 0)
      d++;
  }

  // Continue optimizing for higher damage values
  while (d > 0) {
    int a = z1 / d; // Calculate number of damage increases needed to achieve a damage level
    if (z1 % d != 0)
      a++;
    if (a - ind > k) { // If we exceed the allowed consecutive increments
      ind += k;
      z1 -= ind;
      sum += y + x * k; // Increment cost and add k more increases
      d--;
      continue;
    }
    ans = min(ans, max(a - ind, 0ll) * x + d * y + sum);
    d--;
  }

  cout << ans << endl;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/