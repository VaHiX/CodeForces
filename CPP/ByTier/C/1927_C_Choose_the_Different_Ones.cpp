// Problem: CF 1927 C - Choose the Different Ones!
// https://codeforces.com/contest/1927/problem/C

/*
C. Choose the Different Ones!
Algorithm: Greedy + Counting
Time Complexity: O(n + m + k) per test case
Space Complexity: O(k) per test case

We are given two arrays a and b, and a number k.
We need to choose exactly k/2 elements from each array such that every integer from 1 to k is included.
This means:
- We must have at least one element from 1 to k in each array
- The union of chosen elements from both arrays must cover all numbers from 1 to k

Approach:
1. For each test case, we use two boolean vectors a and b of size k+1 to mark which numbers are present in array a and b.
2. Count numbers that:
   - Are present in both arrays (w)
   - Are present only in array a (u)
   - Are present only in array b (v)
3. If any number from 1 to k is missing in both arrays, return NO.
4. Check if we can satisfy the constraint: 
   - u + w >= k/2 (at least k/2 elements from a must be usable)
   - v + w >= k/2 (at least k/2 elements from b must be usable)
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    std::vector<bool> a(k + 1, 0), b(k + 1, 0); // Mark presence of numbers in arrays a and b
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x <= k) {
        a[x] = 1; // Mark number x as present in array a
      }
    }
    for (long p = 0; p < m; p++) {
      long x;
      scanf("%ld", &x);
      if (x <= k) {
        b[x] = 1; // Mark number x as present in array b
      }
    }
    bool possible(true);
    long u(0), v(0), w(0); // u: only in a, v: only in b, w: in both
    for (long p = 1; possible && p <= k; p++) {
      if (a[p] && b[p]) {
        ++w; // Number present in both arrays
      } else if (a[p]) {
        ++u; // Number present only in array a
      } else if (b[p]) {
        ++v; // Number present only in array b
      } else {
        possible = false; // Number not present in either array
      }
    }
    // Check if we can distribute numbers to satisfy k/2 from each array
    possible = possible && (u + w >= k / 2) && (v + w >= k / 2);
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/