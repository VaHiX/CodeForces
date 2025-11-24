// Problem: CF 1520 C - Not Adjacent Matrix
// https://codeforces.com/contest/1520/problem/C

/*
Algorithm/Technique: 
The solution uses a bipartite coloring of the matrix to ensure that adjacent cells (sharing a side) 
contain numbers that are not adjacent (differ by more than 1). The matrix is divided into two sets 
based on the parity of (row + col). All elements with even (row + col) sum are filled first with 
odd numbers from 1 to n^2, then all elements with odd (row + col) sum are filled with even numbers 
from 1 to n^2. This ensures no two adjacent numbers differ by exactly 1.

Time Complexity: O(n^2) - We iterate through the matrix twice, filling it with numbers.
Space Complexity: O(n^2) - We use an n x n matrix to store the result.

This approach works for all n >= 3. For n = 1, it's trivial. For n = 2, it's impossible to avoid 
adjacent numbers being adjacent in value, hence -1.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n == 1) {
      puts("1");
      continue;
    } else if (n == 2) {
      puts("-1");
      continue;
    }
    std::vector<std::vector<long>> res(n, std::vector<long>(n, 0));
    long cur(1);
    for (long par = 0; par <= 1; par++) {
      for (long row = 0; row < n; row++) {
        for (long col = 0; col < n; col++) {
          if ((row + col) % 2 == par) {
            res[row][col] = cur++;
          }
        }
      }
    }
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < n; col++) {
        printf("%ld ", res[row][col]);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/CodeForces/