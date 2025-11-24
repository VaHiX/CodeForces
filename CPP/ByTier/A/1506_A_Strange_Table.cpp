// Problem: CF 1506 A - Strange Table
// https://codeforces.com/contest/1506/problem/A

/*
Problem: Strange Table
Algorithm/Techniques: Mathematical mapping between column-wise and row-wise numbering systems.
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem asks to convert a cell number from a "column-first" numbering system 
to a "row-first" numbering system on an n x m grid.

In column-first (given):
- Cells are filled column by column, top to bottom in each column.
- For cell x (1-indexed), we find its row and column in this system.
  
In row-first (required):
- Cells are filled row by row, left to right in each row.
- We want to find the corresponding number in this system.

The approach:
1. Convert 1-based index x to 0-based index: x = x - 1
2. Find row number in column-wise grid: row = x % n
3. Find column number in column-wise grid: col = x / n
4. Map that position to row-first grid: res = row * m + col + 1

Sample Input:
5
1 1 1
2 2 3
3 5 11
100 100 7312
1000000 1000000 1000000000000

Sample Output:
1
2
9
1174
1000000000000
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m, x;
    scanf("%lld %lld %lld", &n, &m, &x);
    --x;                       // Convert to 0-based indexing
    ll row = x % n;            // Determine row in column-first system
    ll col = x / n;            // Determine column in column-first system
    ll res = row * m + col + 1; // Map to row-first numbering system
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/