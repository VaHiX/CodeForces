// Problem: CF 1743 B - Permutation Value
// https://codeforces.com/contest/1743/problem/B

/*
Code Purpose:
This code constructs a permutation of size n with the minimum possible value.
The value of a permutation is defined as the number of its subsegments that are also permutations.
The algorithm used is to place 1 at the beginning, followed by the numbers from n down to 2 in descending order.
This arrangement minimizes the number of subsegments that are permutations.

Algorithms/Techniques:
- Greedy approach to construct the permutation
- Simple loop to generate the required order

Time Complexity: O(n) per test case, where n is the size of the permutation.
Space Complexity: O(1) extra space, not counting the output storage.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("1 "); // Start with 1 to minimize subsegment permutations
    for (long p = n; p > 1; p--) {
      printf("%ld ", p); // Print numbers from n down to 2
    }
    puts(""); // New line after each permutation
  }
}


// https://github.com/VaHiX/CodeForces/