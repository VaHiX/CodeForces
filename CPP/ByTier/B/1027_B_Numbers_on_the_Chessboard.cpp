// Problem: CF 1027 B - Numbers on the Chessboard
// https://codeforces.com/contest/1027/problem/B

/*
B. Numbers on the Chessboard

Algorithm:
The problem involves a chessboard of size n x n where numbers from 1 to n^2 are filled in a specific pattern:
- Even sum coordinate cells get the first ceil(n^2/2) numbers (1 to ceil(n^2/2))
- Odd sum coordinate cells get the remaining numbers (ceil(n^2/2)+1 to n^2)
The filling is done row by row, left to right within each row.

Time Complexity: O(1) per query
Space Complexity: O(1)

Approach:
- We precompute formulas for both even and odd n cases based on coordinates.
- For even n: 
  - Even sum cells are assigned first half (n*n/2 numbers)
  - Odd sum cells are assigned second half (n*n/2 numbers)
- For odd n:
  - Compute distribution considering offset due to parity of row/column
*/
#include <cstdio>
typedef long long ll;
int main() {
  ll n, q;
  scanf("%lld %lld", &n, &q);
  while (q--) {
    ll row, col;
    scanf("%lld %lld", &row, &col);
    ll res(0);
    if (n % 2 == 0) {
      // For even n, straightforward formula
      res = ((row + col) % 2) * (n * n / 2) + (n / 2) * (row - 1) + (col + 1) / 2;
    } else {
      // For odd n, account for offset and parity of row
      res = ((row + col) % 2) * (n * n + 1) / 2 + ((row - 1) / 2) * n +
            (row % 2 == 0) * (n + 1 - ((row + col) % 2)) / 2 + (col + 1) / 2;
    }
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/