// Problem: CF 2031 F - Penchick and Even Medians
// https://codeforces.com/contest/2031/problem/F

/*
Algorithm/Technique: 
- Randomized approach to find two indices in a permutation whose values are the medians of the entire permutation.
- Uses random sampling and querying subsequences to narrow down candidates for median indices.
- Time Complexity: O(n^2) average case due to nested loops in final verification step.
- Space Complexity: O(n) for storing indices and temporary arrays.

The algorithm works by:
1. Randomly selecting two indices and querying the remaining elements.
2. If the result matches the expected median values, those two indices are candidates for the median positions.
3. Then, further query combinations between these candidates to identify the exact median indices.
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

using namespace std;
#define pr pair<int, int>
#define mk make_pair
pr ask(vector<int> a) {
  cout << "? " << a.size() << ' ';
  for (auto x : a)
    cout << x << ' ';
  cout << endl;
  pr res;
  cin >> res.first >> res.second;
  if (res.first > res.second)
    swap(res.first, res.second);
  return res;
}
mt19937 rnd(114514);
void sol() {
  int n;
  cin >> n;
  vector<int> a(n);
  iota(a.begin(), a.end(), 1);
  int pa = -1, pb = -1;
  while (pa == -1) {
    int x = rnd() % n + 1, y = rnd() % n + 1;
    if (x == y)
      continue;
    vector<int> b;
    for (int i = 1; i <= n; ++i)
      if (i != x && i != y)
        b.push_back(i);
    pr res = ask(b);
    if (res.first == (n >> 1) && res.second == (n >> 1) + 1) {
      pa = x, pb = y;
      if (pa > pb)
        swap(pa, pb);
    }
  }
  vector<int> b;
  for (int i = 1; i <= n; ++i)
    if (i != pa && i != pb)
      b.push_back(i);
  vector<int> c;
  for (int i = 0; i < b.size(); i += 2) {
    pr res = ask({b[i], b[i + 1], pa, pb});
    if (res.first == (n >> 1) || res.second == (n >> 1) ||
        res.first == (n >> 1) + 1 || res.second == (n >> 1) + 1)
      c.push_back(b[i]), c.push_back(b[i + 1]);
  }
  for (int i = 0; i < c.size(); ++i)
    for (int j = i + 1; j < c.size(); ++j)
      if (ask({pa, pb, c[i], c[j]}) == mk(n >> 1, (n >> 1) + 1)) {
        cout << "! " << c[i] << " " << c[j] << endl;
        return;
      }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    sol();
}


// https://github.com/VaHiX/CodeForces/