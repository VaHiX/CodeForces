// Problem: CF 1928 D - Lonely Mountain Dungeons
// https://codeforces.com/contest/1928/problem/D

/*
 * Problem: Lonely Mountain Dungeons
 * 
 * Approach:
 * - For each possible number of squads k (from 1 to max creature count),
 *   calculate the maximum strength achievable.
 * - For a given number of squads k, we want to distribute creatures optimally
 *   such that the number of pairs between different squads is maximized.
 * - The contribution to strength from each race i is calculated as:
 *   pairs between squads = C[i] * (C[i] - 1) / 2 - (number of same-squad pairs)
 * - This is done by considering how to optimally distribute C[i] creatures into k squads.
 * - We precompute for each k (number of squads), the sum of all valid pairs across all races.
 * - Then, for each k from 1 to max_count, compute total strength as:
 *   (total_pairs * b) - ((k-1) * x)
 * 
 * Time Complexity: O(max_count * max_count) per test case,
 *                  where max_count is the maximum number of creatures in any race.
 * 
 * Space Complexity: O(max_count) for storage of mx_pairs array.
 */

#include <algorithm>
#include <iostream>

using namespace std;
#define LL long long
#define mod 1000000007ll
#define PI acos(-1.0)
#define set0(ar) memset(ar, 0, sizeof ar)
#define setinf(ar) memset(ar, 126, sizeof ar)
inline constexpr LL bigmod(LL p, LL e, LL M) {
  LL r = 1;
  for (; e > 0; e >>= 1, p = (p * p) % M)
    if (e & 1)
      r = (r * p) % M;
  return r;
}
inline constexpr LL modinverse(LL a, LL M) { return bigmod(a, M - 2, M); }
int C[200001];
LL mx_pairs[200001];
LL nc2(LL n) { return (n * (n - 1)) / 2ll; }
void solve() {
  int n, b, x;
  cin >> n >> b >> x;
  for (int i = 0; i < n; i++)
    cin >> C[i];
  sort(C, C + n);
  for (int i = 1; i <= C[n - 1]; i++)
    mx_pairs[i] = 0;
  LL pref_sum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= C[i]; j++) {
      LL tot = nc2(C[i]); // Total pairs in current race
      LL g = C[i] / j;    // Number of creatures in each squad
      tot -= nc2(g) * j;  // Subtract pairs within squads
      LL r = C[i] % j;    // Remaining creature count
      tot -= g * r;       // Subtract intra-squad pairs for remaining
      mx_pairs[j] += tot; // Aggregate contribution for k squads
      if (i > 0 && j > C[i - 1])
        mx_pairs[j] += pref_sum; // Add previous race's contribution
    }
    pref_sum += nc2(C[i]); // Prefix sum updated
  }
  LL res = 0;
  for (int i = 1; i <= C[n - 1]; i++) {
    res = max(res, mx_pairs[i] * (LL)b - (LL)(i - 1) * (LL)x); // Compute max strength
  }
  cout << res << "\n";
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int T = 1;
  cin >> T;
  for (int ts = 1; ts <= T; ts++) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/