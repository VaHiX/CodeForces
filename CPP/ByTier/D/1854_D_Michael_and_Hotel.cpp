// Problem: CF 1854 D - Michael and Hotel
// https://codeforces.com/contest/1854/problem/D

/*
Algorithm: Find all rooms from which Brian (in room 1) can reach Michael (any room) via teleporters.
Technique: 
- Use binary search to find the cycle starting from room 1
- For each unvisited room, perform a query to check if it can reach any room in the cycle
- Build the set A of such rooms

Time Complexity: O(n * log(n) * log(n)) where n is the number of rooms
Space Complexity: O(n) for storing visited status and cycle information

*/
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int X = 63; // Maximum possible cycle length
int a, b, c, d, e, i, j, ii, jj, zx, xc, K, bo[509]; // Global variables for indexing and tracking
vector<int> vv, cyc; // vv - temporary vector, cyc - stores cycle of rooms
bool ask(int i, vector<int> q, int K) { // Function to ask query about reaching rooms in set q from room i in K steps
  cout << "? " << i << " " << K << " " << q.size() << " ";
  for (auto x : q)
    cout << x << " ";
  cout << endl;
  int qw = 0;
  cin >> qw;
  return qw;
}
int NXT(int q, int K) { // Find next room in the cycle using binary search
  int lef, rig, mid, i;
  vector<int> V;
  for (i = 1; i <= a; i++) {
    if (bo[i] != 0) // Skip if already visited
      continue;
    V.push_back(i);
  }
  lef = -1;
  rig = V.size();
  while (1) {
    if (lef + 2 >= rig) // Binary search convergence
      break;
    mid = (lef + rig) >> 1; // Midpoint of search range
    vv.clear(); // Clear vector for next query
    for (i = lef + 1; i <= mid; i++) {
      vv.push_back(V[i]);
    }
    if (ask(q, vv, K) == 1) { // If we can reach from q through mid elements
      rig = mid + 1; // Narrow search to left half
    } else {
      lef = mid; // Narrow search to right half
    }
  }
  return V[lef + 1]; // Return one room that is not in the current query (part of cycle)
}
void print() { // Print result set A
  vector<int> V;
  int i;
  for (i = 1; i <= a; i++) {
    if (bo[i] == 1)
      V.push_back(i);
  }
  cout << "! " << V.size() << " ";
  for (auto x : V)
    cout << x << " ";
  cout << endl;
  exit(0);
}
int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> a;
  K = 1000000; // Large number of steps for checking full reachability
  cyc.push_back(NXT(1, K)); // Start finding cycle from room 1
  int XOM = 0;
  while (cyc.size() < X) { // Build cycle until maximum expected size
    c = NXT(cyc.back(), 1); // Find next element in cycle (only 1 step)
    if (c == cyc[0]) { // If returned to start, complete our cycle
      XOM = 1;
      break;
    }
    cyc.push_back(c);
    bo[c] = 1; // Mark this room as visited
  }
  bo[cyc[0]] = 1; // Mark the start of cycle as visited
  if (XOM == 0) { // If not completed, extend to find rest of graph
    d = X;
    while (1) {
      e = cyc.size(); // Current size before expansion
      vv = cyc; // Temporarily copy cycle
      for (i = 1; i <= a; i++) {
        if (bo[i] == 1) // Skip visited rooms
          continue;
        if (ask(i, vv, d) == 1) // Check if room can reach cycle
          cyc.push_back(i); // Add to cycle
      }
      for (i = e; i < cyc.size(); i++) // Mark newly added rooms as visited
        bo[cyc[i]] = 1;
      if (cyc.size() < e + d) // If no new rooms were added, end expansion
        break;
      d *= 2; // Double the number of steps for next query
    }
  }
  bo[1] = 1; // Mark Brian's initial position as visited
  for (i = 1; i <= a; i++) { // For unvisited rooms, check if they can reach cycle
    if (bo[i] == 1) // Skip already visited rooms
      continue;
    if (ask(i, cyc, K) == 1) { // Can it reach the cycle?
      bo[i] = 1; // Mark as part of set A
    }
  }
  print(); // Output the final set A
  return 0;
}


// https://github.com/VaHiX/CodeForces/