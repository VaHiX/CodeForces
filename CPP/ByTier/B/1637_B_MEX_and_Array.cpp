// Problem: CF 1637 B - MEX and Array
// https://codeforces.com/contest/1637/problem/B

/*
B. MEX and Array
Algorithms/Techniques: Dynamic Programming, Prefix Sum, MEX computation
Time Complexity: O(n^2) per test case
Space Complexity: O(1)

This code computes the sum of the "value" of all subsegments of an array.
The value of a subsegment is defined as the maximum cost over all possible partitions
of that subsegment, where the cost is the number of segments plus the sum of MEX
over each segment. For each element in the array, we compute its contribution to
the total sum by calculating how many times it contributes to the MEX of various
subsegments.

The algorithm uses a nested loop to iterate through all possible subsegments,
and for each subsegment, it calculates the sum of MEX values across all possible
partitions. It optimizes the process by precomputing contributions based on
the position of elements and their relationship with zero.

Key observations:
- If an element is 0, it contributes to the MEX of a subsegment.
- The formula used calculates contribution weighted by segment positions and lengths.
*/

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    ll res(0);  // Initialize result
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // Contribution of element at position p to the total sum:
      // (1 + (x == 0)) accounts for whether 0 is present in current segment
      // (p + 1) and (n - p) represent left and right segment sizes
      res += (1 + (x == 0)) * (p + 1) * (n - p);
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/