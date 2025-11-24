// Problem: CF 844 C - Sorting by Subsequences
// https://codeforces.com/contest/844/problem/C

#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 100010
#define pp pair<int, int>
using namespace std;
int n, idx;
pp *a, *sa;
bool vis[N];
vector<int> v[N];
// Algorithm:
// 1. Create a sorted version of the array with indices
// 2. For each unvisited element, perform DFS to find a cycle
// 3. Each cycle forms a subsequence that can be sorted independently
// Time Complexity: O(n log n) due to sorting
// Space Complexity: O(n) for additional arrays and recursion stack
void dfs(pp s) {
  vis[s.second] = 1;
  if (sa[s.second].first == s.first) {
    // If current element is in correct position in sorted array, end subsequence
    v[idx].push_back(s.second + 1);
    idx++;
    return;
  }
  v[idx].push_back(s.second + 1); // Add index to current subsequence
  pp x = sa[s.second]; // Get the element that should be at this position
  if (!vis[x.second]) // If not visited, continue DFS
    dfs(x);
  else
    idx++; // If already visited, end the current subsequence
}
int main() {
  int i, j, k;
  int m;
  cin >> n;
  a = new pp[n];
  sa = new pp[n];
  for (i = 0; i < n; i++) {
    cin >> k;
    a[i] = {k, i}; // Store value and original index
    sa[i] = a[i];
  }
  sort(sa, sa + n); // Sort by value
  idx = 0;
  memset(vis, 0, sizeof(vis)); // Reset visited array
  for (i = 0; i < n; i++) {
    if (!vis[i])
      dfs(a[i]); // Start DFS for unvisited element
  }
  cout << idx << endl;
  for (i = 0; i < idx; i++) {
    if (v[i].size()) {
      m = v[i].size();
      cout << m << " ";
      for (j = 0; j < m; j++)
        cout << v[i][j] << " ";
      cout << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/