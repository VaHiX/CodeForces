// Problem: CF 1993 B - Parity and Sum
// https://codeforces.com/contest/1993/problem/B

/*
B. Parity and Sum
Problem Description:
Given an array of positive integers, we can perform operations where we pick two elements with distinct parities (one odd, one even), and replace the smaller one with their sum. The goal is to find the minimum number of such operations to make all elements have the same parity.

Approach:
- Odd numbers cannot be made even through addition with even numbers.
- Even numbers can be changed into odd numbers by adding them to an odd number.
- Strategy:
  1. Collect all even numbers in a vector.
  2. Track the maximum odd number encountered.
  3. If all numbers are already of same parity, return 0.
  4. Otherwise, simulate merging operations to try reducing the count of distinct parities.

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the even numbers in a vector.

Algorithms/Techniques:
- Greedy approach with sorting
- Simulation of parity-changing operations
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
    std::vector<long> v;           // Vector to store all even numbers
    long mxodd(0);                 // Maximum odd number encountered
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % 2) {                 // If x is odd
        mxodd = (mxodd > x ? mxodd : x);  // Update maximum odd number
      } else {                     // If x is even
        v.push_back(x);            // Add to vector of even numbers
      }
    }
    if (v.size() == n) {           // All elements are odd
      puts("0");
      continue;
    }
    sort(v.begin(), v.end());      // Sort even numbers for greedy merging
    long cnt(v.size());            // Initial count of even numbers
    for (long p = 0; p < v.size(); p++) {
      if (mxodd > v.back()) {      // If max odd is greater than largest even, no gain
        break;
      } else if (mxodd < v[p]) {   // If max odd is smaller than current even, merge and increase count
        ++cnt;
        break;
      } else {                     // Add current even to max odd
        mxodd += v[p];
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/