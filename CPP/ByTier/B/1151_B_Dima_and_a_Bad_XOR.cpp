// Problem: CF 1151 B - Dima and a Bad XOR
// https://codeforces.com/contest/1151/problem/B

/*
B. Dima and a Bad XOR
Purpose: Given an n x m matrix of non-negative integers, select exactly one integer from each row such that their XOR is strictly greater than zero.
Algorithm: Greedy approach with XOR properties.
Time Complexity: O(n * m)
Space Complexity: O(n * m) for the matrix storage + O(n) for result array = O(n * m)

The idea:
1. First, try selecting the first element from each row and compute their XOR.
2. If the result is already non-zero, we're done.
3. Otherwise, we need to change one of the selections in a way that makes the final XOR non-zero.
   - For each row, if possible, swap to a different column element such that
     XOR changes from 0 to non-zero.
4. If no such swap exists across all rows, return NIE.
*/
#include <cstdio>
#include <vector>
int main() {
  long nr, nc;
  scanf("%ld %ld", &nr, &nc);
  std::vector<std::vector<long>> a(nr, std::vector<long>(nc, 0));
  for (long row = 0; row < nr; row++) {
    for (long col = 0; col < nc; col++) {
      scanf("%ld", &a[row][col]);
    }
  }
  std::vector<long> res(nr, 0); // stores column indices of selected elements
  long ans(0); // cumulative XOR of selected elements
  for (long row = 0; row < nr; row++) {
    ans ^= a[row][0]; // xor all first elements
  }
  // If ans is already non-zero, we have our solution
  for (long row = 0; row < nr; row++) {
    if (ans) {
      break;
    }
    for (long col = 1; col < nc; col++) {
      if (ans) {
        break;
      }
      // If current element differs from selected in this row
      if (a[row][col] != a[row][res[row]]) {
        ans ^= a[row][res[row]]; // remove old value from XOR
        ans ^= a[row][col];      // add new value to XOR
        res[row] = col;          // update column index for this row
      }
      if (ans) {
        break;
      }
    }
  }
  if (ans) {
    puts("TAK");
    for (long row = 0; row < nr; row++) {
      printf("%ld ", 1 + res[row]);
    };
    puts("");
  } else {
    puts("NIE");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/