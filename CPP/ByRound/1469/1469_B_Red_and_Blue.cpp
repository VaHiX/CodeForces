// Problem: CF 1469 B - Red and Blue
// https://codeforces.com/contest/1469/problem/B

/*
B. Red and Blue
Algorithm: 
  - For each test case, we are given two sequences r (red) and b (blue).
  - The goal is to interleave these two sequences to maximize the prefix sum maximum of the combined sequence.
  - This is equivalent to finding the maximum subarray sum for each sequence independently using Kadane's algorithm variant (but we allow the sum to be zero).
  - We compute:
    * Maximum prefix sum (msr) for red sequence r
    * Maximum prefix sum (msb) for blue sequence b
  - Then, the answer is msr + msb.
Time Complexity: O(n + m) per test case.
Space Complexity: O(1).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long sr(0), msr(0); // sr = current prefix sum, msr = max prefix sum for red
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      sr += x;         // Add x to current prefix sum
      msr = (msr > sr) ? msr : sr;  // Update max prefix sum if needed
    }
    long m;
    scanf("%ld", &m);
    long sb(0), msb(0); // sb = current prefix sum, msb = max prefix sum for blue
    for (long p = 0; p < m; p++) {
      long x;
      scanf("%ld", &x);
      sb += x;         // Add x to current prefix sum
      msb = (msb > sb) ? msb : sb;  // Update max prefix sum if needed
    }
    printf("%ld\n", msr + msb);  // Final answer is sum of both maximum prefix sums
  }
}


// https://github.com/VaHiX/codeForces/