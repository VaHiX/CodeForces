// Problem: CF 1205 A - Almost Equal
// https://codeforces.com/contest/1205/problem/A

/*
A. Almost Equal
Time complexity: O(n)
Space complexity: O(n)

Algorithm/Techniques:
This problem asks to arrange numbers 1 to 2n in a circle such that when we take sums of every n consecutive elements,
all these sums differ by at most 1. 

The approach works only for odd n:
- For odd n, we can construct a valid arrangement by interleaving two sequences.
- The first sequence starts with 1 and increases by 2: 1, 3, 5, ...
- The second sequence starts with 2 and increases by 2: 2, 4, 6, ...
- We interleave these sequences to form a pattern that ensures sums are nearly equal.
- If n is even, it's impossible to construct such an arrangement.

Key steps:
1. Check if n is odd. If even, print "NO".
2. If odd:
   - Create a vector of size 2*n.
   - Fill the vector by alternating elements from two sequences.
   - Print the result.
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  if (n % 2) { // if n is odd
    puts("YES");
    std::vector<long> a(2 * n); // create vector of size 2*n
    for (long p = 0; p < n; p++) {
      if (p % 2) { // if p is odd
        a[p] = 2 * p + 2;     // assign even number from second sequence
        a[p + n] = 2 * p + 1; // assign odd number from first sequence
      } else { // if p is even
        a[p] = 2 * p + 1;     // assign odd number from first sequence
        a[p + n] = 2 * p + 2; // assign even number from second sequence
      }
    }
    for (long p = 0; p < 2 * n; p++) {
      printf("%ld ", a[p]); // print all elements
    }
    puts("");
  } else {
    puts("NO"); // if n is even, no solution exists
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/