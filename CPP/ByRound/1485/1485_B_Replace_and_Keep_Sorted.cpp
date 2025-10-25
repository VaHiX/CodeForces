// Problem: CF 1485 B - Replace and Keep Sorted
// https://codeforces.com/contest/1485/problem/B

/*
B. Replace and Keep Sorted
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Given a positive integer k, two arrays are called k-similar if:
- they are strictly increasing;
- they have the same length;
- all their elements are positive integers between 1 and k (inclusive);
- they differ in exactly one position.

You are given an integer k, a strictly increasing array a and q queries. For each query, you are given two integers l_i <= r_i. Your task is to find how many arrays b exist, such that b is k-similar to array [a_{l_i},a_{l_i+1}...,a_{r_i}].

Algorithm:
The key insight is that for a subarray [a[l], ..., a[r]] we can replace any element a[i] with another value from 1 to k, as long as the resulting array remains strictly increasing. The formula computes the count based on valid replacements considering both ends and inner elements.

Time Complexity: O(n + q)
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
int main() {
  long n, q, k;
  scanf("%ld %ld %ld", &n, &q, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]); // Read array elements
  }
  while (q--) {
    long l, r;
    scanf("%ld %ld", &l, &r); // Read query range
    // Calculate the number of valid k-similar arrays
    long ans = k + (a[r - 1] - a[l - 1] + 1) - 2 * (r - l + 1);
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/