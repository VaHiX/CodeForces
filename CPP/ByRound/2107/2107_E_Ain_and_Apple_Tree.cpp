// Problem: CF 2107 E - Ain and Apple Tree
// https://codeforces.com/contest/2107/problem/E

// E. Ain and Apple Tree
// Purpose: Given n nodes and target weight k, construct a tree such that the absolute difference between the tree's weight and k is at most 1.
// Algorithms/Techniques: Greedy construction of tree to match weight k.
// Time Complexity: O(n) per test case (amortized over all test cases).
// Space Complexity: O(n) for storing the result edges.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
int n;
ll k;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    vector<int> ans;
    ll tmp, val;
    // Greedily build the tree by trying to include as many heavy edges as possible
    for (int i = n - 1; i >= 1; i--) {
      tmp = 1ll * (i - 1) * i / 2;
      if (k >= tmp)
        k -= tmp, ans.push_back(i);
    }
    // If remaining k > 1, no valid tree can be made
    if (k > 1) {
      cout << "No\n";
      continue;
    }
    cout << "Yes\n";
    int id = 1, siz = n, tot = n;
    // Construct the actual tree using the greedy values in ans
    for (int cur : ans) {
      for (int i = 1; i <= siz - cur - 1; i++)
        cout << id << " " << (tot--) << "\n";
      cout << id << " " << (++id) << "\n";
      siz = cur;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/