// Problem: CF 1612 D - X-Magic Pair
// https://codeforces.com/contest/1612/problem/D

/*
Algorithm: Extended Euclidean GCD-based approach to determine if x can be obtained
           through repeated operations of replacing one element with the absolute difference
           of the two elements.

The key insight is that the operations mimic the Euclidean algorithm for computing GCD,
and the final values that can be obtained are multiples of the GCD of the initial pair.

Time Complexity: O(log(min(a, b))) per test case due to the loop mimicking Euclidean GCD.
Space Complexity: O(1) - only constant extra space is used.

Techniques:
- Euclidean algorithm simulation
- Modular arithmetic to check divisibility conditions
- Optimization of swapping to ensure A >= B for simplicity
*/

#include <iostream>
#include <utility>

using namespace std;
int T;
long long A, B, X;
int main() {
  cin >> T;
  for (; T--;) {
    cin >> A >> B >> X;
    if (A < B)
      swap(A, B);  // Ensure A >= B for simplification
    bool fn = false;
    while (B > 0) {
      if (A >= X && (A - X) % B == 0) {  // Check if X can be reached
        fn = true;
        break;
      }
      A %= B;  // Apply one step of Euclidean algorithm
      swap(A, B);  // Swap to maintain A >= B
    }
    cout << (fn ? "YES\n" : "NO\n");
  }
}


// https://github.com/VaHiX/CodeForces/