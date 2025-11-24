// Problem: CF 630 E - A rectangle
// https://codeforces.com/contest/630/problem/E

/*
E. A rectangle
time limit per test
0.5 seconds
memory limit per test
64 megabytes
input
standard input
output
standard output
Developing tools for creation of locations maps for turn-based fights in a new game, Petya faced the following problem.
A field map consists of hexagonal cells. Since locations sizes are going to be big, a game designer wants to have a tool for quick filling of a field part with identical enemy units. This action will look like following: a game designer will select a rectangular area on the map, and each cell whose center belongs to the selected rectangle will be filled with the enemy unit.
More formally, if a game designer selected cells having coordinates 
(
x
1
, 
y
1
)
 and 
(
x
2
, 
y
2
)
, where 
x
1
 ≤ 
x
2
 and 
y
1
 ≤ 
y
2
, then all cells having center coordinates 
(
x
, 
y
)
 such that 
x
1
 ≤ 
x
 ≤ 
x
2
 and 
y
1
 ≤ 
y
 ≤ 
y
2
 will be filled. Orthogonal coordinates system is set up so that one of cell sides is parallel to 
OX
 axis, all hexagon centers have integer coordinates and for each integer 
x
 there are cells having center with such 
x
 coordinate and for each integer 
y
 there are cells having center with such 
y
 coordinate. It is guaranteed that difference 
x
2
 - 
x
1
 is divisible by 
2
.
Working on the problem Petya decided that before painting selected units he wants to output number of units that will be painted on the map.
Help him implement counting of these units before painting.

Algorithms/Techniques: 
- Counting lattice points in a rectangle with a specific offset
- Mathematical formula for hexagonal grid cell counting

Time Complexity: O(1)
Space Complexity: O(1)

*/

#include <cstdio>
typedef long long ll;
int main() {
  ll x1, y1, x2, y2;
  scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
  // Calculate number of hexagonal cells in the rectangle using formula
  // The result is derived from the fact that in a hexagonal grid,
  // the count of cells inside a rectangle can be calculated with 
  // inclusion of an offset due to how hexes are arranged.
  printf("%lld\n", 1 + (x2 - x1 + 1) * (y2 - y1 + 1) / 2);
  return 0;
}


// https://github.com/VaHiX/codeForces/