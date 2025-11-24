// Problem: CF 1687 B - Railway System
// https://codeforces.com/contest/1687/problem/B

/*
Algorithm: Binary search + Greedy + Sorting
Approach:
1. First, we determine the length of each edge by querying with all edges set to 1,
   except one edge which is set to 0. This allows us to find the value of every edge.
2. Then, we sort edges based on their lengths in ascending order.
3. We simulate adding edges one by one in this sorted order.
   For each edge, we test if including it increases the maximum capacity.
   If it does, we include it and update the answer.
   Otherwise, we exclude it.

Time Complexity: O(m^2 * log(m)) due to sorting and nested queries.
Space Complexity: O(m) for storing edges and queries.

This solution uses a greedy approach combined with binary search over the edge values
to efficiently determine the minimum capacity of the railway system, which is the
maximum value of a spanning forest under the assumption of optimal edge inclusion.
*/

#include <algorithm>
#include <iostream>

using namespace std;

int n, m, e[510], p[510], ans;
char s[500010];

// Comparator to sort edges by their lengths
bool cmp(const int x, const int y) { return e[x] < e[y]; }

int main() {
  cin >> n >> m;
  // Initialize string s with '0' for all edges
  for (int i = 1; i <= m; i++)
    s[i] = '0', p[i] = i;

  // Query to get the value of each edge
  // For each edge, set it to 1 and others to 0 to isolate its contribution
  for (int i = 1; i <= m; i++) {
    s[i] = '1';                    // Activate current edge
    cout << "? " << s + 1 << endl; // Send query to interactor
    s[i] = '0';                    // Deactivate current edge
    cin >> e[i];                   // Receive result from interactor
  }

  // Sort edge indices by their lengths (ascending order)
  sort(p + 1, p + m + 1, cmp);

  // Greedily add edges in ascending order to build the spanning forest
  for (int i = 1, opt; i <= m; ++i) {
    s[p[i]] = '1';                 // Activate the i-th smallest edge
    cout << "? " << s + 1 << endl; // Query with current edge set
    cin >> opt;                    // Get maximum capacity with this edge included

    // If the new capacity is greater than previous + edge value,
    // then this edge contributes to the maximum capacity and we accept it
    if (opt - ans != e[p[i]])      // Check if edge was contributing
      s[p[i]] = '0';               // If not, remove it
    else
      ans = opt;                   // Else update the answer
  }

  // Output final result
  cout << "! " << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/