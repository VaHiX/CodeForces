// Problem: CF 2021 B - Maximize Mex
// https://codeforces.com/contest/2021/problem/B

/*
Purpose: This code solves the problem of maximizing the MEX (minimum excluded value) of an array
         after performing a specific operation any number of times. The operation allows increasing
         any element of the array by a fixed value x.

Algorithm:
    - For each element in the array, we calculate how many times it appears in the array
      in a frequency table, but only for elements less than n (since MEX cannot exceed n).
    - We then greedily process the frequencies starting from 0, to determine the smallest
      non-negative integer not present in the array. When we find a gap, we update the
      MEX value.
    - For optimization, we propagate frequencies to elements that are x positions ahead,
      allowing us to build longer sequences of available numbers.

Time Complexity: O(n), where n is the size of the input array.
Space Complexity: O(n), for the frequency vector of size n.

Techniques:
    - Frequency counting
    - Greedy update propagation
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> v(n, 0);  // Frequency vector to store counts of elements less than n
    for (long p = 0; p < n; p++) {
      long b;
      scanf("%ld", &b);
      if (b < n) {  // Only consider elements less than n for frequency counting
        ++v[b];
      }
    }
    long mex(n);  // Initialize mex to n (worst case, all values from 0 to n-1 are present)
    for (long p = 0; p < n; p++) {
      if (!v[p]) {  // If count of value p is zero, then p is the mex
        mex = p;
        break;
      }
      // Propagate frequency to next position (p + x) to simulate operations
      if (p + x < n) {
        v[p + x] += (v[p] - 1);
      }
    }
    printf("%ld\n", mex);
  }
}


// https://github.com/VaHiX/CodeForces/