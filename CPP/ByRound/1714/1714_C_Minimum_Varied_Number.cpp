// Problem: CF 1714 C - Minimum  Varied Number
// https://codeforces.com/contest/1714/problem/C

/*
C. Minimum Varied Number
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Find the minimum number with the given sum of digits s such that 
all digits in it are distinct (i.e. all digits are unique).
For example, if s=20, then the answer is 389. This is the minimum number in which all digits are different and the sum of the digits is 20 (3+8+9=20).

Algorithm: Greedy approach
- To get the minimum number with given digit sum, we want to:
  1. Use as few digits as possible
  2. Place smaller digits in higher positions (rightmost) for minimum value
- We iterate from largest digit (9) to smallest (1)
- For each digit p, if it can be used (p <= remaining_sum), we use it
- This ensures we place larger digits at the beginning (left) and smaller at end (right) 
- Time Complexity: O(s) where s is the sum, since we iterate from 9 down to 1 at most s times
- Space Complexity: O(1) - only using constant extra space

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long s;
    scanf("%ld", &s);
    long long res(0);     // Result number being built
    long long pow(1);     // Power of 10 to place digits correctly
    for (long p = 9; p > 0; p--) {  // Try digits from 9 down to 1
      if (p > s) {        // If current digit is larger than remaining sum, skip it
        continue;
      }
      res += pow * p;     // Add this digit to result at correct position
      pow *= 10;          // Move to next higher position
      s -= p;             // Reduce remaining sum
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/