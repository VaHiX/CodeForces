// Problem: CF 1036 D - Vasya and Arrays
// https://codeforces.com/contest/1036/problem/D

/*
D. Vasya and Arrays
Algorithms/Techniques: Prefix sum, map, two pointers

Time Complexity: O(n + m)
Space Complexity: O(n + m)

The problem asks to make two arrays equal by merging consecutive elements 
into their sums, maximizing the final array length.

Approach:
1. Compute prefix sums of both arrays.
2. For each possible prefix length of the first array, check if there's a 
   matching prefix in the second array with the same sum.
3. Use a map to store the frequency of prefix sums from the first array.
4. Iterate through the second array and keep a running sum.
5. If at any point the current sum matches a prefix sum from the first array,
   increment answer counter.
6. The final result is the maximum matching prefix length, or -1 if impossible.

*/

#include <stdio.h>
#include <iostream>
#include <map>

typedef long long l;
using namespace std;
#define z() for (l i = 0, r; i < n; i++)
#define k(i) scanf("%lld", &i)
l n, s, q, a;
map<l, l> x;

int main() {
  k(n); // Read length of array A
  z() { // Process each element of array A
    k(r); // Read current element
    x[s += r]++; // Add prefix sum to map and update running prefix sum
  }
  k(n); // Read length of array B
  z() { // Process each element of array B
    k(r); // Read current element
    a += x[q += r]; // Check if current prefix sum matches any from A, add count
  }
  cout << ((q != s) ? -1 : a); // If last sums don't match, impossible; else output result
}


// https://github.com/VaHiX/codeForces/