// Problem: CF 925 A - Stairs and Elevators
// https://codeforces.com/contest/925/problem/A

/*
Purpose: This code solves the problem of finding the minimum time to travel between two rooms in a hotel with stairs and elevators.
         The hotel has n floors and m sections per floor. Some sections contain stairs or elevators.
         Stairs and elevators span all floors at a specific section.
         The movement time depends on the mode of transport:
         - Walking on the same floor: 1 time unit per section
         - Using stairs: 1 time unit per floor
         - Using elevator: 1 time unit per v floors (rounded up)
         
Algorithms/Techniques:
- Binary search (lower_bound) to quickly find the nearest stair or elevator
- Greedy approach: for each query, examine the closest stairs/elevators to both source and destination
- Preprocessing: sort positions of stairs and elevators for efficient lookup

Time Complexity: O((c_l + c_e) * log(c_l + c_e) + q * log(c_l + c_e))
Space Complexity: O(c_l + c_e)
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
const int inf = INT_MAX;
int n, m, cl, ce, v, q, L[100005], E[100005];

// Function to calculate the minimum time between two sections
int wk(int sx, int sy, int ex, int ey) {
  // If we are on the same floor, just walk horizontally
  if (sx == ex)
    return abs(sy - ey);
  
  // Find the nearest stairs
  int k = lower_bound(L, L + cl, sy) - L, ans = inf;
  
  // Check if there is a stair at or to the right of the starting position
  if (k < cl) {
    int T = L[k];
    ans = min(abs(sy - T) + abs(ey - T) + abs(sx - ex), ans);
  }
  
  // Check if there is a stair to the left of the starting position
  if (k > 0) {
    int T = L[k - 1];
    ans = min(abs(sy - T) + abs(ey - T) + abs(sx - ex), ans);
  }
  
  // Find the nearest elevator
  k = lower_bound(E, E + ce, sy) - E;
  
  // Check if there is an elevator at or to the right of the starting position
  if (k < ce) {
    int T = E[k];
    // Calculate total time: walk to elevator + use elevator + walk to destination
    // For elevator: (abs(sx - ex) / v) + (1 if there's a remainder)
    ans = min(abs(sy - T) + abs(ey - T) + abs(sx - ex) / v +
                  (((abs(sx - ex) % v) == 0) ? 0 : 1),
              ans);
  }
  
  // Check if there is an elevator to the left of the starting position
  if (k > 0) {
    int T = E[k - 1];
    ans = min(abs(sy - T) + abs(ey - T) + abs(sx - ex) / v +
                  (((abs(sx - ex) % v) == 0) ? 0 : 1),
              ans);
  }
  
  return ans;
}

int main() {
  scanf("%d%d%d%d%d", &n, &m, &cl, &ce, &v);
  for (int i = 0; i < cl; i++)
    scanf("%d", &L[i]);
  for (int i = 0; i < ce; i++)
    scanf("%d", &E[i]);
  
  // Sort the stair and elevator positions for binary search
  sort(L, L + cl);
  sort(E, E + ce);
  
  scanf("%d", &q);
  while (q--) {
    int sx, sy, ex, ey;
    scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
    printf("%d\n", wk(sx, sy, ex, ey));
  }
}


// https://github.com/VaHiX/CodeForces/