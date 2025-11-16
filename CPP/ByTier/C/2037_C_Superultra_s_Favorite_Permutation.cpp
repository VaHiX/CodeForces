// Problem: CF 2037 C - Superultra's Favorite Permutation
// https://codeforces.com/contest/2037/problem/C

/*
Purpose: 
    This code constructs a permutation of length n such that the sum of every two adjacent elements is a composite number.
    The algorithm leverages the fact that odd numbers (except 5) and even numbers can be arranged to avoid prime sums.

    Key insight:
        - For n < 5, it's impossible to construct such a permutation due to constraints on small numbers.
        - The approach separates odd and even numbers, placing odd numbers first (excluding 5),
          then places 5 and 4, followed by even numbers (excluding 4).
        - This arrangement ensures that no adjacent sums result in prime numbers.

Algorithms/Techniques:
    - Greedy construction with specific ordering.
    - Handling edge cases for small n.

Time Complexity: O(n)
    - Each test case processes all numbers from 1 to n a constant number of times, leading to linear time.

Space Complexity: O(1)
    - Only a constant amount of extra space is used, not counting the output.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n < 5) {
      puts("-1");  // For n < 5, impossible to construct valid permutation
      continue;
    }
    // Output all odd numbers from 1 to n, skipping 5
    for (long p = 1; p <= n; p += 2) {
      if (p == 5) {
        continue;
      }
      printf("%ld ", p);
    }
    printf("5 4 ");  // Place 5 and 4 to ensure valid adjacency with previous odds
    // Output all even numbers from 2 to n, skipping 4
    for (long p = 2; p <= n; p += 2) {
      if (p == 4) {
        continue;
      }
      printf("%ld ", p);
    }
    puts("");  // Newline after each permutation
  }
}


// https://github.com/VaHiX/CodeForces/