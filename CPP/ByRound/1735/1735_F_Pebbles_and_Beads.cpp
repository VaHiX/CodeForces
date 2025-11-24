// Problem: CF 1735 F - Pebbles and Beads
// https://codeforces.com/contest/1735/problem/F

/*
Algorithm: Greedy with Multiset
The approach uses a greedy method combined with a multiset to track the best
exchange rates. At each day, we consider the exchange opportunities and maintain
a set of possible trades in a way that allows us to efficiently find and apply
the most beneficial trades.

Time Complexity: O(n log n) per test case due to multiset operations (insert,
erase, find). Space Complexity: O(n) for storing the exchange rates and the
multiset.
*/

#include <iostream>
#include <set>
#include <utility>

using namespace std;
typedef long double db;
const db eps = 1e-9;
multiset<pair<db, db>> st; // Multiset to store exchange rates and amounts
db sx, sy, tx, ty;
long long n, xx, yy, P[300004], Q[300004];

void sol() {
  cin >> n >> xx >> yy;
  sx = tx = xx, sy = ty = yy; // Initialize current and total pebbles/beads
  st.clear();                 // Clear the multiset for new test case

  for (int i = 1; i <= n; i++)
    cin >> P[i]; // Read pebble exchange limits
  for (int i = 1; i <= n; i++)
    cin >> Q[i]; // Read bead exchange limits

  if (xx == 0 && yy == 0) { // If we start with no pebbles or beads
    for (int i = 1; i <= n; i++)
      cout << 0 << endl;
    return;
  }

  for (int i = 1; i <= n; i++) {
    db p = P[i], q = Q[i];              // Current day's exchange limits
    sx -= p, tx += p, sy += q, ty -= q; // Update bounds
    st.insert(
        {q / p, p + p}); // Insert the rate and amount that can be exchanged

    // Adjust if we are below the minimum pebble requirement
    while (sx < -eps) {
      auto it = st.begin();
      st.erase(it);      // Remove the smallest rate
      auto [r, d] = *it; // Get rate and amount
      if (sx + d > 0) {  // If we can partially use this trade
        db D = sx + d;
        d -= D;
        st.insert({r, D}); // Insert remaining part
      }
      sx += d, sy -= d * r; // Apply the trade
    }

    // Adjust if we are below the minimum bead requirement
    while (ty < -eps) {
      auto it = --st.end(); // Find the largest rate
      st.erase(it);         // Remove it
      auto [r, d] = *it;    // Get rate and amount
      if (ty + r * d > 0) { // If we can partially use this trade
        db D = ty / r + d;
        d -= D;
        st.insert({r, D}); // Insert remaining part
      }
      tx -= d, ty += d * r; // Apply the trade
    }

    cout << fixed << tx << endl; // Output the maximum pebbles at the end of day i
  }
}

int main() {
  int tc;
  cin >> tc;
  while (tc--)
    sol();
}

// https://github.com/VaHiX/CodeForces/