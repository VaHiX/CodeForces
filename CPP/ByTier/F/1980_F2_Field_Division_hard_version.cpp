// Problem: CF 1980 F2 - Field Division (hard version)
// https://codeforces.com/contest/1980/problem/F2

/*
 * Problem: Field Division (Hard Version)
 * 
 * Purpose: 
 *   This code determines the maximum area Alice can claim in a field divided by her path,
 *   considering k fountains that may or may not be given to her. It computes the optimal
 *   path for Alice such that her plot includes cell (n,1) and excludes all fountains unless
 *   they are given to her.
 *
 * Algorithm:
 *   - The key insight is to process fountains by columns from left to right.
 *   - For each column, we maintain a "top-right" boundary that represents the area that Alice can claim.
 *   - We use a sweep line approach processing fountains in order of increasing column.
 *   - When a new column is processed, we calculate how much area Alice gains by including that fountain.
 * 
 * Time Complexity:
 *   O(k * log k) - Sorting the fountains takes O(k * log k), and one pass through the sorted list takes O(k).
 * 
 * Space Complexity:
 *   O(k) - The vector storing fountains and results.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
using i64 = long long;
#define i128 __int128
int inf = 1e9 + 5;
int mod = 1e9 + 7;

// Structure to hold fountain data with index
struct Node {
  int r, c, i;  // row, column, index
};

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<Node> node(k);
  for (int i = 0; i < k; i++) {
    cin >> node[i].r >> node[i].c;
    node[i].i = i;  // Store original index for result mapping
  }

  // Sort fountains by column (ascending), then by row (descending) if same column
  sort(node.begin(), node.end(), [&](auto x, auto y) {
    if (x.c == y.c) {
      return x.r > y.r;  // For tied columns, put higher rows first
    }
    return x.c < y.c;  // Sort by column ascending
  });

  ll ans = 0;  // Maximum area Alice can get without any fountain
  vector<ll> res(k);  // Result array to store gains for each fountain

  int tr = 0, tc = 1;  // Top-right boundary tracker: row and column
  Node nodet;
  nodet.c = m + 1;  // Sentinel value (beyond last column)
  nodet.r = n;  // Bottom row
  node.push_back(nodet);  // Add sentinel at end

  int tjr = 0;  // Temporary row tracker for area calculation
  int tjc = 1;  // Temporary column tracker for area calculation

  // Iterate through fountains (including sentinel)
  for (int i = 0, j = -1; i < node.size(); i++) {
    // If we've already seen a previous fountain (j != -1) and current fountain
    // is above the previous one in the same column (i.e., closer to top), update its gain
    if (j != -1) {
      if (node[i].r > tjr) {
        // Calculate area of area rectangle from last valid position to current position
        res[node[j].i] += 1LL * (node[i].c - tjc) * (node[j].r - tjr);
        tjc = node[i].c;
        tjr = node[i].r;
      }
    }

    // If the current fountain is below the previous top-right bound, 
    // update the area Alice gets from the entire path so far.
    if (node[i].r > tr) {
      // Calculate area from current top-right point to full bottom row
      ans += 1LL * (node[i].c - tc) * (n - tr);
      tjr = tr;       // Set temporary row tracker
      tc = node[i].c; // Update temporary column
      tr = node[i].r; // Update top-right row
      tjc = tc;       // Reset temporary column
      j = i;          // Set j to current fountain index
    }
  }

  // Output the maximum area Alice can claim without any gift from Bob
  cout << ans << endl;

  // Output the gains for each fountain (i.e., how much more area would Alice get if given that fountain)
  for (int i = 0; i < k; i++) {
    cout << res[i] << " \n"[i == k - 1];  // Print with space except for last element
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/