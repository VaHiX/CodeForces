// Problem: CF 1736 C1 - Good Subarrays (Easy Version)
// https://codeforces.com/contest/1736/problem/C1

/*
C1. Good Subarrays (Easy Version)
Algorithms/Techniques: Prefix sum, sliding window concept with maintaining minimums.

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(1), only using a few variables for computation.

This problem asks to count the number of subarrays that are "good".
A good subarray means for each element at position i (1-indexed), it must be >= i.
We use an approach where we maintain a running minimum of valid elements and
accumulate the count of good subarrays ending at each position.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0);                    // s represents the current minimum valid length for a good subarray ending here
    long long cnt(0);             // cnt stores total count of good subarrays
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++s;                        // increment the potential length
      s = (s < x ? s : x);        // update s to be the minimum of current s and x
      cnt += s;                   // add current s to total count
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/