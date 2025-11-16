// Problem: CF 1779 H - Olympic Team Building
// https://codeforces.com/contest/1779/problem/H
//
// This file implements a randomized constructive/checking approach used to
// determine a subset of athletes satisfying a layered power-of-two selection
// process. The original contest solution uses randomized shuffles and a
// bounded DFS to find subsets of given sizes whose sum is bounded by a
// running threshold. The driver performs a binary search (over candidate
// starting athletes) and uses `check` to validate if a given starting choice
// can lead to a valid full construction.
//
// High-level idea (informal):
// - Sort athletes by skill value. We binary-search the minimal skill value
//   threshold such that picking all athletes with skill >= threshold can be
//   achieved by the layered selection process described in the statement.
// - The `check(x)` routine treats athlete `x` as initially selected, then
//   repeatedly (for i = 1,2,...) tries to choose `2^{i-1}` additional
//   currently-unselected athletes whose total skill does not exceed the
//   current budget `sum`. If at any layer it's impossible to pick such a
//   group, that randomized attempt fails. The function repeats randomized
//   attempts to reduce the probability of false negatives.

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

using namespace std;
const int maxn = 55;
int n;

// Arrays used by DFS/randomized attempts
int id[maxn];  // permutation of indices after sorting by value
int vis[maxn]; // visibility/selected flag for each athlete
int p[maxn];   // randomized order used in DFS choices
long long sum, res,
    T; // sum = current budget, res=DFS best sum, T=bitmask of chosen set
long long a[maxn],
    rec[maxn];        // a[i]=skill value, rec stores chosen bitmasks per layer
mt19937 rnd(time(0)); // random generator

// Comparator for sorting indices by skill value
int cmp(int x, int y) { return a[x] < a[y]; }

// Bounded DFS: try to pick `rst` items from positions [x..n] (in the randomized
// order `p`) such that the total added value `now` does not exceed `sum`.
// - x: current position in the randomized list (1-based)
// - rst: number of items we still need to pick in this layer
// - now: accumulated skill sum of items chosen in this layer so far
// - S: bitmask of chosen athlete indices in this layer (persisted via T)
// The DFS explores choosing or skipping the current candidate. It updates
// global `res` with the best feasible sum found and records the chosen set
// in `T` when a better feasible subset is found.
void dfs(int x, int rst, long long now, long long S) {
  if (now > sum || x + rst > n + 1)
    return; // pruning: exceeded budget or not enough positions left
  if (x == n + 1) {
    // reached end: record feasible solution if better
    if (now > res && (res == -1 || rnd() % 8)) {
      // tie-breaking with randomness to diversify solutions
      res = now;
      T = S;
    }
    return;
  }
  // Option 1: pick current candidate if not already globally selected
  if (vis[p[x]] == 0 && rst > 0) {
    vis[p[x]] = 1;
    dfs(x + 1, rst - 1, now + a[p[x]], S | (1ll << (p[x] - 1)));
    vis[p[x]] = 0;
  }
  // Option 2: skip current candidate
  dfs(x + 1, rst, now, S);
}

// Randomized feasibility check for starting athlete x.
// Repeats several randomized trials (up to 30) to reduce false negatives.
// For each trial:
// - Shuffle order `p` and initialize sum with a[x] (x is preselected).
// - For each layer i (sizes 1,2,4,8,... while <= n): run DFS to pick exactly
//   2^{i-1} new athletes whose total skill <= current sum. If successful,
//   add that sum to `sum` and mark those athletes as permanently selected.
// - If all layers succeed in one trial, `check` returns true. Otherwise after
//   repeated trials, it returns false.
int check(int x) {
  int R = 0;
  for (int tt = 1; tt <= 30 && R == 0; tt++) {
    for (int i = 1; i <= n; i++) {
      vis[i] = 0;
      p[i] = i;
    }
    // Randomize candidate ordering to diversify DFS search
    shuffle(p + 1, p + 1 + n, rnd);
    sum = a[x];
    vis[x] = 1; // x is initially chosen
    int flg = 0;
    for (int i = 1; (1 << i) <= n; i++) {
      res = -1;
      T = 0;
      // Try to pick 2^{i-1} new athletes under current budget
      dfs(1, 1 << (i - 1), 0, 0);
      if (res == -1) {
        flg = 1; // this layer failed
        break;
      }
      // Layer succeeded: add its contribution and mark the chosen athletes
      sum += res, rec[i] = T;
      for (int j = 1; j <= n; j++)
        if ((T >> (j - 1)) & 1)
          vis[j] = 1;
    }
    if (flg == 0)
      R = 1; // success in this trial
  }
  return R;
}

int main() {
  // Read input
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    id[i] = i;
  }
  // Sort indices by skill value (ascending)
  sort(id + 1, id + 1 + n, cmp);

  // Binary search over the sorted indices to find the minimal threshold index
  // such that starting with id[mid] leads to a successful construction.
  int L = 0, R = n + 1;
  while (L + 1 < R) {
    int mid = (L + R >> 1);
    if (check(id[mid]))
      R = mid;
    else
      L = mid;
  }

  // Output binary array marking which athletes have skill >= chosen threshold
  for (int i = 1; i <= n; i++)
    cout << (a[i] >= a[id[R]]);
  cout << '\n';
  return 0;
}
// https://github.com/VaHiX/CodeForces/