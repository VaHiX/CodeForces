// Problem: CF 2102 A - Dinner Time
// https://codeforces.com/contest/2102/problem/A

/*
Problem: Dinner Time

Given four integers n, m, p, and q, determine whether there exists an integer array a1, a2, ..., an
such that:
- The sum of all elements in the array is equal to m.
- The sum of every p consecutive elements is equal to q.

Algorithms/Techniques: Mathematical analysis and condition checking

Time Complexity: O(1) per test case
Space Complexity: O(1)

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, p, q;
    scanf("%ld %ld %ld %ld", &n, &m, &p, &q);
    // Check if the conditions are satisfied:
    // (n % p) checks if array length is not divisible by segment length => impossible to have all segments equal
    // (n * q == m * p) checks if total sum matches expected sum from periodicity
    puts((n % p) || (n * q == m * p) ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/