// Problem: CF 1438 A - Specific Tastes of Andre 
// https://codeforces.com/contest/1438/problem/A

/*
Purpose: This code generates a "perfect" array of length n for each test case.
         A perfect array is one where every nonempty subarray has a sum divisible by its length.
         The approach is to output an array of n ones, because:
         - Any subarray of length k will have sum k (since all elements are 1)
         - k is always divisible by k, hence all subarrays are "good"
         - All elements are within the allowed range [1, 100]

Algorithms/Techniques: Trivial construction using constant values (1s)

Time Complexity: O(n) per test case, where n is the input size.
Space Complexity: O(1) excluding the output space.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      printf("1 "); // Print 1 for each position to ensure all subarrays are good
    }
    puts(""); // Print newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/