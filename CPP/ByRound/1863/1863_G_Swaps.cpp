// Problem: CF 1863 G - Swaps
// https://codeforces.com/contest/1863/problem/G

/*
Purpose: This code solves the problem of counting the number of distinct arrays that can be obtained by performing swaps of the form (a[i], a[a[i]]) on a given array.
Algorithm/Techniques:
- Graph traversal using DFS to detect cycles in the array permutation.
- For each cycle, calculate the number of valid configurations based on in-degrees.
- Use modular arithmetic to handle large numbers.

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int mod = 1e9 + 7;

void testCase() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &i : a)
    cin >> i, i--; // Convert to 0-based indexing
  vector<bool> vis(n), cycle(n); // vis tracks visited nodes, cycle tracks nodes in current cycle
  vector<int> in(n); // in[i] stores the in-degree of node i
  for (int i : a)
    in[i]++; // Count in-degrees
  int ans = 1;
  for (int i = 0; i < n; i++) {
    if (vis[i])
      continue;
    int cur = i;
    // First DFS to find the cycle
    while (!vis[cur]) {
      vis[cur] = true;
      cur = a[cur];
    }
    int tot = 0, val = 1;
    // Process the cycle to compute number of valid configurations
    while (!cycle[cur]) {
      val = (1LL * val * (1 + in[cur])) % mod;
      tot += in[cur];
      cycle[cur] = true;
      cur = a[cur];
    }
    val -= tot;
    val %= mod;
    if (val < 0)
      val += mod;
    ans = (1LL * ans * val) % mod;
    // Second DFS to assign values for the nodes already processed in cycle
    cur = i;
    while (!cycle[cur]) {
      ans = (1LL * ans * (1 + in[cur])) % mod;
      cycle[cur] = true;
      cur = a[cur];
    }
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  testCase();
  return 0;
}


// https://github.com/VaHiX/CodeForces/