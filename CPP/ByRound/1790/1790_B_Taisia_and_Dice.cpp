// Problem: CF 1790 B - Taisia and Dice
// https://codeforces.com/contest/1790/problem/B

/*
Algorithm/Technique: Greedy approach with constructive strategy
Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input/output storage

This code solves the problem of reconstructing a sequence of dice rolls
given the total sum 's', the sum after removing one maximum die 'r',
and the number of dice 'n'. 

The approach is:
1. Calculate the value of the removed die: u = s - r.
2. Fill the remaining positions with values such that their sum equals r,
   using a greedy method to assign the largest possible value (up to u) 
   to each position, ensuring the total adds up correctly.

The key idea is to place the maximum value 'u' first, then distribute the 
remaining sum 'r' among the rest of the positions greedily.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, s, r;
    scanf("%ld %ld %ld", &n, &s, &r);
    long u = s - r;  // Value of the removed die (maximum die)
    printf("%ld ", u);  // Print the removed die value first
    
    // Distribute the remaining sum 'r' among the remaining n-1 dice
    for (long p = n - 1; p >= 1; p--) {
      long a = r - p + 1;  // Calculate how much we can assign without exceeding remaining sum
      a = (a < u ? a : u);  // Ensure we don't exceed the maximum value u
      printf("%ld ", a);  // Print assigned value
      r -= a;  // Reduce remaining sum
    }
    puts("");  // Newline after each test case
  }
}


// https://github.com/VaHiX/CodeForces/