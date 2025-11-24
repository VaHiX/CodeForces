// Problem: CF 2042 D - Recommendations
// https://codeforces.com/contest/2042/problem/D

/*
D. Recommendations

Purpose:
This code computes the number of "strongly recommended" tracks for each user,
based on their liked segments and the concept of predictors (users who like all
tracks that a given user likes, possibly more). A track is strongly recommended
for user i if it's not liked by user i but is liked by every predictor for user i.

Algorithms:
1. For each user, determine the leftmost and rightmost segments using monotonic stack techniques to identify predictors.
2. Sort users twice — once by left endpoints ascending (with right endpoint descending), another by right endpoints descending (with left endpoint ascending).
3. Use a stack-based approach to compute for each user the nearest predictor on the left (for left boundary) and right (for right boundary).
4. Adjust for overlapping segments among users.

Time Complexity: O(n log n) per test case due to sorting and monotonic stack processing.
Space Complexity: O(n) for storing arrays and temporary data structures.
*/

#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;
const int N = 2e5 + 10;
#define fo(i, x, y) for (int i = x; i < y; ++i)
int T, n, tp, l[N], r[N], o[N], q[N], al[N], ar[N];
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n, iota(o, o + n, 0); // Initialize indices from 0 to n-1
    fo(i, 0, n) cin >> l[i] >> r[i]; // Read intervals [l[i], r[i]]

    // Sort by left endpoint ascending (and right descending in case of ties)
    sort(o, o + n,
         [](int i, int j) { return l[i] ^ l[j] ? l[i] < l[j] : r[i] > r[j]; }),
        tp = -1; // Reset stack pointer

    fo(i, 0, n) {
      while (~tp && r[q[tp]] < r[o[i]]) // Pop from stack if current interval has smaller right bound
        --tp;
      al[o[i]] = ~tp ? l[q[tp]] : -1; // Store the left boundary of previous valid predictor
      q[++tp] = o[i]; // Push index to stack
    }

    // Sort by right endpoint descending (and left ascending in case of ties)
    sort(o, o + n,
         [](int i, int j) { return r[i] ^ r[j] ? r[i] > r[j] : l[i] < l[j]; }),
        tp = -1; // Reset stack pointer

    fo(i, 0, n) {
      while (~tp && l[q[tp]] > l[o[i]]) // Pop from stack if current interval has larger left bound
        --tp;
      ar[o[i]] = ~tp ? r[q[tp]] : -1; // Store the right boundary of previous valid predictor
      q[++tp] = o[i]; // Push index to stack
    }

    // Handle cases where two segments are identical — reset their boundaries to invalid (-1)
    fo(i, 1, n) if (l[o[i]] == l[o[i - 1]] && r[o[i]] == r[o[i - 1]]) al[o[i]] =
        al[o[i - 1]] = -1;

    // Compute final result for each user: difference between predictor and original interval
    fo(i, 0, n) cout << (~al[i] && ~ar[i] ? ar[i] - al[i] + l[i] - r[i] : 0)
                     << '\n';
  }
}


// https://github.com/VaHiX/codeForces/