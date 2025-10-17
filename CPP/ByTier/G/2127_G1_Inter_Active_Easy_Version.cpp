// Problem: CF 2127 G1 - Inter Active (Easy Version)
// https://codeforces.com/contest/2127/problem/G1

/*
 * Problem: Inter Active (Easy Version)
 * Description:
 *   Given a hidden permutation p of length n (where p_i != i for all i),
 *   find the permutation using interactive queries.
 *   Each query provides a permutation q and returns the number of pairs (i,j) such that:
 *     - i < j
 *     - p[q[i]] = q[j]
 *     - i != k (where k is a fixed value chosen at the start)
 *
 * Algorithm:
 *   1. Choose k = (n + 1) / 4 + 1.
 *   2. For each element in the permutation, determine its position using binary search-like technique.
 *   3. Use queries to narrow down candidates and deduce the permutation.
 *
 * Time Complexity: O(n^2 * log n) - Each element needs up to O(n) queries, and there are up to O(n) elements,
 *                                   and logarithmic number of steps for binary search.
 *
 * Space Complexity: O(n) - To store arrays and temporary vectors of size n.
 */

#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <vector>
using namespace std;
const int MXN = 1005;
int n, k;
int p[MXN], qarr[MXN];
bool used[MXN];

// Ask the jury for a query result
int ask() {
  cout << "? ";
  for (int i = 1; i <= n; i++)
    cout << qarr[i] << ' ';
  cout << endl;
  int r;
  if (!(cin >> r))
    exit(0);
  if (r == -1)
    exit(0);
  return r;
}

// Output the final permutation
void answer() {
  cout << "! ";
  for (int i = 1; i <= n; i++)
    cout << p[i] << ' ';
  cout << endl;
}

// Construct a query array for a specific target value
void build_query(int fix, vector<int> good, vector<int> bad) {
  fill(used + 1, used + n + 1, false);
  fill(qarr + 1, qarr + n + 1, 0);
  qarr[k] = fix;
  used[fix] = true;
  for (int i = 1; i < k && !good.empty(); i++) {
    qarr[i] = good.back();
    used[qarr[i]] = true;
    good.pop_back();
  }
  for (int i = n; !good.empty(); i--) {
    qarr[i] = good.back();
    used[qarr[i]] = true;
    good.pop_back();
  }
  for (int i = k + 1; !bad.empty(); i++) {
    qarr[i] = bad.back();
    used[qarr[i]] = true;
    bad.pop_back();
  }
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

// Reverse the elements except the element at position k
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

// Solve one test case
void solve_one() {
  cin >> n;
  k = (n + 1) / 4 + 1;
  cout << k << endl;
  for (int target = 1; target <= n; target++) {
    vector<int> cand;
    cand.reserve(n - 1);
    for (int v = 1; v <= n; v++)
      if (v != target)
        cand.push_back(v);
    while ((int)cand.size() > 1) {
      int capB = n - (2 * k - 1); // Maximum bad elements allowed
      int takeBad = min((int)((cand.size() + 1) / 2), capB); // Number of elements to place in "bad" part
      int keepGood = (int)cand.size() - takeBad; // Remaining elements for "good"
      vector<int> good(cand.begin(), cand.begin() + keepGood);
      vector<int> bad(cand.begin() + keepGood, cand.end());
      build_query(target, good, bad); // Construct a query with good and bad parts
      int a = ask();
      rev_except_k(); // Reverse except k and ask again
      int b = ask();
      if (a + b == n - 1) {
        cand = move(good);
      } else {
        cand = move(bad);
      }
    }
    int pred = cand.back();
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


// https://github.com/VaHiX/codeForces/