// Problem: CF 1696 E - Placing Jinas
// https://codeforces.com/contest/1696/problem/E

/*
Code Purpose:
This code calculates the minimum number of operations needed to ensure that all white cells in a grid are empty of dolls. 
The grid is defined by a non-increasing sequence 'a', where a cell (x, y) is white if y < a[x]. 
Each operation splits one doll into two dolls at adjacent positions (x, y+1) and (x+1, y).
The solution leverages combinatorics: for each row x, we compute the number of ways to place dolls 
such that the resulting configuration satisfies the white cell constraint, using multinomial coefficients.

Algorithms/Techniques:
- Preprocessing factorials for fast combination calculations
- Modular exponentiation for inverse computation
- Multinomial coefficient calculation using factorials
- Summation of contributions from each row

Time Complexity: O(n + max_a), where max_a is the maximum value in the array a
Space Complexity: O(max_a), for storing precomputed factorials up to max_a
*/

#include <iostream>

using namespace std;
#define int long long
const int P = 1e9 + 7;
int n, a[200009], f[400009], s;
int qsm(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = res * a % P;
    a = a * a % P;
    b /= 2;
  }
  return res;
}
signed main() {
  cin >> n;
  f[0] = 1;
  f[1] = 1;
  for (int i = 2; i <= 400000; i++)
    f[i] = i * f[i - 1] % P; // Precompute factorials modulo P
  for (int i = 0; i <= n; i++)
    cin >> a[i];
  for (int i = 0; i <= n; i++)
    s = (s +
         f[a[i] + i] * qsm(f[i + 1], P - 2) % P * qsm(f[a[i] - 1], P - 2) % P) %
        P; // Compute multinomial coefficient contribution for row i
  cout << s;
}


// https://github.com/VaHiX/CodeForces/