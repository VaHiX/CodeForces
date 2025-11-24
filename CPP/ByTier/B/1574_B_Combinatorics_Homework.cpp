// Problem: CF 1574 B - Combinatorics Homework
// https://codeforces.com/contest/1574/problem/B

/*
B. Combinatorics Homework

Purpose:
This program determines whether it's possible to construct a string consisting of exactly 'a' 'A's, 'b' 'B's, and 'c' 'C's such that there are exactly 'm' adjacent pairs of equal letters.

Approach:
1. For a valid arrangement of letters, we need to check if the number of adjacent equal pairs 'm' is achievable.
2. The minimum number of adjacent equal pairs occurs when letters are grouped as much as possible (i.e., try to minimize total groups).
3. The maximum number of adjacent equal pairs happens when we maximize groupings of same characters.

Algorithms/Techniques:
- Sorting the counts in descending order
- Using greedy grouping logic for min/max pair calculation

Time Complexity: O(1) per test case (sorting 3 elements is constant time)
Space Complexity: O(1) (only using fixed-size vector and variables)

Input Format:
- t: number of test cases
- For each test case: a, b, c, m (counts of letters A, B, C and required adjacent pairs)

Output Format:
- "YES" if valid arrangement exists, otherwise "NO"
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<long> v(3); // Store counts of A, B, C
    long m;
    scanf("%ld %ld %ld %ld", &v[0], &v[1], &v[2], &m); // Read a, b, c, m
    sort(v.rbegin(), v.rend()); // Sort in descending order: v[0] >= v[1] >= v[2]
    long mn = (v[0] - v[1] - v[2] - 1); // Minimum pairs required
    mn = (mn > 0) ? mn : 0; // Ensure non-negative
    long mx = v[0] + v[1] + v[2] - 3; // Maximum possible pairs
    puts(mn <= m && m <= mx ? "YES" : "NO"); // Check if m is within valid range
  }
}


// https://github.com/VaHiX/codeForces/