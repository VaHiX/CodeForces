// Problem: CF 1797 C - Li Hua and Chess
// https://codeforces.com/contest/1797/problem/C

/*
Algorithm: Find the position of a king on an n×m chessboard using at most 3 queries.
Techniques: 
- Use queries from corners (1,1) and (n,1) to determine row and column.
- Based on the distances, deduce the king's position using geometric properties.

Time Complexity: O(1) - A constant number of operations and queries.
Space Complexity: O(1) - Only using a fixed amount of extra space.

Approach:
1. Query the king's distance from (1,1) and (n,1).
2. Depending on the results, determine row and column using mathematical relations.
3. If the king is not in the first or last row, we can find it directly from the first query.
4. If the king is in the first or last row, we need a third query to determine the exact column.

*/
#include <stdio.h>
#include <algorithm>

using namespace std;
long long n, m, a[3]; // a[0] and a[1] store distances from (1,1) and (n,1)
inline long long qr(long long y, long long x) { // Query function to get distance from (y,x)
  long long k;
  printf("? %lld %lld\n", y, x);
  fflush(stdout);
  scanf("%lld", &k);
  return k;
}
int main() {
  long long t, rr, y, x; // t: number of test cases, rr: loop counter, y,x: answer coordinates
  scanf("%lld", &t);
  for (rr = 0; rr < t; rr++) {
    scanf("%lld%lld", &n, &m);
    a[0] = qr(1, 1); // Distance from top-left corner
    a[1] = qr(n, 1); // Distance from bottom-left corner
    
    if (a[0] != a[1] && a[0] + a[1] != n - 1) { // King is not in first or last row
      // If the king is below the first row
      if (a[0] <= a[1]) {
        y = n - a[1]; // Row determined from distance to (n,1)
      } else { // If the king is above the last row
        y = a[0] + 1; // Row determined from distance to (1,1)
      }
      x = min(a[0], a[1]) + 1; // Column determined by minimum distance
    } else {
      // King is in first or last row, resolve with additional query
      if (a[0] + a[1] == n - 1) { // King is on first row
        y = a[0] + 1; // Row is determined by distance from (1,1)
        a[2] = qr(y, 1); // Query again from same row to solve column
        x = a[2] + 1; // Column determined from this query
      } else {
        // King is on last row
        x = a[0] + 1; // Column determined by distance from (1,1)
        a[2] = qr(1, x); // Query from top to solve row
        y = a[2] + 1; // Row determined from this query
      }
    }
    printf("! %lld %lld\n", y, x); // Output final answer
    fflush(stdout);
  }
}


// https://github.com/VaHiX/CodeForces/