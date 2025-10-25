// Problem: CF 1541 A - Pretty Permutations
// https://codeforces.com/contest/1541/problem/A

/*
Problem: Pretty Permutations
Algorithm/Technique: Greedy approach to generate a permutation where no element remains in its original position,
                    minimizing total movement distance.

Approach:
- For even n: Swap adjacent elements in pairs (1,2), (3,4), etc.
- For odd n: Start with 3,1,2 and then swap pairs (4,5), (6,7), etc.
This ensures minimal distance moved and no element stays at its original index.

Time Complexity: O(n) for each test case
Space Complexity: O(1) additional space (excluding output)

Input: Number of test cases t, followed by t integers n (2 <= n <= 100)
Output: A permutation of 1 to n such that:
        - No cat is in its original position
        - Total movement distance is minimized

Example:
n=2: 2 1
n=3: 3 1 2
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long start(1); // Starting position for the loop
    if (n % 2) {   // If n is odd, handle first three elements specially
      start = 4;   // Start from 4 since 1,2,3 are handled separately
      printf("3 1 2 "); // Special case for odd n: place 3 at position 1, 1 at 2, 2 at 3
    }
    for (long p = start; p < n; p += 2) { // Process pairs of elements
      printf("%ld %ld ", p + 1, p);        // Print swapped pair (e.g., 2,1 then 4,3)
    }
    puts(""); // New line after each test case output
  }
}


// https://github.com/VaHiX/codeForces/