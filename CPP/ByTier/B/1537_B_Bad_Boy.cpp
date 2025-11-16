// Problem: CF 1537 B - Bad Boy
// https://codeforces.com/contest/1537/problem/B

/*
Code purpose:
This program determines the optimal positions to place two yo-yos in a grid room 
so that Anton, standing at position (i, j), has to travel the maximum possible 
distance to collect them and return to his starting position. 

The strategy is to place the yo-yos at opposite corners of the grid to maximize 
the Manhattan distance. For any grid of size n x m, placing one yo-yo at (1, m) 
and the other at (n, 1) ensures the longest path.

Algorithms/Techniques: 
- Greedy approach to maximize Manhattan distance
- Direct calculation based on grid dimensions and Anton's position

Time Complexity: O(1) - Constant time operations per test case
Space Complexity: O(1) - Only a fixed amount of variables used
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, i, j;
    scanf("%ld %ld %ld %ld", &n, &m, &i, &j);
    printf("1 %ld %ld 1\n", m, n);
  }
}


// https://github.com/VaHiX/CodeForces/