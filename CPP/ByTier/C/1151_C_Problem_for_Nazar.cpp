// Problem: CF 1151 C - Problem for Nazar
// https://codeforces.com/contest/1151/problem/C

/*
Problem: C. Problem for Nazar
Purpose: Computes the sum of numbers from l to r in a sequence where:
- Odd numbers (1, 3, 5, ...) are written in stages 1, 3, 5, ...
- Even numbers (2, 4, 6, ...) are written in stages 2, 4, 6, ...
- Each stage doubles the number of elements from the previous stage.
- Stage 1: 1 element, Stage 2: 2 elements, Stage 3: 4 elements, etc.
Algorithm:
- Uses a simulation to determine which numbers belong to which stage
- For a given n, calc(n) computes the sum of first n numbers in this sequence
- The main function outputs (calc(r) - calc(l-1)) % p to compute range sum

Time Complexity: O(log n) where n is up to 1e18
Space Complexity: O(1)
*/

#include <iostream>
#include <utility>

using namespace std;
typedef long long ll;
const int p = 1e9 + 7;
inline int calc(ll n) {
  ll sx = 0, sy = 0, *x = &sx, *y = &sy; // sx: sum of odd numbers, sy: sum of even numbers
  for (ll k = 1; n >= k; k <<= 1) {     // k doubles each iteration (1, 2, 4, 8, ...)
    *x += k;                             // Add k elements to the current set
    n -= k;                              // Reduce remaining count
    swap(x, y);                          // Alternate between odd and even sums
  }
  *x += n;                               // Handle remaining numbers in last stage
  sx %= p, sy %= p;                      // Modular reduction
  return (sx * sx + (sy + 1) * sy) % p;   // Return sum of squares formula for arithmetic progression
}
int main() {
  ll l, r;
  cin >> l >> r;
  cout << (calc(r) - calc(l - 1) + p) % p; // Range sum using prefix sums
  return 0;
}


// https://github.com/VaHiX/codeForces/