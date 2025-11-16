// Problem: CF 1916 A - 2023
// https://codeforces.com/contest/1916/problem/A

/*
Purpose: Given a sequence b of length n and number k of elements removed from original sequence a,
         determine if a valid sequence a exists such that product of a equals 2023.
         Output "YES" and the k removed elements if valid, otherwise "NO".

Algorithms/Techniques: 
    - Greedy approach: For each element in b, check if it divides the remaining product.
    - If all elements divide evenly, then the last remainder must be the product of removed elements.
    - If any element does not divide, no valid sequence exists.

Time Complexity: O(n) per test case, where n is the size of sequence b.
Space Complexity: O(1), constant extra space used.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long rem(2023);  // Remaining product after removing elements in b
    bool ans(true);  // Flag to track validity of sequence
    while (n--) {
      long b;
      scanf("%ld", &b);
      if (rem % b) {  // If b does not divide rem evenly, no valid sequence
        ans = false;
      } else {
        rem /= b;  // Update rem by dividing with b
      }
    }
    if (ans) {
      puts("YES");
      for (long p = 1; p < k; p++) {  // Print k-1 ones
        printf("1 ");
      }
      printf("%ld\n", rem);  // Print the last element (product of removed elements)
    } else {
      puts("NO");
    }
  }
}


// https://github.com/VaHiX/CodeForces/