// Problem: CF 1976 B - Increase/Decrease/Copy
// https://codeforces.com/contest/1976/problem/B

/*
B. Increase/Decrease/Copy
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm/Techniques: Greedy, Array Manipulation

The problem asks to transform array `a` into array `b` using three types of operations:
1. Increase any element in `a` by 1.
2. Decrease any element in `a` by 1.
3. Copy any element from `a` and append it to the end of `a`.

We process elements one by one. For each pair (a[p], b[p]), we calculate:
- The number of operations needed to make a[p] equal to b[p], which is |a[p] - b[p]|.
- If `b[p]` is outside the range [min(a[p], b[p]), max(a[p], b[p])], then we would need to copy 
  an element of `a` and adjust it, which costs extra operations.

The greedy approach ensures that we minimize these over-adjustments.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing arrays a and b

*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long z;
    scanf("%ld", &z);
    long long total(1); // Start with 1 as base operation count
    long f(2e9 + 7); // Initialize with a large value to track minimal adjustment cost
    
    for (long p = 0; p < n; p++) {
      long x = (a[p] < b[p] ? a[p] : b[p]); // Smaller of the two values
      long y = (a[p] > b[p] ? a[p] : b[p]); // Larger of the two values
      total += (y - x); // Add operations to bring a[p] to b[p]

      // If z is outside the range [x, y], we need an extra copy/adjustment
      if (z < x) {
        f = (f < (x - z) ? f : (x - z)); // Update minimal additional cost
      } else if (z > y) {
        f = (f < (z - y) ? f : (z - y)); // Update minimal additional cost
      } else {
        f = 0; // No need to adjust further, z is inside the valid range
      }
    }
    
    total += f;
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/