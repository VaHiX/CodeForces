// Problem: CF 1797 A - Li Hua and Maze
// https://codeforces.com/contest/1797/problem/A

/*
Problem: A. Li Hua and Maze
Purpose: Determine the minimum number of obstacles to block all paths between two points in an n×m grid.
Algorithms/Techniques: Geometric analysis to find minimum cut based on position of start and end points relative to borders.
Time Complexity: O(1) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long x1, y1, x2, y2;
    scanf("%ld %ld %ld %ld", &x1, &y1, &x2, &y2);
    
    // Calculate the minimum number of obstacles needed to block paths from (x1,y1) to (x2,y2)
    // a represents the minimum obstacles needed to cut off path from (x1,y1)
    int a = 4 - (x1 == 1 || x1 == n) - (y1 == 1 || y1 == m);
    // b represents the minimum obstacles needed to cut off path from (x2,y2)
    int b = 4 - (x2 == 1 || x2 == n) - (y2 == 1 || y2 == m);
    
    // Output the smaller of the two values
    printf("%d\n", a < b ? a : b);
  }
}


// https://github.com/VaHiX/codeForces/