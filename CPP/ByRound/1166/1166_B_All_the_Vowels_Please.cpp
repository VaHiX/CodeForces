// Problem: CF 1166 B - All the Vowels Please
// https://codeforces.com/contest/1166/problem/B

/*
B. All the Vowels Please
Problem Description:
Given an integer k, construct a vowelly word of length k such that when written in a grid of size n x m (where n*m = k), 
every row and column contains at least one occurrence of each vowel ('a', 'e', 'i', 'o', 'u').
If no such arrangement exists, output "-1".

Algorithms/Techniques:
- Factorization: Find factors n, m such that n * m = k
- Grid filling: Fill the grid in row-major order using a repeating pattern of vowels
- Validation: Check if both dimensions are at least 5 to ensure all vowels fit in each row/column

Time Complexity: O(sqrt(k) + k)
Space Complexity: O(k)

The approach first finds suitable n and m (both >= 5) by iterating through possible factors up to sqrt(k).
Then, it fills a grid with vowels in a pattern ensuring every row/column has all 5 vowels.
*/
#include <cstdio>
#include <vector>
int main() {
  long k;
  scanf("%ld", &k);
  long nr(0), nc(0);
  for (long p = 1; p * p <= k; p++) {
    if (k % p) {        // If p is not a factor of k, skip
      continue;
    }
    nr = p;             // Assign potential number of rows
    nc = k / p;         // Calculate corresponding number of columns
  }
  if (nr < 5) {         // If smallest dimension < 5, impossible to hold all vowels in each row/column
    puts("-1");
    return 0;
  }
  std::vector<std::vector<char>> m(nr, std::vector<char>(nc, 'd'));  // Initialize grid with 'd'
  std::vector<char> s(5);
  s[0] = 'a';
  s[1] = 'e';
  s[2] = 'i';
  s[3] = 'o';
  s[4] = 'u';
  long vow(0), row(0), col(0), x(k);
  while (x--) {
    m[row][col] = s[(vow / nc) % 5];  // Fill vowel in current position
    ++vow;
    ++row;
    row %= nr;         // Move to next row (wrap around)
    ++col;
    col %= nc;         // Move to next column (wrap around)
    if (m[row][col] != 'd') {  // If cell already filled, skip
      col = (col + 1) % nc;
    }
  }
  for (long row = 0; row < nr; row++) {
    for (long col = 0; col < nc; col++) {
      printf("%c", m[row][col]);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/