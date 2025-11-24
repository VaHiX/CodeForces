// Problem: CF 1786 B - Cake Assembly Line
// https://codeforces.com/contest/1786/problem/B

/*
B. Cake Assembly Line

Algorithm:
This problem involves determining whether it's possible to shift a set of cake segments so that each cake is covered by some dispenser segment, with no excess coverage outside the cakes.

The key insight is to compute the minimum and maximum shifts required such that every cake falls under at least one dispenser. For each cake i, there's an interval [a[i] - w, a[i] + w] representing its position, and for each dispenser j, there's an interval [b[j] - h, b[j] + h] representing its coverage.

To ensure the cake i is covered by dispenser j, we need their intervals to overlap. Let us denote:
- Cake interval: [a[i] - w, a[i] + w]
- Dispenser interval: [b[j] - h, b[j] + h]

Let's define how much we need to shift the conveyor so that this specific cake i is covered by dispenser j:
shift = b[j] - a[i], and for coverage to happen, [a[i] - w + shift, a[i] + w + shift] should intersect with [b[j] - h, b[j] + h].

Rearranging constraints gives us the required shift interval for each such pair. We compute the intersection of all such intervals across all pairs.

Time Complexity: O(n)
Space Complexity: O(1)

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, w, h;
    scanf("%ld %ld %ld", &n, &w, &h);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long minshift(-1e9), maxshift(1e9); // Initialize bounds for required shift
    for (long p = 0; p < n; p++) {
      // Compute the required shift range to cover cake p with dispenser p
      long left = (b[p] + h) - (a[p] + w);  // Minimum shift needed
      long right = (b[p] - h) - (a[p] - w); // Maximum shift allowed
      minshift = (minshift > left ? minshift : left); // Update global minimum shift
      maxshift = (maxshift < right ? maxshift : right); // Update global maximum shift
    }
    puts(minshift <= maxshift ? "YES" : "NO"); // Check if valid shift interval exists
  }
}


// https://github.com/VaHiX/codeForces/