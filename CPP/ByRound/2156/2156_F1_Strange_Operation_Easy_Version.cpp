// Problem: CF 2156 F1 - Strange Operation (Easy Version)
// https://codeforces.com/contest/2156/problem/F1

/*
Code Purpose:
This code solves the problem of transforming a given permutation into the lexicographically smallest permutation possible through a specific operation. The operation allows adjusting three elements in a certain way, and the algorithm uses a greedy approach to simulate the process.

Algorithms/Techniques:
- Greedy simulation using position tracking
- Sorting-like logic to bring elements into lexicographically minimal order

Time Complexity: O(n^2) in worst case due to nested loops and the while loop that may iterate up to n times per element.
Space Complexity: O(n) for storing the permutation and position arrays.

*/
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
void myfun() {
  int n;
  cin >> n;
  vector<int> perm(n + 1), pos(n + 1); // perm stores the current permutation, pos stores positions of elements
  for (int i = 1; i <= n; i++) {
    cin >> perm[i];
    pos[perm[i]] = i; // Store the position of each element in the permutation
  }
  while (1) {
    int ops = 0; // Flag to check if any operations were performed in this iteration
    for (int i = 0; i < (n - 1); i++) {
      // Check if the element at pos[i+2] is smaller than both pos[i] and pos[i+1]
      if (pos[i + 2] < pos[i] && pos[i + 2] < pos[i + 1]) {
        int tmp1 = pos[i];
        int tmp0 = pos[i + 2];
        int tmp2 = pos[i + 1];
        pos[i] = tmp0;         // Update positions
        pos[i + 1] = tmp1;
        pos[i + 2] = tmp2;
        ops++; // Mark that one operation was done
      }
    }
    if (!ops) // If no operations were performed, we're done
      break;
  }
  vector<int> ans(n + 1); // Final answer permutation
  for (int i = 1; i <= n; i++) {
    ans[pos[i]] = i; // Reconstruct the permutation based on the final positions
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " "; // Output the result
  }
  cout << "\n";
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  cin >> t;
  while (t--) {
    myfun();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/