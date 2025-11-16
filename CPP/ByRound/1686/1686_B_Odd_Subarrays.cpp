// Problem: CF 1686 B - Odd Subarrays
// https://codeforces.com/contest/1686/problem/B

/*
B. Odd Subarrays

Algorithm: Greedy approach to maximize number of odd subarrays.
Time Complexity: O(n) per test case, where n is the size of the permutation.
Space Complexity: O(1), only using a few variables for computation.

The key insight is that we want to split the array into as many "odd" subarrays as possible,
where an odd subarray has an odd number of inversions.

This problem can be solved greedily by observing:
- An array of length 1 always has 0 inversions (even), so it's not odd.
- For a subarray to be odd, it must have an odd number of inversions.
- The strategy is to keep extending a subarray until the inversion count becomes even,
  which means we can make a cut there.

The algorithm works by scanning through the array:
1. Keep track of previous element and a counter for transitions where current element < previous.
2. When we detect such a transition, increment the count of odd subarrays and reset for next.
3. This mimics cutting at optimal points to maximize odd subarrays.

Example:
Input: [4, 3, 2, 1]
When processing: 4 -> 3 (3<4), so cut here, cnt=1
Then from 2 to 1, again 1<2, so another cut, cnt=2
So output = 2
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev(0), cnt(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < prev) {        // If current element is smaller than previous
        ++cnt;               // Increment odd subarray counter
        prev = 0;            // Reset prev to start new subarray
      } else {
        prev = x;            // Else continue subarray
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/