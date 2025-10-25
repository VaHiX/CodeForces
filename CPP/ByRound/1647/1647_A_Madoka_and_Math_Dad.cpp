// Problem: CF 1647 A - Madoka and Math Dad
// https://codeforces.com/contest/1647/problem/A

/*
A. Madoka and Math Dad
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Madoka finally found the administrator password for her computer. Her father is a well-known popularizer of mathematics, so the password is the answer to the following problem.
Find the maximum decimal number without zeroes and with no equal digits in a row, such that the sum of its digits is n.
Algorithm/Techniques: Greedy approach
Time complexity: O(n) per test case
Space complexity: O(1) excluding output space
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 3 == 1) {
      printf("1");  // Start with '1' to reduce remainder to multiple of 3
      --n;          // Decrease remaining sum
    }
    while (n > 0) {
      printf("2");     // Use '2' as much as possible for larger digits
      n -= 2;          // Subtract 2 from remaining sum
      if (n <= 0) {
        break;         // Stop if no more digits to add
      }
      printf("1");     // Alternate with '1'
      n -= 1;          // Subtract 1 from remaining sum
    }
    puts("");          // Print newline after each number
  }
}


// https://github.com/VaHiX/codeForces/