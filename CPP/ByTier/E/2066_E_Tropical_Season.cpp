// Problem: CF 2066 E - Tropical Season
// https://codeforces.com/contest/2066/problem/E

/*
E. Tropical Season
Algorithms/Techniques: Segment Tree, Binary Search, Simulation
Time Complexity: O((n + q) log n)
Space Complexity: O(n)

This code solves the problem of determining whether it's possible to identify a poisoned barrel among n barrels,
where each barrel may contain different amounts of water, and exactly one barrel has an unknown poison with weight 0.179 kg.

It uses a segment tree to maintain dynamic information about the barrels' weights and allows for efficient updates and queries.
The key idea is that after handling each query, we must verify if there exists a valid strategy to identify the poisoned barrel
by checking the conditions of comparison operations between barrels.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int offset = 1 << 20; // Offset for segment tree indices
const int INF = 1e9;        // Infinity constant for initialization
struct Node {
  ll sum;
  int mini, lft, rig;
  Node(ll sum, int mini, int lft, int rig)
      : sum(sum), mini(mini), lft(lft), rig(rig) {}
  Node() : sum(0), mini(INF), lft(INF), rig(-INF) {}
};
Node tour[2 * offset]; // Segment tree array

// Merges two nodes of the segment tree based on their properties
Node merge(Node lhs, Node rhs) {
  return Node(lhs.sum + rhs.sum,
              min(min(lhs.mini, rhs.mini), rhs.lft - lhs.rig),
              min(lhs.lft, rhs.lft), max(lhs.rig, rhs.rig));
}

// Updates the segment tree node at position x with value val
void update(int x, int val) {
  int pos = x + offset;
  tour[pos].sum += val * x;           // Update sum of weights
  tour[pos].mini = tour[pos].sum > x ? 0 : INF; // Check if valid at point x
  if (tour[pos].sum)                  // If current segment contains weight
    tour[pos].lft = tour[pos].rig = x; // Set left and right bounds to x
  else {
    tour[pos].lft = INF;
    tour[pos].rig = -INF;
  }
  for (pos /= 2; pos; pos /= 2)       // Propagate up the tree
    tour[pos] = merge(tour[2 * pos], tour[2 * pos + 1]);
}

// Queries range [from, to) in the segment tree
Node query(int x, int lo, int hi, int from, int to) {
  if (lo >= to || hi <= from)
    return Node();   // Return default node when out of bounds
  if (lo >= from && hi <= to)
    return tour[x];  // Return segment tree node when fully inside range
  int mid = (lo + hi) / 2;
  return merge(query(2 * x, lo, mid, from, to),
               query(2 * x + 1, mid, hi, from, to)); // Recursively merge results
}

Node query(int from, int to) { return query(1, 0, offset, from, to); }

// Main function logic to check valid identification strategy
void answer() {
  for (int curr = 1; curr < offset; curr++) {
    int x = 1;
    ll pref = 0;
    while (x < offset) {
      x *= 2;
      if (tour[x].rig < curr)
        pref += tour[x++].sum; // Accumulate prefix sum while moving down
    }
    curr = x - offset;         // Adjust current index
    if (pref < curr) {
      int gap = query(1, 0, offset, curr, offset).mini;
      if (gap < offset && gap > pref) { // If valid gap detected -> impossible to identify
        puts("No");
        return;
      }
    } else
      curr = min(pref, (ll)offset); // Ensure limit is respected
  }
  puts("Yes");                 // Valid identification strategy exists
}

int main() {
  int N, Q;
  scanf("%d%d", &N, &Q);
  while (N--) {
    int x;
    scanf("%d", &x);
    update(x, 1);   // Initialize all barrels' weights
  }
  answer();         // Process initial state
  while (Q--) {
    char c;
    int x;
    scanf(" %c%d", &c, &x);
    update(x, c == '+' ? 1 : -1); // Update with new or removed barrel
    answer();                     // Determine feasibility after update
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/