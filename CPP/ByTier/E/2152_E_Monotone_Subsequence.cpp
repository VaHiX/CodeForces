// Problem: CF 2152 E - Monotone Subsequence
// https://codeforces.com/contest/2152/problem/E

/*
E. Monotone Subsequence
Interactive problem to find a monotone subsequence of length n+1 in a hidden permutation of length n^2+1.

Algorithms/Techniques:
- Uses visible skyscrapers queries to determine the structure of the permutation
- Applies the Erdős–Szekeres theorem which guarantees existence of monotone subsequences
- Maintains an array idx to track which indices have been "seen" and their associated query iteration
- Builds a result sequence by collecting visible elements from strategic queries

Time Complexity: O(n^3) - At most n queries, each with up to n^2 elements in the query set. Each query takes O(n^2) time due to processing.
Space Complexity: O(n^2) - for storing the idx array and query results
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define X first
#define Y second
typedef long long ll;
typedef pair<int, int> pii;
int t, n;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> idx(n * n + 1, 0), res; // idx tracks which query iteration each index was seen in
    for (int i = 1; i <= n; ++i) {
      vector<int> ans = {}, ask = {}; // ans stores visible skyscrapers, ask is the current query list
      for (int j = 0; j < n * n + 1; ++j) {
        if (!idx[j]) // If not yet processed, include in current query
          ask.push_back(j);
      }
      cout << "? " << ask.size() << " "; // Send the query with size and indices
      for (int x : ask)
        cout << x + 1 << " "; // Output indices (1-based)
      cout << endl;
      int len;
      cin >> len;
      ans.resize(len);
      for (int &x : ans) 
        cin >> x, --x; // Read visible indices and convert to 0-based
      if ((int)ans.size() >= n + 1) { // Found enough elements to form the required subsequence
        res = ans;
        break;
      }
      for (int x : ans)
        idx[x] = i; // Mark these indices as processed in iteration i
    }
    if (res.empty()) {
      int pos = n * n; // Start from highest index
      while (idx[pos])
        --pos; // Find first unmarked position
      res.push_back(pos);
      for (int i = n; i >= 1; --i) { // Backtrack from last iteration to build decreasing sequence
        while (idx[pos] != i)
          --pos;
        res.push_back(pos);
      }
      reverse(res.begin(), res.end()); // Reverse to maintain increasing order in result
    }
    cout << "! ";
    for (int i = 0; i < n + 1; ++i)
      cout << res[i] + 1 << " "; // Output result indices (1-based)
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/