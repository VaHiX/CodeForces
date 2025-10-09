// Problem: CF 2148 F - Gravity Falls
// https://codeforces.com/contest/2148/problem/F

/*
F. Gravity Falls
Algorithms/Techniques: Greedy algorithm, lexicographical comparison, simulation of gravity effect on stacked arrays.
Time Complexity: O(sum(k_i) * log(n)) where sum(k_i) is the total number of elements across all arrays.
Space Complexity: O(sum(k_i))

The task is to find the lexicographically smallest bottom row after stacking and letting gravity take effect.
We simulate this by always selecting the lexicographically smallest array at each step, extending our result
with that array's remaining portion. The process proceeds character-by-character until all arrays are exhausted.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n, L = 0;
    cin >> n;
    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
      int k;
      cin >> k;
      a[i].resize(k);
      for (int j = 0; j < k; j++)
        cin >> a[i][j];
      L = max(L, k); // Track maximum length among all arrays
    }
    vector<int> b; // Resultant bottom row
    int cur = 0;   // Current position in the arrays to process
    while (cur < L) {
      int best = -1; // Index of the lexicographically smallest array at current step
      for (int i = 0; i < n; i++) {
        if (a[i].size() <= cur)
          continue; // Skip arrays that are shorter than current position
        if (best == -1 ||
            lexicographical_compare(a[i].begin() + cur, a[i].end(),
                                    a[best].begin() + cur, a[best].end()))
          best = i; // Select index of array with smaller suffix
      }
      for (int k = cur; k < a[best].size(); k++)
        b.push_back(a[best][k]); // Append the rest of the selected array
      cur = a[best].size();        // Move to end of that array
    }
    for (int i = 0; i < b.size(); i++) {
      cout << b[i] << " ";
    }
    cout << "\n";
  }
}


// https://github.com/VaHiX/codeForces/