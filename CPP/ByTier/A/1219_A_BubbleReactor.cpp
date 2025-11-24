// Problem: CF 1219 A - BubbleReactor
// https://codeforces.com/contest/1219/problem/A

/*
Algorithm: 
- Find all cycles in the graph using DFS
- For each cycle, calculate subtree sizes and prefix sums
- Use dynamic programming with bitmask to find the optimal starting position for the cycle
- For each leaf node, calculate the potential if started manually
- Return the maximum sum of potentials

Time Complexity: O(N^2) - The DP solution iterates over all possible start points and computes prefix sums
Space Complexity: O(N) - Storing graph, visited arrays, and DP tables
*/

#include <limits.h>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <ostream>
#include <random>
#include <set>
#include <vector>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define D(x) cerr << #x << " is " << (x) << "\n";
using namespace std;

const int N = 15005, M = 2 * N;
vector<vector<int>> graf(N);
vector<int> inCycle(N), siz(N), dep(N), indeks(N), cycle, visited(N);
vector<ll> pref, pref2, dpp;
int koji, parr;
int trazi;
ll dp2[2][M], sum;
int findCyc(int tr, int par) {
  visited[tr] = 1;
  for (auto p : graf[tr]) {
    if (p == par)
      continue;
    if (visited[p] == 0)
      if (int d = findCyc(p, tr)) {
        if (d == 1)
          inCycle[tr] = 1;
        if (trazi == tr)
          d = 2;
        return d;
      }
    if (visited[p] == 1) {
      trazi = p;
      inCycle[tr] = 1;
      return 1;
    }
  }
  visited[tr] = 2;
  return 0;
}
void dfs(int tr, int par) {
  siz[tr] = 1;
  for (auto p : graf[tr])
    if (p != par && !inCycle[p])
      dfs(p, tr), siz[tr] += siz[p];
  sum += siz[tr];
}
void dfs2(int tr, int par) {
  siz[tr] = 1;
  if (inCycle[tr]) {
    koji = tr;
    parr = par;
    sum += siz[tr];
    return;
  }
  for (auto p : graf[tr])
    if (p != par)
      dep[p] = dep[tr] + 1, dfs2(p, tr), siz[tr] += siz[p];
  sum += siz[tr];
}
vector<ll> dpsol(M);
int main() {
  int n, a, b;
  scanf("%i", &n);
  for (int i = 0; i < n; i++)
    scanf("%i %i", &a, &b), graf[a].pb(b), graf[b].pb(a);
  findCyc(0, 0);
  for (int i = 0; i < n; i++)
    if (inCycle[i] == 1)
      cycle.pb(i);
  for (auto p : cycle) {
    sum = 0;
    dfs(p, p);
    dpp.pb(siz[p]);
    pref.pb(siz[p]);
    pref2.pb(sum - siz[p]);
  }
  for (int i = 0; i < (int)cycle.size(); i++)
    dpp.pb(dpp[i]), pref.pb(pref[i]), pref2.pb(pref2[i]), indeks[cycle[i]] = i;
  int m = dpp.size();
  for (int i = 1; i < m; i++)
    pref[i] += pref[i - 1], pref2[i] += pref2[i - 1];
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < M; j++)
      dp2[i][j] = LLONG_MAX / 2;
  for (int i = m - 1; i >= 0; i--)
    for (int j = i; j < m; j++) {
      if (i == j) {
        dp2[i & 1][j] = dpp[i];
        continue;
      }
      if (dp2[(i + 1) & 1][j] >= dp2[i & 1][j - 1])
        dp2[i & 1][j] = dp2[(i + 1) & 1][j];
      else
        dp2[i & 1][j] = dp2[i & 1][j - 1];
      dp2[i & 1][j] += pref[j];
      if (i)
        dp2[i & 1][j] -= pref[i - 1];
      if (j == i + m / 2 - 2)
        dpsol[i] = dp2[i & 1][j];
    }
  int i = cycle[0];
  sum = 0;
  dep[i] = 1;
  dfs2(i, i);
  ll sol = sum;
  int ind = indeks[i];
  sol += n - 1;
  sol += dpsol[ind + 1];
  sol += pref2[ind + m / 2 - 1];
  if (ind)
    sol -= pref2[ind - 1];
  ll total = sol;
  for (i = 0; i < n; i++) {
    if (graf[i].size() == 1) {
      sum = 0;
      dep[i] = 1;
      dfs2(i, i);
      sol = sum;
      int ind = indeks[koji], ostali = n - siz[i];
      sol += (ll)ostali * dep[koji];
      sol += dpsol[ind + 1];
      sol += pref2[ind + m / 2 - 1];
      if (ind)
        sol -= pref2[ind - 1];
      if (sol <= total)
        continue;
      sum = 0;
      dfs(parr, parr);
      sol -= sum;
      total = max(total, sol);
    }
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/