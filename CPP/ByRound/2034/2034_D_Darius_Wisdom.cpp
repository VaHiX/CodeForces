// Problem: CF 2034 D - Darius' Wisdom
// https://codeforces.com/contest/2034/problem/D

/*
Purpose: This code solves the problem of sorting stone columns by inscriptions in non-decreasing order using specific allowed moves.
         Each move transfers one inscription from a column with 2 inscriptions to a column with 1, or from 1 to 0, maintaining valid transitions.
         The algorithm works by scanning from left to right and greedily pairing columns to achieve ascending order.

Algorithms/Techniques:
- Greedy two-pointer approach
- In-place rearrangement with swapping and move tracking
- Linear scan with conditional transfer logic for 0,1,2 inscription states

Time Complexity: O(n) - Each element is visited at most twice, once for checking and once for transfer.
Space Complexity: O(n) - For storing the move sequence and the input array.

*/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define ll long long
using namespace std;
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &i : a)
    cin >> i;
  int j = n - 1, k = n - 1, ans = 0;
  vector<pair<int, int>> move;
  for (int i = 0; i < n; i++) {
    j = max(j, k);  // Ensure j is at least k to avoid invalid comparisons
    if (a[i] == 2) {  // If current column has 2 inscriptions
      while (i < j && a[j] != 1)  // Find a column with 1 inscription
        j--;
      if (i < j && a[j] == 1) {  // If found
        move.push_back({i, j});  // Record the move
        ans++;  // Increment move count
        swap(a[i], a[j]);  // Transfer inscription (simulate by swapping values)
      }
    }
    if (a[i] == 1) {  // If current column has 1 inscription
      while (i < k && a[k] != 0)  // Find a column with 0 inscriptions
        k--;
      if (i < k && a[k] == 0) {  // If found
        move.push_back({i, k});  // Record the move
        ans++;  // Increment move count
        swap(a[i], a[k]);  // Transfer inscription
      }
    }
  }
  cout << ans << "\n";
  for (auto [a, b] : move)
    cout << a + 1 << " " << b + 1 << "\n";  // Output 1-based indices
  return;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/