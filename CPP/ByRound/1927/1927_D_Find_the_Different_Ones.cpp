// Problem: CF 1927 D - Find the Different Ones!
// https://codeforces.com/contest/1927/problem/D

/*
Algorithm/Techniques: Prefix processing with sliding window logic to find first differing element
Time Complexity: O(n + q) per test case, where n is array length and q is number of queries
Space Complexity: O(n) for the prefix vector v

This solution pre-processes the array to efficiently answer queries about whether there exists
a pair of different elements in a given range [l, r]. It uses a prefix vector v such that
v[i] stores the index of the first element before or at i which is different from a[i].
This allows answering each query in O(1) time.
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n + 1, 0); // Vector to store prefix information
    long prev(0); // To keep track of the previous element
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      if (x != prev) {
        // If current element is different from previous, store index of previous
        v[p] = p - 1;
      } else {
        // If same as previous, carry forward the index of the first different element
        v[p] = v[p - 1];
      }
      prev = x; // Update previous to current
    }
    long q;
    scanf("%ld", &q);
    while (q--) {
      long l, r;
      scanf("%ld %ld", &l, &r);
      if (v[r] < l) {
        // No different element found in range [l, r]
        puts("-1 -1");
      } else {
        // v[r] gives the index of an element that differs from a[r] and is within range
        printf("%ld %ld\n", v[r], r);
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/