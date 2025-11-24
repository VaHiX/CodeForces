// Problem: CF 966 A - Stairs and Elevators
// https://codeforces.com/contest/966/problem/A

/*
Purpose: This code solves the problem of finding the minimum time to travel between two rooms in a hotel with floors and sections, using stairs, elevators, and walking. 
         The algorithm computes the minimum travel time by considering using stairs or elevators optimally.

Algorithms/Techniques: 
- Binary search using lower_bound to find nearest stairs/elevators.
- Greedy approach with case analysis for optimal path selection.
- Preprocessing of stairs and elevators positions.

Time Complexity: 
- Preprocessing: O(c1 + c2), where c1 is number of stairs, c2 is number of elevators.
- Per query: O(log(c1) + log(c2)), due to binary search operations.
- Overall: O(q * (log(c1) + log(c2))) for q queries.

Space Complexity:
- O(c1 + c2) for storing positions of stairs and elevators.
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
const int inf = 0x3f3f3f3f;
using namespace std;
int n, m, v, c1, c2, q, a[120000], b[120000];
int main() {
  scanf("%d%d%d%d%d", &n, &m, &c1, &c2, &v);
  for (int i = 0; i < c1; i++)
    scanf("%d", &a[i]); // Read positions of stairs
  for (int i = 0; i < c2; i++)
    scanf("%d", &b[i]); // Read positions of elevators
  int q;
  scanf("%d", &q); // Read number of queries
  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2); // Read query coordinates
    
    // If on same floor, travel directly along corridor
    if (x1 == x2) {
      printf("%d\n", abs(y2 - y1));
      continue;
    }
    
    // Find nearest stair to starting position
    int temp = lower_bound(a, a + c1, y1) - a;
    int ans = inf;
    
    // If a stair exists at or after y1 position
    if (temp < c1) {
      ans = min(ans, abs(a[temp] - y1) + abs(a[temp] - y2) + abs(x1 - x2));
    }
    
    // If a stair exists before y1 position
    if (temp > 0) {
      ans = min(ans,
                abs(a[temp - 1] - y1) + abs(a[temp - 1] - y2) + abs(x1 - x2));
    }
    
    // Find nearest elevator to starting position
    temp = lower_bound(b, b + c2, y1) - b;
    
    // If an elevator exists at or after y1 position
    if (temp < c2) {
      ans = min(ans, abs(b[temp] - y1) + abs(b[temp] - y2) +
                         (abs(x1 - x2) + v - 1) / v);
    }
    
    // If an elevator exists before y1 position
    if (temp > 0) {
      ans = min(ans, abs(b[temp - 1] - y1) + abs(b[temp - 1] - y2) +
                         (abs(x1 - x2) + v - 1) / v);
    }
    
    printf("%d\n", ans); // Output the minimum time for this query
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/