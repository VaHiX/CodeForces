// Problem: CF 995 A - Tesla
// https://codeforces.com/contest/995/problem/A

/*
Purpose: This code solves a car parking problem where Allen wants to park k cars in a 4-row, n-column grid.
         Cars start in rows 2 and 3, and must be moved to designated spots in rows 1 and 4.
         Only one car can be moved at a time, and only to adjacent empty spaces.
         The goal is to determine if all cars can be parked within 20000 moves.

Algorithm: Greedy simulation approach
           - Traverse the grid in a zigzag pattern from row 2 to row 3, left to right
           - For each cell in the traversal:
             * If there is a car, attempt to move it to the target spot
             * If the car is already in the target spot, increment the parking count
             * Otherwise, move the car to an adjacent empty space
           - Continue until all cars are parked or 20000 moves are exhausted

Time Complexity: O(2*n) = O(n), where n is the number of columns
Space Complexity: O(1) - only using fixed-size arrays and variables, not counting input/output

*/

#include <stdio.h>
#include <utility>

using namespace std;
int n, k, a[5][51], tot;
struct node {
  int id, x, y;
  node(int a = 0, int b = 0, int c = 0) { id = a, x = b, y = c; }
} ans[20005];
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= n; j++)
      scanf("%d", &a[i][j]);
  int nx = 2, ny = 1, cnt = 0, sum = 0;
  while (cnt <= 20000 && sum != k) {
    int tx = nx, ty, gx, gy;
    nx == 2 ? ty = ny + 1 : ty = ny - 1; // Move right in row 2, left in row 3
    if (ty > n)
      tx++, ty--; // Change row if out of bounds
    if (ty < 1)
      tx--, ty++; // Change row if out of bounds
    gy = ty;
    tx == 2 ? gx = 1 : gx = 4; // Target row is 1 for row 2, 4 for row 3
    if (a[tx][ty] != 0) {
      if (a[tx][ty] == a[gx][gy]) // Car is already at its target spot
        ans[++tot] = node(a[tx][ty], gx, gy), sum++, a[tx][ty] = 0;
      else if (!a[nx][ny]) // Move car to adjacent empty space
        ans[++tot] = node(a[tx][ty], nx, ny), swap(a[tx][ty], a[nx][ny]);
    }
    nx = tx, ny = ty; // Update current position
    cnt++; // Increment move counter
  }
  if (sum == k) {
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++)
      printf("%d %d %d\n", ans[i].id, ans[i].x, ans[i].y);
  } else
    puts("-1");
  return 0;
}


// https://github.com/VaHiX/CodeForces/