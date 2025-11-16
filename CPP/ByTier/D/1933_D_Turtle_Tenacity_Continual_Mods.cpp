// Problem: CF 1933 D - Turtle Tenacity: Continual Mods
// https://codeforces.com/contest/1933/problem/D

/*
D. Turtle Tenacity: Continual Mods

Problem Description:
Given an array of integers, determine if we can rearrange its elements such that 
the sequence of repeated modulo operations (from left to right) does not result in 0.

Algorithm:
1. For each test case:
   - Find the minimum element in the array.
   - Count how many times this minimum element appears.
   - If the minimum element appears only once, return "YES".
   - Otherwise, check if any element is not divisible by the minimum element.
     - If such an element exists, return "YES".
     - Otherwise, return "NO".

Time Complexity: O(n) per test case
Space Complexity: O(n) due to the vector storing input array

Techniques:
- Single pass through the array to find minimum and count occurrences
- Check divisibility condition for mod operations
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1e9 + 7), cnt(0); // Initialize min value and count
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      if (a[p] < mn) {         // Update minimum and reset counter
        mn = a[p];
        cnt = 1;
      } else if (a[p] == mn) { // Increment count if equal to current min
        ++cnt;
      }
    }
    if (cnt == 1) {            // If only one occurrence of minimum, possible
      puts("YES");
      continue;
    }
    bool sm(false);            // Flag to check if any element not divisible by mn
    for (long p = 0; !sm && p < n; p++) {
      if (a[p] % mn) {         // If remainder is non-zero, not divisible
        sm = true;
      }
    }
    puts(sm ? "YES" : "NO");   // Output based on divisibility check
  }
}


// https://github.com/VaHiX/codeForces/