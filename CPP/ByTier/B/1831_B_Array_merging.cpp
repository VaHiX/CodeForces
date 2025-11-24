// Problem: CF 1831 B - Array merging
// https://codeforces.com/contest/1831/problem/B

/*
B. Array merging
time limit per test1 second
memory limit per test256 megabytes

Algorithm:
The algorithm processes two arrays a and b of length n, and computes the maximum length of a subarray with equal elements in any possible merge of these arrays.
It works by:
1. For each array separately:
   - Identify consecutive segments of same values (run-length encoding).
   - Store for each unique value, the maximum run length seen so far.
2. For all unique values appearing in both arrays:
   - Combine their max run lengths from both arrays and track maximum.
3. Return the overall maximum.

Time Complexity: O(n)
Space Complexity: O(n)

Input
Each test contains multiple test cases. The first line of input contains a single integer t (1≤t≤10^4) — the number of test cases.
The first line of each test case contains a single integer n (1≤n≤2⋅10^5) — the length of the array a and b.
The second line of each test case contains n integers a1, a2, ..., an (1≤ai≤2⋅n) — the elements of array a.
The third line of each test case contains n integers b1, b2, ..., bn (1≤bi≤2⋅n) — the elements of array b.
It is guaranteed that the sum of n across all test cases does not exceed 2⋅10^5.

Output
For each test case, output the maximum length of a subarray consisting of equal values across all merges.

Example
input
4
1
2
2
3
1 2 3
4 5 6
2
1 2
2 1
5
1 2 2 2 2
2 1 1 1 1
output
2
1
2
5
*/

#include <cstdio>
#include <map>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> a, b;
    long prev(-1), cur(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x != prev) {
        // If current value is different from previous,
        // update the count of run length for previous value
        if (prev > 0 && !a.count(prev) || a[prev] < cur) {
          a[prev] = cur;
        }
        cur = 0;
      }
      ++cur; // Increment current run length
      prev = x;
    }
    // Handle the last run
    if (!a.count(prev) || a[prev] < cur) {
      a[prev] = cur;
    }
    prev = -1;
    cur = 0;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x != prev) {
        // Same logic applied to second array
        if (prev > 0 && !b.count(prev) || b[prev] < cur) {
          b[prev] = cur;
        }
        cur = 0;
      }
      ++cur;
      prev = x;
    }
    // Handle the last run for second array
    if (!b.count(prev) || b[prev] < cur) {
      b[prev] = cur;
    }
    long mx(0);
    // For all values in first map, check if they exist in second map and combine run lengths
    for (std::map<long, long>::iterator it = a.begin(); it != a.end(); it++) {
      long key = it->first;
      long val = it->second;
      if (key > 0 && b.count(key)) {
        val += b[key];
      }
      mx = (mx > val) ? mx : val;
    }
    // For all values in second map, check if they exist in first map and combine run lengths
    for (std::map<long, long>::iterator it = b.begin(); it != b.end(); it++) {
      long key = it->first;
      long val = it->second;
      if (key > 0 && a.count(key)) {
        val += a[key];
      }
      mx = (mx > val) ? mx : val;
    }
    printf("%ld\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/