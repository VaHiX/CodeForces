// Problem: CF 1612 G - Max Sum Array
// https://codeforces.com/contest/1612/problem/G

/*
 * Problem: Max Sum Array
 * 
 * Purpose: Given an array c of m integers, we construct an array a of length sum(c)
 *          using integers from 1 to m, where each integer i appears exactly c[i] times.
 *          We want to maximize the sum of distances between equal elements in a.
 * 
 * Algorithm:
 *  - The key insight is that for each element with count c[i], the maximum total distance
 *    is achieved by placing all occurrences of that element as far apart as possible.
 *  - This arrangement leads to a quadratic sum of distances.
 *  - The approach uses difference arrays to compute the distances efficiently,
 *    followed by combinatorial calculation for counting valid arrangements.
 * 
 * Time Complexity: O(m + max(c_i)) where m is size of array c and max(c_i) is maximum element in c
 * Space Complexity: O(max(c_i)) for storing the difference array and factorials
 * 
 * Techniques:
 *  - Difference array technique
 *  - Modular arithmetic
 *  - Combinatorial counting
 */

#include <iostream>

using namespace std;
const int P = 1e9 + 7, N = 1e6 + 9, O = 1e6 + 5, iv = P + 1 >> 1;
int S[N * 2], *s = S + N, jc[N];  // S is used for difference array, jc for factorials
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int m, i, ans = 0, way = 1;
  long long sum = 0;
  // Read input and update difference array
  for (cin >> m; m--;) {
    cin >> i;
    ++s[1 - i], --s[1 + i];  // Mark start and end of intervals for elements
  }
  // Precompute factorials
  jc[0] = 1;
  for (i = 1; i < N; ++i)
    jc[i] = jc[i - 1] * 1ll * i % P;
  // Convert difference array to actual values
  for (i = -O; i < O; ++i)
    s[i] += s[i - 2];
  // Compute answer and count of ways
  for (i = -O; i < O; ++i) {
    way = way * 1ll * jc[s[i]] % P;  // Multiply by factorial of count of element i
    ans = (ans + (sum + 1 + sum + s[i]) % P * s[i] % P * iv % P * i) % P;  // Add contribution to the max sum
    sum += s[i];  // Update cumulative sum
  }
  cout << (ans + P) % P << ' ' << way;
  return 0;
}


// https://github.com/VaHiX/CodeForces/