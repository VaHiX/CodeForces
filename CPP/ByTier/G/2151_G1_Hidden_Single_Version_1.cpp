// Problem: CF 2151 G1 - Hidden Single (Version 1)
// https://codeforces.com/contest/2151/problem/G1
/*
Hidden Single Problem Solver
Algorithm: Binary Search with Query Optimization
Time Complexity: O(n * log n)
Space Complexity: O(n)
*/

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
const int N = 607;
int T, n, p[N];

// Ask query function - returns 1 if x exists in subset S, 0 otherwise
int ask(int l, int r, int x) {
  cout << "? " << x << " " << r - l + 1 << " ";
  assert(l <= n and r <= n and l <= r);
  for (int i = l; i <= r; i++)
    cout << p[i] << " ";
  cout << endl;
  int o;
  cin >> o;
  return o;
}

// Recursive solve function that finds the unique element
int solve(int l, int r, vector<int> vec, vector<int> wst) {
  // Base case: if total elements in wst and vec is equal to range size, no
  // unique element found
  if ((int)wst.size() + 2 * (int)vec.size() == r - l + 1)
    return -1;
  // If vec is empty, then no candidate left
  if (!vec.size())
    return -1;

  vector<int> toL, toR, wL, wR;
  if (l == r)
    return assert(vec.size() == 1), vec[0];

  int mid = (l + r) >> 1; // Midpoint of current range
  int cnt = 0;
  shuffle(p + l, p + r + 1, mt19937{}); // Shuffle the elements in current range

  // Process each candidate element from vec
  for (auto u : vec) {
    int o = ask(l, mid, u); // Check if u exists in left half
    if (!o) {
      toR.push_back(u); // If not found in left half, move to right half
    } else {
      int o2 = ask(mid + 1, r, u); // Check if u exists in right half
      if (!o2)
        toL.push_back(u); // If not found in right half, move to left half
      else
        wL.push_back(u),
            wR.push_back(u); // If found in both halves, mark as wildcard
    }
  }

  // Process wildcard elements from wst
  for (auto u : wst) {
    int o = ask(l, mid, u);
    if (o)
      wL.push_back(u);
    else
      wR.push_back(u);
  }

  int ans = -1;
  // Recursively search in left half first
  ans = solve(l, mid, toL, wL);
  if (ans == -1)
    // If answer not found in left, search right half
    ans = solve(mid + 1, r, toR, wR);
  assert(ans != -1); // Assertion to ensure solution found
  return ans;
}

void solve() {
  cin >> n;
  n = 2 * n - 1; // Size of hidden array
  for (int i = 1; i <= n; i++)
    p[i] = i; // Initialize position array with values 1..n

  shuffle(p + 1, p + n + 1, mt19937{}); // Shuffle the positions array

  vector<int> vec, vec2;
  for (int i = 1; i <= (n + 1) / 2; i++)
    vec.push_back(
        i); // Initialize initial candidates with first half of elements

  int o = solve(1, n, vec, vec2);
  cout << "! " << o << endl; // Output the result
}

int main() {
  cin >> T;
  while (T--)
    solve();
}

// https://github.com/VaHiX/CodeForces/