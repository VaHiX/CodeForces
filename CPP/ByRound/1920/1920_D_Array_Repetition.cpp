// Problem: CF 1920 D - Array Repetition
// https://codeforces.com/contest/1920/problem/D

/*
Purpose: This code solves the problem of simulating array operations and answering queries about specific elements in the resulting array.
The key idea is to track how the array grows through operations and efficiently determine which original element corresponds to a queried position.

Approach:
- Use a layered structure to store the array segments formed by appending copies.
- Maintain length and repetition counts for each segment.
- For each query, perform a reverse lookup to find the corresponding original element.

Time Complexity: O(n + q) per test case, where n is the number of operations and q is the number of queries.
Space Complexity: O(n) for storing the array state and history.

Algorithms/Techniques:
- Simulation with compression of repeated structures
- Reverse lookup to map query index to original elements
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
vector<int> pos[70];           // Stores the values appended in each layer
long long int len[70], x[70], c[70];  // len: length of array in each layer, x: repetition factor, c: cumulative size
long long int now, inf = 1e18, xx;    // now: current size of array, inf: large number to avoid overflow
int main() {
  int T, opt, n, q, cnt, ans;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    ans = now = cnt = 0, c[0] = len[0] = x[0] = 0;
    pos[0].clear();
    for (int i = 1; i <= n; i++) {
      scanf("%d%lld", &opt, &xx);
      if (now > inf)  // Skip further processing if overflow occurs
        continue;
      if (opt == 1) {  // Append a single element
        pos[cnt].push_back(xx);
        now++;
      } else {  // Append multiple copies of current array
        xx++;  // Increment x to account for 1-based indexing
        if (inf / now < xx) {  // Prevent overflow when multiplying
          xx = inf / now;
          if (now * xx < inf)
            xx++;  // Adjust to avoid overflow
        }
        cnt++;  // Move to next layer
        len[cnt] = now;   // Record the size before this operation
        x[cnt] = xx;      // Record number of copies
        now = now * xx;   // Update total size
        pos[cnt].clear(); // Clear the position list for this layer
        c[cnt] = now;     // Cumulative size after this operation
      }
    }
    for (int i = 1; i <= q; i++) {
      scanf("%lld", &xx);
      int t = cnt;  // Start from the last layer
      while (1) {
        if (xx > c[t]) {  // If the query exceeds cumulative size of the current layer
          ans = xx - c[t] - 1;  // Adjust index to find the correct one
          break;
        }
        xx = xx % len[t]; // Wrap x within the length of the layer
        if (xx == 0)
          xx = len[t];  // Handle case where remainder is zero
        t--;  // Move to the previous layer
      }
      printf("%d ", pos[t][ans]);  // Output the value from the correct layer and index
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/