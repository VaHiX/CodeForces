// Problem: CF 1401 B - Ternary Sequence
// https://codeforces.com/contest/1401/problem/B

/*
B. Ternary Sequence
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

You are given two sequences a_1, a_2, ..., a_n and b_1, b_2, ..., b_n. Each element of both sequences is either 0, 1 or 2.
The number of elements 0, 1, 2 in the sequence a is x_1, y_1, z_1 respectively, and the number of elements 0, 1, 2 in the sequence b is x_2, y_2, z_2 respectively.

You can rearrange the elements in both sequences a and b however you like. After that, let's define a sequence c as follows:
c_i = { a_i * b_i   if a_i > b_i
       0           if a_i = b_i
       -a_i * b_i   if a_i < b_i

You'd like to make sum of all elements of the sequence c as large as possible. What is the maximum possible sum?

Algorithms/Techniques:
Greedy approach to maximize the sum by optimally placing 2s and 1s in sequences to get positive contributions 
and placing 0s strategically.

Time Complexity: O(1) per test case - constant number of operations regardless of input size.
Space Complexity: O(1) - only a few variables used, independent of input size.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x0, x1, x2, y0, y1, y2;
    scanf("%lld %lld %lld", &x0, &x1, &x2); // Read counts of 0s, 1s, 2s in sequence a
    scanf("%lld %lld %lld", &y0, &y1, &y2); // Read counts of 0s, 1s, 2s in sequence b
    
    ll res(0), q(0);
    
    // Match 2s from a with 1s from b to get maximum positive contribution (2 * 1 = 2)
    q = (x2 < y1) ? x2 : y1;
    res += 2 * q;
    x2 -= q;
    y1 -= q;
    
    // Match remaining 2s from a with 2s from b to get no contribution (2 * 2 = 4 -> -4, but we just don't add anything)
    q = (x2 < y2) ? x2 : y2;
    res += 0 * q; // No contribution from matching 2s
    x2 -= q;
    y2 -= q;
    
    // Match remaining 2s from a with 0s from b - no contribution (2 * 0 = 0)
    q = (x2 < y0) ? x2 : y0;
    res += 0 * q;
    x2 -= q;
    y0 -= q;
    
    // Match remaining 0s from a with 2s from b - no contribution
    q = (x0 < y2) ? x0 : y2;
    res += 0 * q;
    x0 -= q;
    y2 -= q;
    
    // Match remaining 0s from a with 0s from b - no contribution
    q = (x0 < y0) ? x0 : y0;
    res += 0 * q;
    x0 -= q;
    y0 -= q;
    
    // Match remaining 0s from a with 1s from b - no contribution (0 * 1 = 0)
    q = (x0 < y1) ? x0 : y1;
    res += 0 * q;
    x0 -= q;
    y1 -= q;
    
    // Match remaining 1s from a with 0s from b - no contribution
    q = (x1 < y0) ? x1 : y0;
    res += 0 * q;
    x1 -= q;
    y0 -= q;
    
    // Match remaining 1s from a with 1s from b - no contribution (1 * 1 = 1 -> 0)
    q = (x1 < y1) ? x1 : y1;
    res += 0 * q;
    x1 -= q;
    y1 -= q;
    
    // Match remaining 1s from a with 2s from b to get negative contribution (-1 * 2 = -2)
    q = (x1 < y2) ? x1 : y2;
    res -= 2 * q; // Subtract because c_i = -a_i * b_i
    x1 -= q;
    y2 -= q;
    
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/