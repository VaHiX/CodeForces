// Problem: CF 1468 M - Similar Sets
// https://codeforces.com/contest/1468/problem/M

/*
M. Similar Sets

Purpose:
This code finds two sets among a given collection of n sets that share at least two common elements.
It uses a combination of brute-force for large sets and hashing for small sets to efficiently detect such pairs.

Algorithms/Techniques:
- Coordinate compression using sorting and unique()
- Hashing with bucket-based approach for small sets (using list of pairs)
- Brute-force check for large sets (those with size > sqrt(total elements))
- Two-phase algorithm: first handle large sets, then use hashing on small sets

Time Complexity:
O(S * sqrt(S) + n * k_max) where S is total number of elements across all sets,
k_max is maximum size of a set. In practice due to constraints it's efficient enough.

Space Complexity:
O(S + n) where S is total number of unique elements, and n is number of sets.
*/

#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

#define um unordered_map
using namespace std;
const int N = 2e5 + 10;
int T, n, K[N], tmp[N], inv[N];
bool vis[N];
int lst[N];
void print(pair<int, int> res) {
  if (res.first > res.second)
    swap(res.first, res.second);
  printf("%d %d\n", res.first, res.second);
  return;
}
vector<int> vec[N];
vector<pair<int, int>> e[N];
void solve() {
  vector<int> vec[n + 10]; // Stores compressed indices for each set
  int m = 0, S = 0;        // m: size of unique elements; S: total elements count
  for (int i = 1; i <= n; S += K[i], ++i) {
    scanf("%d", &K[i]);
    vec[i].clear();
    for (int j = 0; j < K[i]; ++j) {
      int x;
      scanf("%d", &x);
      vec[i].emplace_back(x);
      tmp[++m] = x;
    }
  }
  sort(tmp + 1, tmp + 1 + m);
  m = unique(tmp + 1, tmp + 1 + m) - tmp - 1;
  // Coordinate compression of elements: map original values to compressed IDs
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < K[i]; ++j) {
      int x = lower_bound(tmp + 1, tmp + 1 + m, vec[i][j]) - tmp;
      inv[x] = vec[i][j], vec[i][j] = x;
    }
  }

  int B = sqrt(S) / 2; // Threshold for deciding large vs small sets
  bool flag = false;
  pair<int, int> res;

  // For large sets (size > B), brute force check against other sets
  for (int i = 1; i <= n; ++i) {
    if (K[i] <= B)
      continue;
    for (int j = 0; j < K[i]; ++j) {
      vis[vec[i][j]] = true;
    }
    for (int p = 1; p <= n; ++p) {
      if (p == i)
        continue;
      int cnt = 0;
      for (int j = 0; j < K[p]; ++j) {
        if (vis[vec[p][j]])
          cnt++;
        if (cnt >= 2) {           // Found two matching elements
          flag = true;
          res = {i, p};
          break;
        }
      }
      if (flag)
        break;
    }
    for (int j = 0; j < K[i]; ++j) {
      vis[vec[i][j]] = false;
    }
    if (flag) {
      print(res);
      return;
    }
  }

  // Clear edges for small sets
  for (int i = 1; i <= m; ++i) {
    e[i].clear();
  }
  
  // For small sets (size <= B), build edges between pairs in sets
  for (int i = 1; i <= n; ++i) {
    if (K[i] > B)
      continue;
    for (int j = 0; j < K[i]; ++j) {
      for (int k = j + 1; k < K[i]; ++k) {
        // Build list of edges using minimum of two elements as key,
        // storing the other element and the set id
        e[min(vec[i][j], vec[i][k])].push_back({max(vec[i][j], vec[i][k]), i});
      }
    }
  }

  // Process edge buckets to find intersecting sets
  for (int x = 1; x <= m; ++x) {
    for (int j = 0; j < e[x].size(); ++j) {
      if (lst[e[x][j].first]) { // If same larger element was seen before
        flag = true;
        res = {lst[e[x][j].first], e[x][j].second};
        break;
      }
      lst[e[x][j].first] = e[x][j].second;  // Record current set index
    }
    for (int j = 0; j < e[x].size(); ++j) {
      lst[e[x][j].first] = 0;               // Reset for next iteration
    }
    if (flag) {
      print(res);
      return;
    }
  }

  puts("-1");                               // No similar sets found
  return;
}
int main(void) {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/