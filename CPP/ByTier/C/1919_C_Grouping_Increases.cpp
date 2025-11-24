// Problem: CF 1919 C - Grouping Increases
// https://codeforces.com/contest/1919/problem/C

/*
C. Grouping Increases
time limit per test1 second
memory limit per test256 megabytes

Problem Description:
Given an array of integers, split it into two subsequences such that the sum of penalties (number of increasing transitions) in both subsequences is minimized.

Algorithm:
- The approach uses a greedy method with two variables to track the smallest elements seen so far in each subsequence.
- For each element in the array, we decide whether to place it in the first or second subsequence based on how it compares to the current minimums in both.
- This ensures we minimize the number of increasing transitions globally.

Time Complexity: O(n) per test case
Space Complexity: O(1)

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long preva(1e9), prevb(1e9), cnt(0);
    // preva and prevb keep track of the smallest values seen so far in each subsequence
    while (n--) {
      long x;
      scanf("%ld", &x);
      if (x <= preva) {
        // Place x in subsequence a (smaller or equal to current minimum)
        preva = x;
      } else if (x <= prevb) {
        // Place x in subsequence b (smaller or equal to current minimum of b)
        prevb = x;
      } else {
        // Must create a new transition, move the previous b to a, and add to count
        preva = prevb;
        prevb = x;
        ++cnt;
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/