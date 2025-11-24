// Problem: CF 641 C - Little Artem and Dance
// https://codeforces.com/contest/641/problem/C

/*
Algorithm/Techniques: 
- Simulation with shift tracking and parity-based swapping operations
- Uses modular arithmetic to handle circular shifts efficiently
- Tracks the effect of moves using a vector of parity states to determine when swaps occur
- Time complexity: O(n + q)
- Space complexity: O(n)

The problem simulates a dance circle where boys move in a circle and sometimes swap with partners based on the parity of their girl's index.
We use a shift variable to track the cumulative movement of boys and a vector z to store parity states for swapping operations.
The final arrangement is computed based on these operations.

*/

#include <cstdio>
#include <vector>
int main() {
  long n, q;
  scanf("%ld %ld", &n, &q);
  long shift(0); // Tracks the total shift of boys in the circle
  std::vector<long> z; // Stores parity of the shift for swap operations
  for (long p = 0; p < q; p++) {
    int cm;
    scanf("%d", &cm);
    if (cm == 1) {
      long x;
      scanf("%ld", &x);
      // Update shift with x, using modular arithmetic to stay within range
      shift += (n + x);
      shift %= n;
    } else {
      // Process swap operation: determine if we should apply or cancel a swap
      if (z.size() && z.back() == (shift % 2)) {
        z.pop_back(); // Cancel the last swap if same parity
      } else {
        z.push_back(shift % 2); // Store the current parity for future swap
      }
    }
  }
  std::vector<long> f(n); // Final arrangement of boys
  if (!z.size()) {
    // No swaps, so boys are just shifted
    for (long p = 0; p < n; p++) {
      f[p] = p + 1;
    }
  } else {
    // Apply swaps according to stored parity information
    for (long p = 0; p < n; p++) {
      if ((p + z[0]) % 2 == 0) {
        // Even position logic
        f[(p + z.size()) % n] = p + 1;
      } else {
        // Odd position logic
        f[(p - z.size() % n + n) % n] = p + 1;
      }
    }
  }
  // Output the result with applied shift
  for (long p = 0; p < n; p++) {
    printf("%ld ", f[(p + n - shift) % n]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/