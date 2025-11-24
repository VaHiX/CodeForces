// Problem: CF 1174 C - Ehab and a Special Coloring Problem
// https://codeforces.com/contest/1174/problem/C

/*
C. Ehab and a Special Coloring Problem
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
You're given an integer n. For every integer i from 2 to n, assign a positive integer a_i such that the following conditions hold:
 
 For any pair of integers (i,j), if i and j are coprime, a_i != a_j. 
 The maximal value of all a_i should be minimized (that is, as small as possible). 
A pair of integers is called coprime if their greatest common divisor is 1.
Input
The only line contains the integer n (2 <= n <= 10^5).
Output
Print n-1 integers, a_2, a_3, ..., a_n (1 <= a_i <= n). 
If there are multiple solutions, print any of them.
Examples
Input

4

Output

1 2 1 
Input

3

Output

2 1
Note
In the first example, notice that 3 and 4 are coprime, so a_3 != a_4. Also, notice that a=[1,2,3] satisfies the first condition, but it's not a correct answer because its maximal value is 3.

Algorithm: Sieve-based coloring approach.
Time Complexity: O(n log log n)
Space Complexity: O(n)
*/
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1, 0); // Initialize array to store color of each number
  long cur(1); // Current color index
  for (long p = 2; p * p <= n; p++) { // Iterate through primes up to sqrt(n)
    if (a[p]) { // If already colored, skip
      continue;
    }
    a[p] = cur++; // Assign new color to prime p
    for (long q = 2 * p; q <= n; q += p) { // For all multiples of p
      a[q] = (a[q] ? a[q] : a[p]); // If not yet colored, color it with same color as p
    }
  }
  for (long p = 2; p <= n; p++) { // Print colors for numbers from 2 to n
    printf("%ld ", a[p] ? a[p] : (cur++)); // If already colored, use that color, else assign new color
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/