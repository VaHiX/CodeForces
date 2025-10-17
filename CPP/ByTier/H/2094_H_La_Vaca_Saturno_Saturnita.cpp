// Problem: CF 2094 H - La Vaca Saturno Saturnita
// https://codeforces.com/contest/2094/problem/H

/*
 * Problem: Saturnita's Function Evaluation
 *
 * Purpose:
 *   This code efficiently computes a function f(k, a, l, r) for multiple queries,
 *   where f(k, a, l, r) sums k divided by elements in array a from index l to r,
 *   repeatedly dividing k by a[i] while it's divisible.
 *
 * Algorithm/Techniques:
 *   - Offline processing with segment-style traversal
 *   - Preprocessing of divisors for numbers up to 10^5
 *   - Efficient data structure using vectors for each element's positions
 *   - Lazy propagation style updates using queries and precomputed divisor lists
 *
 * Time Complexity: O(N * log(N) + Q * sqrt(N) * log(N))
 * Space Complexity: O(N * log(N) + N)
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define F first
#define S second
#define all(x) x.begin(), x.end()
#define pb push_back
#define FIO                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const int N = 1e5 + 7;
vector<int> d[N], p[N]; // d[i] stores divisors of i; p[i] stores indices where value i appears
vector<pii> qu[N];      // qu[i] stores queries starting at position i
void task() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n), ri(q);
  vector<ll> res(q);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < q; i++) {
    int x, l;
    cin >> x >> l >> ri[i]; // read query parameters
    l--;
    ri[i]--;
    qu[l].pb({i, x});       // store query at starting index l
  }
  for (int i = n - 1; i >= 0; i--)
    p[a[i]].pb(i);          // record positions of each number in reverse order
  for (int i = 0; i < n; i++) {
    p[a[i]].pop_back();     // remove processed position from list

    for (auto x : qu[i]) {  // process all queries starting at index i
      while (x.S % a[i] == 0) // reduce x.S by factors of current element a[i]
        x.S /= a[i];
      int r = ri[x.F] + 1;   // final right bound of query
      for (int y : d[x.S])   // check all divisors of reduced x.S
        if (!p[y].empty())   // if there's a previous occurrence of divisor y
          r = min(r, p[y].back()); // update minimum end position from previous occurrences

      res[x.F] += x.S * (r - i); // accumulate the contribution to answer
      if (r <= ri[x.F])
        qu[r].pb(x);         // schedule delayed query for position r
    }
    qu[i].clear();          // clear processed queries at current index
  }
  for (int i = 0; i < q; i++)
    cout << res[i] << "\n";
}
int main() {
  FIO;
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i)
      d[j].pb(i);         // precompute divisors for all numbers up to N
  }
  int tt;
  cin >> tt;
  while (tt--)
    task();
  return 0;
}


// https://github.com/VaHiX/codeForces/