// Problem: CF 1669 C - Odd/Even Increments
// https://codeforces.com/contest/1669/problem/C

/*
C. Odd/Even Increments
Algorithms/Techniques: Simulation, Array Parity Analysis

Time Complexity: O(n) per test case
Space Complexity: O(n) for the array storage

The problem asks whether we can make all elements of the array have the same parity (all even or all odd)
by performing operations that add 1 to elements at odd indices or even indices.

Key Insight:
- Adding 1 to an element toggles its parity.
- Elements at odd indices (1-based) can only change their parity by operations on odd indices.
- Elements at even indices (1-based) can only change their parity by operations on even indices.
- The final state depends on the initial parity pattern of elements.

The approach checks if it's possible to make all elements have the same parity:
- For each element, check whether it is consistent with the allowed parity patterns based on its index.
*/

#include <stdio.h>
#include <iostream>

using namespace std;
int n, a[200005];
void Solve() {
  cin >> n;
  bool ok = 1;  // Flag to indicate if it's possible to make all elements same parity
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    // Check if current element's parity matches expected parity for its index
    // If a[i] % 2 != a[i % 2] % 2, this means the element cannot be made to match the required pattern
    if (a[i] % 2 != a[i % 2] % 2)
      ok = 0;
  }
  if (ok)
    puts("YES");
  else
    puts("NO");
}
int main() {
  int t;
  cin >> t;
  while (t--)
    Solve();
}


// https://github.com/VaHiX/codeForces/