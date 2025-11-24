// Problem: CF 2113 D - Cheater
// https://codeforces.com/contest/2113/problem/D

/*
D. Cheater

Algorithms/Techniques: 
  - Preprocessing arrays for minimums and maximums
  - Greedy approach with one possible swap operation
  - Efficient scanning from left to right and right to left

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Problem:
You are playing a card game with n rounds. You know the dealer's hand, and you want to maximize your points.
You can swap at most two cards in your hand. You need to compute the maximum number of points you can get.

Approach:
1. Preprocess minimums from left (a[i]) and suffix maximums from right (mx[i])
2. Try all positions where a swap can potentially increase score
3. For each position, check if swapping gives better result than current
4. Use greedy strategy to find best possible score by one swap
*/
#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
constexpr int N = 2e5 + 5;
int t, n, a[N], sa[N], b[N], mx[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> n, a[0] = sa[0] = b[0] = 1e9, mx[n + 1] = 0;
    // Build prefix arrays for minimums
    for (int i = 1, x; i <= n; i++) {
      cin >> x, mx[i] = x, a[i] = a[i - 1], sa[i] = sa[i - 1];
      if (x < a[i])
        sa[i] = a[i], a[i] = x;
      else if (x < sa[i])
        sa[i] = x;
    }
    // Build suffix max array
    for (int i = n; i; i--)
      mx[i] = max(mx[i + 1], mx[i]);
    
    // Read dealer's hand and build prefix minimums
    for (int i = 1, x; i <= n; i++)
      cin >> x, b[i] = min(b[i - 1], x);
    
    // Try each index to see if swapping improves score
    for (int i = n; ~i; i--)
      if (b[n - i + 1] < sa[i] &&
          (b[n - i + 1] < a[i] || b[n - i + 1] < mx[i + 1])) {
        cout << i << "\n";
        break;
      }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/