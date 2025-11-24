// Problem: CF 1842 B - Tenzing and Books
// https://codeforces.com/contest/1842/problem/B

/*
B. Tenzing and Books

Algorithm:
The problem involves determining whether it's possible to achieve a target knowledge value x using bitwise OR operations on books from three stacks. The key insight is that for a book to be useful in achieving x, its bits must be a subset of the bits in x (i.e., (x | book) == x). For each stack, we check if all books in that stack can contribute towards the result. If so, we compute the OR of those books and see if it's possible to get x.

Time Complexity: O(n) per test case, since for each of the 3 stacks, we iterate n times.
Space Complexity: O(1), only a constant amount of extra space is used.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    long k(0); // k will accumulate the OR of valid books from each stack
    for (long u = 0; u < 3; u++) { // Process three stacks
      bool read = true; // Flag to track if we can use this stack
      for (long p = 0; p < n; p++) {
        long cur;
        scanf("%ld", &cur);
        // Check if current book can be used (its bits must be subset of x's bits)
        if ((x | cur) != x) {
          read = false;
        }
        // If this stack is still valid, update k with OR of books in it
        if (read) {
          k |= cur;
        }
      }
    }
    puts(x == k ? "Yes" : "No"); // Output result based on whether final k equals x
  }
}


// https://github.com/VaHiX/codeForces/