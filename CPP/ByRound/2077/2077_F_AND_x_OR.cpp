// Problem: CF 2077 F - AND x OR
// https://codeforces.com/contest/2077/problem/F

/*
F. AND x OR
Algorithms/Techniques:
- Subset convolution (SOS - Sum over Subsets) using two variants: sos and sos2
- Greedy optimization with bit operations and sorting
- Modular arithmetic for large numbers

Time Complexity: O(n * log(m) + m * log(m))
Space Complexity: O(m)

The problem reduces to finding the minimum number of increments needed to make
two arrays a and b such that there exists a sequence of bitwise operations
(a[i] &= x, a[j] |= x) that transforms array a into array b.
This is equivalent to checking if for each bit position, the set of values
in a can be transformed to those in b through OR/AND operations.
To solve it:
1. Preprocess arrays to identify unique occurrences and their subset counts.
2. Use SOS transform to count subsets efficiently.
3. Apply greedy condition checks on these counts.
*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define ll long long
#define pb push_back
#define mp make_pair
#define vt vector
using namespace std;

ll powmod(ll base, ll exponent, ll mod) {
  ll ans = 1;
  if (base < 0)
    base += mod;
  while (exponent) {
    if (exponent & 1)
      ans = (ans * base) % mod;
    base = (base * base) % mod;
    exponent /= 2;
  }
  return ans;
}

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

const int INF = 2e9;
const ll INFLL = 4e18;
const int mod = 998244353;
const int ul = 1e6 + 1;

// Subset convolution (Sum over Subsets)
vt<int> sos(const vt<int> &a) {
  int n = a.size();
  vt<int> ans = a;
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += (i << 1)) {
      for (int k = j; k < j + i; k++) {
        ans[k + i] += ans[k]; // accumulate subset sums
      }
    }
  }
  return ans;
}

// Another variant of SOS
vt<int> sos2(const vt<int> &a) {
  int n = a.size();
  vt<int> ans = a;
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += (i << 1)) {
      for (int k = j; k < j + i; k++) {
        ans[k] += ans[k + i]; // accumulate subset sums in reverse
      }
    }
  }
  return ans;
}

void solve() {
  int n, m;
  cin >> n >> m;
  vt<int> a(n), b(n);
  for (int &i : a)
    cin >> i;
  for (int &i : b)
    cin >> i;

  // Find least power of two greater than or equal to m
  int gg = 1;
  while (gg <= m)
    gg <<= 1;

  vt<int> occ_b(gg); // count occurrences of elements in b
  for (int &i : b) {
    if (++occ_b[i] > 1) { // if any duplicate exists, solution is impossible
      cout << "0\n";
      return;
    }
  }

  vt<int> sos_b = sos(occ_b); // compute SOS transform of occurrence array
  vt<int> temp = sos2(occ_b); // compute SOS inverse or variant

  // Combine the two transformations
  for (int i = 0; i < gg; i++)
    sos_b[i] += temp[i]; // add results for better subset counting

  int ans = m, mn = -INF;
  ll manhattan = 0;
  
  // Calculate Manhattan distance as an initial approximation
  for (int i = 0; i < n; i++)
    manhattan += abs(a[i] - b[i]);
  if (ans > manhattan)
    ans = manhattan;

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  // Main logic to check constraints
  for (int i = 0; i < gg; i++) {
    if (occ_b[i] > 0 && sos_b[i] > 2 * occ_b[i]) { // impossible case: too many subsets
      cout << "0\n";
      return;
    }
    if (sos_b[i] > 0) {
      if (sos_b[i] > 1 || (i & mn) != mn) // greedy condition check
        ans = min(ans, i - mn);
    }
    if (occ_b[i] > 0)
      mn = i; // track maximum
  }
  
  cout << ans << "\n";
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/