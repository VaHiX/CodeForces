// Problem: CF 2028 F - Alice's Adventures in Addition
// https://codeforces.com/contest/2028/problem/F

/*
F. Alice's Adventures in Addition
Algorithms/Techniques: Bitset optimization with sliding window approach for expression evaluation.
Time Complexity: O(n * log(m) * 16), where n is the size of array, m is target value, and 16 represents the sliding window size.
Space Complexity: O(16 * M), where M = 10^4 + 2, constant due to fixed-size bitsets.

Note that the memory limit is unusual.
The Cheshire Cat has a riddle for Alice: given
n
integers
a
1
,
a
2
,…,
a
n
and a target
m
, is there a way to insert
+
and
×
into the circles of the expression
a
1
∘
a
2
∘⋯∘
a
n
=m
a
∘
a
∘
∘
a
=
m
to make it true? We follow the usual order of operations:
×
is done before
+
.
Although Alice is excellent at chess, she is not good at math. Please help her so she can find a way out of Wonderland!
*/
#include <bitset>
#include <iostream>

#pragma GCC optimize("Ofast", "unroll-loops", "inline")
#define ll long long
#define pb push_back
#define pii pair<int, int>
#define MP make_pair
#define fi first
#define se second
using namespace std;
const int N = 2e5 + 60, M = 1e4 + 2, mod = 998244353;
bitset<M> b[16], f, g, z; // b: sliding window of bitsets, f: current set of achievable values, g: cumulative set, z: zero handling
int p[16], o;             // p: powers stored in buffer, o: current index in buffer
int a[N], n, m;
inline int lst(int x) { return (x + 15) & 15; } // helper to get previous index mod 16 (circular buffer)
void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 0; i < 16; i++)
    b[i].reset(), p[i] = -1;
  g.reset(), z.reset();
  f.reset();
  g.set(0), o = 0, b[o].set(0), p[o] = a[1];
  if (!a[1])
    z.set(0); // special handling for zero at start
  for (int i = 1; i <= n; i++) {
    f.reset(); // reset current achievable values
    // Iterate through buffer from current pointer backward, computing possible combinations using multiplication
    for (int u = o, k = p[o]; lst(u) != o && k > 0 && k <= m;
         u = lst(u), k = k * p[u])
      f |= b[u] << k; // shift and OR to update set of achievable sums
    f |= z; // include values that can come from previous zeros
    if (i != n) {
      if (p[o] == 1)
        p[o] = a[i + 1], b[o] |= f; // overwrite if power is 1
      else
        o = (o + 1) & 15, p[o] = a[i + 1], b[o] = f; // move to next position in buffer
      g |= f; // accumulate all previous achievable values
      if (!a[i + 1])
        z = g; // update zero tracking with cumulative set
    }
  }
  cout << (f[m] ? "YES" : "NO") << '\n'; // output result for target m
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/