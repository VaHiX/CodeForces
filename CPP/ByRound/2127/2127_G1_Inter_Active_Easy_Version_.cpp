/*
 * Problem URL : https://codeforces.com/problemset/problem/2127/G1
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;

const int MXN = 1005;

int n, k;
int p[MXN], qarr[MXN];
bool used[MXN];

// ask the judge with current qarr and read the reply
int ask() {
  cout << "? ";
  for (int i = 1; i <= n; i++)
    cout << qarr[i] << ' ';
  cout << endl; // endl flushes (required)
  int r;
  if (!(cin >> r))
    exit(0); // safety
  if (r == -1)
    exit(0); // per statement
  return r;
}

// print final permutation
void answer() {
  cout << "! ";
  for (int i = 1; i <= n; i++)
    cout << p[i] << ' ';
  cout << endl;
}

// build a permutation q where:
// - value `fix` is placed at position k
// - the candidates in `good` are placed in A∪C (sides around k)
// - the candidates in `bad` are placed in B (middle, right of k)
// remaining positions are filled arbitrarily
void build_query(int fix, vector<int> good, vector<int> bad) {
  fill(used + 1, used + n + 1, false);
  fill(qarr + 1, qarr + n + 1, 0);

  qarr[k] = fix;
  used[fix] = true;

  // fill left side [1..k-1] from good (back)
  for (int i = 1; i < k && !good.empty(); i++) {
    qarr[i] = good.back();
    used[qarr[i]] = true;
    good.pop_back();
  }
  // fill rightmost side [n..] from remaining good
  for (int i = n; !good.empty(); i--) {
    qarr[i] = good.back();
    used[qarr[i]] = true;
    good.pop_back();
  }
  // fill middle [k+1..] with bad
  for (int i = k + 1; !bad.empty(); i++) {
    qarr[i] = bad.back();
    used[qarr[i]] = true;
    bad.pop_back();
  }
  // fill any leftover spots with remaining numbers
  vector<int> rest;
  for (int v = 1; v <= n; v++)
    if (!used[v])
      rest.push_back(v);
  for (int i = 1; i <= n; i++)
    if (qarr[i] == 0) {
      qarr[i] = rest.back();
      rest.pop_back();
    }
}

// reverse q except position k
void rev_except_k() {
  vector<int> v;
  v.reserve(n - 1);
  for (int i = 1; i <= n; i++)
    if (i != k)
      v.push_back(qarr[i]);
  for (int i = 1, j = (int)v.size() - 1; i <= n; i++)
    if (i != k) {
      qarr[i] = v[j--];
    }
}

void solve_one() {
  cin >> n;
  // choose k ≈ (n+1)/4 + 1 (editorial choice)
  k = (n + 1) / 4 + 1;
  cout << k << endl; // not a query

  for (int target = 1; target <= n; target++) {
    // we will find predecessor j with p[j] = target
    vector<int> cand;
    cand.reserve(n - 1);
    for (int v = 1; v <= n; v++)
      if (v != target)
        cand.push_back(v);

    // binary-search using the “query + reversed query” trick
    while ((int)cand.size() > 1) {
      // we want to split cand into:
      //   - put some into A∪C (good) and the rest into B (bad)
      // keep B size <= capacity (n - (2*k - 1))
      int capB = n - (2 * k - 1);
      int takeBad = min((int)((cand.size() + 1) / 2), capB);
      int keepGood = (int)cand.size() - takeBad;

      vector<int> good(cand.begin(), cand.begin() + keepGood);
      vector<int> bad(cand.begin() + keepGood, cand.end());

      build_query(target, good, bad);
      int a = ask();
      rev_except_k();
      int b = ask();

      // For all edges except the one entering `target`,
      // total contribution over (q, reversed q) is exactly 1.
      // The edge *into* `target` contributes:
      //   - 0 if its tail ends up in B
      //   - 1 if its tail ends up in A∪C
      // Thus, a+b == n-1  -> predecessor in A∪C (keep `good`)
      //       a+b == n-2  -> predecessor in B    (keep `bad`)
      if (a + b == n - 1) {
        cand = move(good);
      } else {
        cand = move(bad);
      }
    }
    int pred = cand.back(); // unique j with p[j] = target
    p[pred] = target;
  }
  answer();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  if (!(cin >> T))
    return 0;
  while (T--)
    solve_one();
  return 0;
}