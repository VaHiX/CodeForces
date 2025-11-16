// Problem: CF 1851 C - Tiles Comeback
// https://codeforces.com/contest/1851/problem/C

/*
C. Tiles Comeback

Problem Overview:
Given a sequence of colored tiles and a block size k, determine if it's possible to construct a path from the first tile to the last tile such that:
1. The path ends at the last tile.
2. The total length is divisible by k.
3. The path is divided into blocks of exactly k tiles each, where all tiles in a block have the same color.

Algorithm:
- For each test case, we check if there exists a valid path satisfying the conditions.
- We perform two scans:
  * Left-to-right scan starting from index 0: Try to form as many full blocks as possible, counting how many
    complete k-length blocks can be formed using tiles of color c[0].
  * Right-to-left scan starting from index n-1: Similar for the last tile's color.
- After identifying the last valid tile (from left) and first valid tile (from right), we verify:
  1. If colors at start and end are same, then we need exactly k full blocks to cover the path.
  2. Else, if there is an overlap between left and right segments such that a valid path exists.

Time Complexity: O(n) per test case, as each tile is accessed at most twice.
Space Complexity: O(n), due to the vector storing tile colors.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long left(0);
    long rem(k); // we need to fill k blocks
    for (left = 0; rem && left < n; left++) {
      rem -= (a[left] == a[0]); // Count how many tiles match the first color
    }
    --left;
    long right(n - 1);
    rem = k; // we again need to fill k blocks from the end
    for (right = n - 1; rem && right >= 0; right--) {
      rem -= (a[right] == a.back()); // Count how many tiles match the last color
    }
    ++right;
    bool res = ((a[0] == a.back()) && !rem) || (left < right); // Valid path condition
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/