// Problem: CF 1973 F - Maximum GCD Sum Queries
// https://codeforces.com/contest/1973/problem/F

/*
Algorithm: 
This code uses a technique involving divisors and prefix sums to efficiently compute the maximum GCD sum over all possible swap configurations within a budget.
The approach processes each divisor of the first elements from both arrays, computes how much cost is needed to set those divisors as GCDs of the final arrays after swaps, and then uses this information to answer queries.

Time Complexity: O(n * sqrt(max(a[i], b[i]))^2 + q * log(q))
Space Complexity: O(sqrt(max(a[i], b[i]))^2 + q)

The algorithm works by:
1. Preprocessing divisors of a[1] and b[1]
2. For each element (except the first one), calculate the GCDs it can contribute to and mark these in a 2D difference array
3. Propagate these contributions using prefix sums
4. Sort and merge results to answer queries in logarithmic time per query

*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
#define N 500000
int i, j, k, n, t, a[N + 50], b[N + 50], c[N + 50];
ll f[805][805], g[805][805];
vector<pair<ll, ll>> v;
set<pair<ll, ll>> s;

void fuck(int t0) {
  map<int, int> mpa, mpb;
  basic_string<int> va, vb, pa, pb;
  int i, j, k, ma, mb;
  // Find all divisors of a[1]
  for (i = 1; i * i <= a[1]; i++)
    if (!(a[1] % i)) {
      va += i;
      if (i * i != a[1])
        va += a[1] / i;
    }
  // Find all divisors of b[1]
  for (i = 1; i * i <= b[1]; i++)
    if (!(b[1] % i)) {
      vb += i;
      if (i * i != b[1])
        vb += b[1] / i;
    }
  sort(va.begin(), va.end());
  sort(vb.begin(), vb.end());
  reverse(va.begin(), va.end());
  reverse(vb.begin(), vb.end());
  ma = va.size();
  mb = vb.size();
  memset(f, 0, sizeof(f));
  memset(g, 0, sizeof(g));
  for (i = 0; i < ma; i++)
    mpa[va[i]] = i;
  for (i = 0; i < mb; i++)
    mpb[vb[i]] = i;
  // Remove redundant divisors from va
  for (i = 0; i < ma - 1; i++) {
    pa += va[i];
    for (j = i + 1; j < ma - 1; j++)
      if (!(va[i] % va[j])) {
        pa.pop_back();
        break;
      }
  }
  // Remove redundant divisors from vb
  for (i = 0; i < mb - 1; i++) {
    pb += vb[i];
    for (j = i + 1; j < mb - 1; j++)
      if (!(vb[i] % vb[j])) {
        pb.pop_back();
        break;
      }
  }
  // Process all elements after first one
  for (i = 2; i <= n; i++) {
    int t1, t2, t3, t4, t5, t6;
    t1 = gcd(a[i], a[1]); // gcd of a[i] and a[1]
    t2 = gcd(b[i], b[1]); // gcd of b[i] and b[1]
    t3 = gcd(b[i], a[1]); // gcd of b[i] and a[1]
    t4 = gcd(a[i], b[1]); // gcd of a[i] and b[1]
    t5 = gcd(t1, t3);     // combined gcd
    t6 = gcd(t2, t4);     // combined gcd
    t1 = mpa[t1];
    t2 = mpb[t2];
    t3 = mpa[t3];
    t4 = mpb[t4];
    t5 = mpa[t5];
    t6 = mpb[t6];
    // Mark changes in difference array
    g[t1][t2]++;
    g[t3][t4]++;
    g[t5][t6]--;
    f[t3][t4] += c[i];   // cost to make the swap
    f[t5][t6] -= c[i];   // undo cost
  }
  // Compute prefix sums for divisors
  for (auto w : pa)
    for (i = 0; i < ma; i++)
      if (!(va[i] % w)) {
        j = mpa[va[i] / w];
        for (k = 0; k < mb; k++) {
          f[j][k] += f[i][k];
          g[j][k] += g[i][k];
        }
      }
  for (auto w : pb)
    for (i = 0; i < mb; i++)
      if (!(vb[i] % w)) {
        j = mpb[vb[i] / w];
        for (k = 0; k < ma; k++) {
          f[k][j] += f[k][i];
          g[k][j] += g[k][i];
        }
      }
  // Collect valid pairs of GCD sums and their required cost
  for (i = 0; i < ma; i++)
    for (j = 0; j < mb; j++) {
      if (g[i][j] == n - 1) // All elements can form this pair of GCD
        v.push_back({f[i][j] + t0, va[i] + vb[j]});
    }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> t;
  for (i = 1; i <= n; i++)
    cin >> a[i];
  for (i = 1; i <= n; i++)
    cin >> b[i];
  for (i = 1; i <= n; i++)
    cin >> c[i];
  // Process two cases: keep initial arrangement, and swap first pair
  fuck(0);
  swap(a[1], b[1]);
  fuck(c[1]);
  // Sort pairs by cost
  sort(v.begin(), v.end());
  ll lst = -1;
  // Insert a sentinel at high cost to simplify processing
  s.insert({1e18, -1});
  // For each unique GCD sum (by cost), keep only the highest one
  for (auto [x, y] : v)
    if (y > lst) {
      lst = y;
      s.insert({x, lst});
    }
  // Process each query
  while (t--) {
    ll sb;
    cin >> sb;
    // Find the best GCD sum that can be achieved with cost ≤ sb
    auto [x, y] = *--s.upper_bound({sb + 1, -1});
    cout << y << ' ';
  }
}


// https://github.com/VaHiX/CodeForces/