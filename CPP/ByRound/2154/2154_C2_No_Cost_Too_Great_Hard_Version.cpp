// Problem: CF 2154 C2 - No Cost Too Great (Hard Version)
// https://codeforces.com/contest/2154/problem/C2

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int t, n;
int big[N] = {1, 1}, a[N], b[N];
int prs[N], dex[N];
int dp[N], mark[N];
vector<int> history;
bool visited[N];
int main() {
  // Sieve of Eratosthenes to precompute smallest prime factor for each number
  for (int i = 2; i < N; ++i)
    big[i] = i;
  for (int i = 2; i < N; ++i) {
    if (i == big[i]) {
      for (int j = i * 2; j < N; j += i) {
        big[j] = i;
      }
    }
  }
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> t;
  while (t-- > 0) {
    cin >> n;
    int evens = 0;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    for (int i = 1; i <= n; ++i)
      cin >> b[i];
    history.clear();
    bool brk = false;
    // Factorize each element of array 'a' and track prime factors
    for (int i = 1; i <= n; ++i) {
      for (int x = a[i]; x > 1; x /= big[x]) {
        int prime = big[x];
        if (prime == big[x / prime]) {
          // Skip if prime factor is repeated (e.g., 4 = 2*2)
          continue;
        } else {
          history.push_back(prime);
          prs[prime] += 1;
          if (prs[prime] >= 2) {
            brk = true;
            break;
          }
        }
      }
    }
    // Early check: if there are already two elements having same prime factor
    if (brk) {
      for (int x : history)
        prs[x] = 0;
      cout << "0\n";
      continue;
    }
    sort(history.begin(), history.end());
    for (int i = 1; i <= n; ++i)
      dex[i] = i;
    // Sort indices by their corresponding cost 'b[i]'
    sort(dex + 1, dex + n + 1, [&](int i, int j) { return b[i] < b[j]; });
    // Special case: if no prime factors found, we need to make two even numbers
    if (history.empty()) {
      cout << (b[dex[1]] + b[dex[2]]) << '\n';
      for (int x : history)
        prs[x] = 0;
      continue;
    }
    ll mincost = LLONG_MAX;
    // Check if any prime factor is 2 - if so, we can make an even number for minimum cost
    if (prs[2]) {
      for (int i = 1; i <= n; ++i) {
        for (auto prx : history) {
          if ((a[i] % prx) != 0) {
            // Cost of making 'a[i]' divisible by 'prx'
            mincost = min(mincost, 1ll * b[i] * (prx - (a[i] % prx)));
            if (prx == 2)
              break;
            if (prx > a[i])
              break;
          }
        }
      }
      for (int x : history)
        prs[x] = 0;
      cout << mincost << '\n';
      continue;
    }
    int i = dex[1];
    int mnai = INT_MAX;
    for (auto prx : history) {
      if ((a[i] % prx) != 0) {
        // Compute minimum cost to make a[i] divisible by prx
        mnai = min(mnai, prx - (a[i] % prx));
      }
    }
    if (mnai < INT_MAX) {
      mincost = min(mincost, 1LL * mnai * b[i]);
    }
    // Consider case of making two elements both even (cost of two smallest elements)
    mincost = min(mincost, 1LL * b[dex[1]] + b[dex[2]]);
    for (int i : history)
      mark[i] = 1;
    for (int i = 1; i <= n; ++i) {
      if (dp[a[i]]) {
        continue;
      }
      // Try to find a way to make existing a[i] part of a pair
      for (int x = a[i] + 1; x > 1; x /= big[x]) {
        if (big[x] == big[x / big[x]])
          continue;
        int pr = big[x];
        if (mark[pr]) {
          // Minimum cost is just the cost of adding 1 to a[i]
          mincost = min(mincost, 1ll * b[i]);
          break;
        }
      }
      dp[a[i]] = 1;
    }
    for (int i = 1; i <= n; ++i)
      dp[a[i]] = 0;
    for (int i : history)
      mark[i] = 0;
    cout << mincost << '\n';
    for (int x : history) {
      prs[x] = 0;
    }
  }
  cout << flush;
}


// https://github.com/VaHiX/CodeForces/