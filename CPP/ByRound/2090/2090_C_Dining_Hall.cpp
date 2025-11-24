// Problem: CF 2090 C - Dining Hall
// https://codeforces.com/contest/2090/problem/C

/*
C. Dining Hall
Algorithms/Techniques: Priority Queue, BFS-like traversal with greedy selection based on t_i value.

Time Complexity: O(n log n) per test case, where n is the number of guests.
Space Complexity: O(n) for storing the priority queue and auxiliary data structures.

The problem involves assigning guests to table cells in a grid-based dining hall,
where tables occupy 2x2 blocks. Each guest selects a cell based on:
- If t_i = 1: nearest vacant table cell
- If t_i = 0: nearest unoccupied table (entire block)  
Distance is measured as Manhattan distance from (0,0), and ties are broken by x then y coordinates.
A priority queue helps efficiently process candidates in order of increasing distance.
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
#define PII pair<int, int>
#define PIP pair<int, PII>
const int N = 5e4 + 5;
int T, n, p;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> n;
    priority_queue<PIP, vector<PIP>, greater<PIP>> q; // Priority queue stores {distance, {x,y}}, min-heap
    int x = 1, y = 1, dis = 2; // Initial position and distance tracking for next candidates
    for (int i = 1; i <= n; i++) {
      cin >> p;
      if (p == 1 && !q.empty() && q.top().first < dis) { // If t_i=1 and closer table exists
        cout << q.top().second.first << " " << q.top().second.second << "\n";
        q.pop(); // Use up that candidate cell
      } else { // Otherwise pick according to strategy
        cout << x << " " << y << "\n"; // Output selected cell coordinates
        
        // Insert next potential candidates into queue
        q.push({x + y + 1, {x, y + 1}}); // Push (x, y+1) for future consideration
        q.push({x + y + 1, {x + 1, y}}); // Push (x+1, y)
        q.push({x + y + 4, {x + 1, y + 1}}); // Push (x+1, y+1)
        
        // Update x & y to simulate progression through the grid
        if (y == 1) {
          swap(x, y);
          y += 3;
        } else
          x += 3, y -= 3;
        dis = x + y; // Recalculate current distance for comparison in next iteration
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/