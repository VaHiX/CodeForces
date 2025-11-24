// Problem: CF 630 Q - Pyramids
// https://codeforces.com/contest/630/problem/Q

/*
Purpose: Calculate the total volume of three pyramids with specific base shapes and edge lengths.
           - Triangular pyramid with equilateral triangle base and all edges equal.
           - Quadrangular pyramid with square base and all edges equal.
           - Pentagonal pyramid with regular pentagon base and all edges equal.

Algorithms/Techniques:
  - Volume calculation for regular pyramids using geometric formulas.
  - Mathematical constants and square root computations for accurate results.

Time Complexity: O(1) - Constant time operations.
Space Complexity: O(1) - Only a few variables are used regardless of input size.

*/
#include <stddef.h>
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;
#define lli long long int
#define pb push_back
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long double a, b, c;
  cin >> a >> b >> c;
  // Volume of triangular pyramid with equilateral triangle base and all edges equal
  long double t = ((a * a) / sqrt(2)) * a / 6;
  // Volume of quadrangular pyramid with square base and all edges equal
  long double s = ((b * b) / sqrt(2)) * b / 3;
  // Volume of pentagonal pyramid with regular pentagon base and all edges equal
  long double p = c * c * .3015028324 * c;
  cout << setprecision(10) << t + s + p << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/