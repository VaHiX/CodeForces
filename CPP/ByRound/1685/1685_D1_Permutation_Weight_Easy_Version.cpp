// Problem: CF 1685 D1 - Permutation Weight (Easy Version)
// https://codeforces.com/contest/1685/problem/D1

/*
Purpose: This code solves the problem of finding a permutation q that minimizes the weight,
         where weight is defined as the sum of absolute differences between consecutive
         elements in the permutation when indexed by the original permutation.
         The solution uses a cycle decomposition approach to build the optimal permutation.

Algorithms: 
    - Cycle decomposition in permutations
    - Greedy construction of permutation based on cycles

Time Complexity: O(n^2) due to nested loops for handling cycles and inserting elements
Space Complexity: O(n) for storing the permutation and auxiliary arrays

*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define fo(i, n) for (i = 0; i < n; i++)
#define pb push_back
typedef vector<int> vi;
void solve(int tc) {
  int i, j, n, id, at = 0;
  cin >> n;
  vi a(n), vis(n), prv(n), ans; // 'prv' stores positions of elements in original permutation
  fo(i, n) cin >> a[i]; // read input permutation
  fo(i, n) prv[a[i] - 1] = i; // map each element to its position in the original array
  while (1) {
    ans.pb(at); // add current index to result
    vis[at] = 1; // mark as visited
    at = prv[at]; // move to next element in cycle
    if (at == 0) // if back to start, finish current cycle
      break;
  }
  fo(i, n) {
    if (vis[i]) // skip already visited elements
      continue;
    fo(j, ans.size()) if (ans[j] == i - 1) id = j; // find position of element i-1 in ans
    int at = i; // start from unvisited element
    while (1) {
      at = prv[at]; // find next element in cycle
      vis[at] = 1; // mark as visited
      id++; // increment position
      ans.insert(ans.begin() + id, at); // insert at correct position
      if (at == i) // if back to start, end cycle
        break;
    }
  }
  for (auto &i : ans)
    cout << i + 1 << " "; // output the permutation (1-indexed)
  cout << "\n";
}
int main() {
  int t, i;
  cin >> t;
  fo(i, t) solve(i + 1);
  return 0;
}


// https://github.com/VaHiX/CodeForces/