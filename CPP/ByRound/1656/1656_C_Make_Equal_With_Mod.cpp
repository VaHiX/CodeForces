// Problem: CF 1656 C - Make Equal With Mod
// https://codeforces.com/contest/1656/problem/C

/*
C. Make Equal With Mod
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Problem Description:
Given an array of non-negative integers, determine if it's possible to make all elements equal by repeatedly applying the operation: choose an integer x >= 2 and replace each number with a_i % x.

Algorithm:
- Sort the array first.
- If there is any element with value 1, then we check if there are consecutive integers. 
  If consecutive integers exist, it's impossible to make all elements equal via modulo operations.
- The key insight is that for two numbers a and b, if a % x = b % x for some x >= 2,
  then (a - b) is divisible by x. But if there are consecutive integers in sorted array,
  we cannot make them equal using modulo operation with same x.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for the vector storage
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    bool one(false);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      if (a[p] == 1) {
        one = true;
      }
    }
    sort(a.begin(), a.end()); // Sort the array to easily check consecutive elements
    bool res(true);
    for (long p = 1; one && res && p < n; p++) {
      if (a[p] == 1 + a[p - 1]) { // Check for consecutive integers
        res = false;
        break;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/