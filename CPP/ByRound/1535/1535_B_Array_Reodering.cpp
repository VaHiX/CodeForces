// Problem: CF 1535 B - Array Reodering
// https://codeforces.com/contest/1535/problem/B

/*
B. Array Reodering
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

You are given an array a consisting of n integers.
Let's call a pair of indices i, j good if 1 ≤ i < j ≤ n and gcd(a_i, 2a_j) > 1.
Find the maximum number of good index pairs if you can reorder the array a in an arbitrary way.

Algorithm:
- Separate odd and even numbers into two groups: v for even, w for odd
- For each pair (even, even), we get (v.size() * (v.size() - 1) / 2) good pairs
- For each pair (even, odd), we get v.size() * w.size() good pairs
- For each pair (odd, odd), compute gcd and count if greater than 1

Time Complexity: O(n^2 + n*log(max(a))) where n is the size of array
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v, w; // v stores even numbers, w stores odd numbers
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      x % 2 ? w.push_back(x) : v.push_back(x); // separate odds and evens
    }
    long cnt(0);
    // count all pairs where one element is even and other is any
    cnt += v.size() * (v.size() - 1) / 2 + v.size() * w.size();
    // check all pairs of odd numbers for gcd > 1
    for (long p = 0; p < w.size(); p++) {
      for (long q = p + 1; q < w.size(); q++) {
        cnt += (gcd(w[p], w[q]) > 1);
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/