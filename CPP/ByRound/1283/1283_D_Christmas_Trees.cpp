// Problem: CF 1283 D - Christmas Trees
// https://codeforces.com/contest/1283/problem/D

/*
Algorithm: BFS-based greedy placement of people to minimize total distance to nearest tree
Approach:
- Start from each tree position, perform BFS to expand outward
- At each step, place a person at the next unoccupied integer position
- Track the minimum distance contribution for each person placed
- Use a queue to simulate BFS expansion and a set to track occupied positions

Time Complexity: O(n + m * log(m)) where n is number of trees, m is number of people
Space Complexity: O(n + m) for storing occupied positions and BFS queue

The algorithm greedily places people at positions that minimize the sum of distances
by expanding from tree locations using BFS.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;
#define ll long long
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m, x;
  cin >> n >> m;
  set<int> s;  // Set to keep track of occupied positions (trees and people)
  queue<array<int, 3>> q;  // BFS queue storing {position, direction, distance}
  vector<int> v;  // Vector to store final positions of people
  for (int i = 0; i < n; i++) {
    cin >> x;
    s.insert(x);  // Insert tree positions into occupied set
    q.push({x - 1, -1});  // Push left neighbor with direction -1
    q.push({x + 1, 1});   // Push right neighbor with direction 1
  }
  ll d = 0;  // Total distance sum
  array<int, 3> p;  // Temporary array to hold current BFS state
  while (m) {
    p = q.front();  // Get next position from BFS
    q.pop();
    if (s.find(p[0]) == s.end()) {  // If position is not occupied
      s.insert(p[0]);  // Mark as occupied
      v.push_back(p[0]);  // Add to people positions
      d += p[2] + 1;  // Add distance (distance from tree to person)
      q.push({p[0] + p[1], p[1], p[2] + 1});  // Continue BFS expansion
      --m;  // Decrement number of people to place
    }
  }
  cout << d << '\n';
  for (int i : v)
    cout << i << ' ';
}


// https://github.com/VaHiX/CodeForces/