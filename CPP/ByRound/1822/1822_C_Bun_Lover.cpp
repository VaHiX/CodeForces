// Problem: CF 1822 C - Bun Lover
// https://codeforces.com/contest/1822/problem/C

/*
C. Bun Lover
Purpose: Calculate the total length of the chocolate layer in a cinnabon roll of size n.
Algorithms/Techniques: Mathematical formula derivation based on spiral pattern growth.

The problem models a square cinnabon roll of side length n, where chocolate forms a spiral pattern.
Each new layer adds to the total chocolate length in a predictable manner.
From analysis, the formula for total chocolate length is derived as:
res = 1 + (n + 1)^2

Time Complexity: O(1) per test case
Space Complexity: O(1)

Input:
- First line: number of test cases t
- Next t lines: each contains an integer n (size of cinnabon roll)

Output:
- For each test case, output the total length of chocolate layer.
*/

#include <cstdio>
typedef long long ll;

int main() {
  long t; // Number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll n; // Size of cinnabon roll
    scanf("%lld", &n);
    ll res = 1 + (n + 1) * (n + 1); // Formula for chocolate length
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/