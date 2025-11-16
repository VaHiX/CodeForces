// Problem: CF 1589 A - Mathematical Addition
// https://codeforces.com/contest/1589/problem/A

/*
Code Purpose:
This code solves the equation of the form (x/u) + (y/v) = (x+y)/(u+v) for given positive integers u and v.
The solution is derived mathematically to avoid the trivial (0,0) solution.
The approach is to manipulate the equation algebraically and find a non-trivial solution.
It uses the identity that x = u^2 and y = -v^2 satisfies the equation for any u, v > 0.

Algorithms/Techniques:
- Algebraic manipulation of the given equation to derive a solution
- Direct computation using the derived formula x = u^2 and y = -v^2

Time Complexity: O(T), where T is the number of test cases. Each test case is processed in constant time.
Space Complexity: O(1), as only a constant amount of extra space is used regardless of input size.

*/
#include <iostream>

using namespace std;
int main() {
  int T, u, v;
  for (cin >> T; T--;)
    cin >> u >> v, cout << 1ll * u * u << ' ' << -1ll * v * v << '\n';
}


// https://github.com/VaHiX/CodeForces/