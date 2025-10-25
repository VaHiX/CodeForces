// Problem: CF 1692 G - 2^Sort
// https://codeforces.com/contest/1692/problem/G

/*
G. 2^Sort
Algorithms/Techniques: Sliding window with preprocessing to check valid subsequences.
Time Complexity: O(n) amortized per test case, where n is the length of array a.
Space Complexity: O(n) for the vector a.

Given an array a of length n and an integer k, find the number of indices 
1 <= i <= n - k such that the subarray [a_i, ..., a_{i+k}] with length k+1 
has the property: 2^0 * a_i < 2^1 * a_{i+1} < ... < 2^k * a_{i+k}.
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long last(0), cnt(0);
    for (long p = 1; p < n; p++) {
      // If current element is at most half of previous, we update last
      if (a[p - 1] >= 2 * a[p]) {
        last = p;
      } else if (p >= last + k) {
        // If we have moved past k positions from last invalid point,
        // then valid subarray starting at 'last' and ending at current position exists
        ++cnt;
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/