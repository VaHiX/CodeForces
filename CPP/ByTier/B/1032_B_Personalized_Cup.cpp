// Problem: CF 1032 B - Personalized Cup
// https://codeforces.com/contest/1032/problem/B

/*
B. Personalized Cup
Purpose: Generate a rectangular table (nameplate) to display a given string handle,
         where the number of rows is minimized and among valid tables with minimum rows,
         the one with minimum columns is chosen.
         The table must consist of asterisks (*) and letters such that:
         - Rows are uniform (difference in asterisk count <= 1)
         - Reading table top-to-bottom, left-to-right skipping asterisks gives original string
Algorithms/Techniques: Greedy approach to find optimal matrix dimensions,
         then filling the matrix row by row, placing asterisks in a way that
         satisfies the uniformity constraint.
Time Complexity: O(n), where n is the length of the string s (for both finding dimensions and filling).
Space Complexity: O(n), for storing the string and outputting the matrix.

*/
#include <iostream>
#include <string>

using namespace std;
int n, i, j, k, x, c, r;
string s;
int main() {
  cin >> s;
  n = s.size();
  // Find optimal number of columns (c) and rows (r) to minimize rows,
  // then columns, under constraints.
  // r = ceil(n / c), x = extra cells needed for even distribution
  for (c = 20; r = (n + c - 1) / c, x = r * c - n, x >= r; c--)
    ; // Continue decreasing c while x >= r to satisfy uniformity requirement.
  cout << r << " " << c << endl;
  // Fill the matrix row by row
  for (i = 0; i < r; cout << endl, i++)
    for (j = 0; j < c; j++)
      cout << (j == 0 && i < x ? '*' : s[k++]); // Place asterisk only at start of first x rows
}


// https://github.com/VaHiX/codeForces/