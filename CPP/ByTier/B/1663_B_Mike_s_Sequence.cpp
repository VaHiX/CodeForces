// Problem: CF 1663 B - Mike's Sequence
// https://codeforces.com/contest/1663/problem/B

#include <cstdio>

/*
B. Mike's Sequence
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
You won't find this sequence on OEIS.

This code implements a lookup-based solution to find the smallest value in a predefined array
that is greater than or equal to the input value. It uses a reverse linear search approach,
starting from the largest index and moving backwards until it finds the first element
that is less than or equal to the input value. The algorithm then returns the next element
in the sequence (the one at index p).

Time Complexity: O(N) where N is the size of the lookup array (10 in this case)
Space Complexity: O(1) - only using a constant amount of extra space
*/

int main() {
  const long N = 10;  // Size of the lookup array
  const long w[] = {-1000, 1200, 1400, 1600, 1900,
                    2100,  2300, 2400, 2600, 3000};  // Predefined sequence
  long x;
  scanf("%ld", &x);  // Read input value
  for (long p = N - 1; p > 0; p--) {  // Loop from highest index to 1
    if (x >= w[p - 1]) {  // If input is greater than or equal to previous element
      printf("%ld\n", w[p]);  // Print the current element (next in sequence)
      break;  // Exit loop once found
    }
  }
}

// https://github.com/VaHiX/codeForces/