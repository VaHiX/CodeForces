// Problem: CF 2041 M - Selection Sort
// https://codeforces.com/contest/2041/problem/M

/*
Problem: Minimum cost to sort an array using Alice's Selection Sort as a building block.
Algorithms/Techniques: Two-pass greedy approach with prefix and suffix sorting.
Time Complexity: O(n^2)
Space Complexity: O(n)

Approach:
- The key idea is to determine when parts of the array are already sorted relative to their final positions.
- We compute for each prefix (from left to right) and suffix (from right to left) how many elements are correctly placed,
  then calculate minimal cost combining two operations (prefix + suffix).

Code Logic:
- First, we sort the array to determine the order of elements.
- For each index i, we simulate prefix sorting up to i+1 elements.
- We track which indices in the sorted version are already "in place" or have been seen through prior operations.
- A similar reverse pass is done for suffix operations.
- Answer is the minimum total cost among all valid combinations of prefix and suffix sort.

*/
#include <string.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<pair<int, int>> vp(n); // value and original index
  for (int i = 0; i < n; i++) {
    cin >> vp[i].first;
    vp[i].second = i;
  }
  sort(vp.begin(), vp.end()); // Sort by value to find correct positions
  int idx[n]; // maps original index to sorted position
  for (int i = 0; i < n; i++) {
    idx[vp[i].second] = i; // assign sorted index for each element
  }
  long long ans = 1e18;
  int al_sort_idx = 0; // tracks the first index where sorting is required
  int in_s[n]; // marks if sorted position is "in place" or visited
  memset(in_s, 0, sizeof(in_s));
  for (int i = 0; i < n; i++) {
    in_s[idx[i]] = 1; // mark the element's final position as filled
    while (al_sort_idx < n &&
           (in_s[al_sort_idx] || idx[al_sort_idx] == al_sort_idx)) {
      al_sort_idx++; // advance to next unsorted index
    }
    ans = min(ans, 1LL * (i + 1) * (i + 1) +
                       1LL * (n - al_sort_idx) * (n - al_sort_idx)); // cost = prefix^2 + suffix^2
  }

  memset(in_s, 0, sizeof(in_s));
  al_sort_idx = n - 1;
  for (int i = n - 1; i >= 0; i--) {
    in_s[idx[i]] = 1; // mark the element's final position as seen from back
    while (al_sort_idx >= 0 &&
           (in_s[al_sort_idx] || idx[al_sort_idx] == al_sort_idx)) {
      al_sort_idx--; // move backward to unsorted index
    }
    ans = min(ans, 1LL * (n - i) * (n - i) +
                       1LL * (al_sort_idx + 1) * (al_sort_idx + 1)); // cost = suffix^2 + prefix^2
  }
  cout << ans << '\n';
  return 0;
}


// https://github.com/VaHiX/codeForces/