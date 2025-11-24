// Problem: CF 764 B - Timofey and cubes
// https://codeforces.com/contest/764/problem/B

/*
B. Timofey and cubes

Algorithm: The code simulates the reverse operations performed by Dima on a sequence of cubes. Instead of performing forward operations, we reverse the process to recover the original order.

The approach works by:
1. Reading input array of size n.
2. For each valid step i (from 0 to n/2), if i is even, swap elements at positions i and (n - 1 - i).
3. Then output the modified array which will correspond to the original configuration.

Time Complexity: O(n)
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]); // Read each cube number
  }
  for (long p = 0; p < n / 2; p++) {
    if (p % 2 == 0) {
      long u = a[p];                // Store value at position p
      a[p] = a[n - 1 - p];          // Swap with element from the end
      a[n - 1 - p] = u;             // Complete the swap
    }
  }
  for (long p = 0; p < n; p++) {
    printf("%ld ", a[p]); // Print the restored sequence
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/