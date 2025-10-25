// Problem: CF 1840 B - Binary Cafe
// https://codeforces.com/contest/1840/problem/B

/*
B. Binary Cafe
Algorithm/Techniques: Bit manipulation, mathematical observation
Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1)

The problem asks for the number of ways to select desserts such that their total cost does not exceed n.
Each dessert i costs 2^i coins. Since we can only pick each dessert once, this becomes a subset sum problem
where the available items are powers of two up to k.

Key insight:
- Each dessert costs 2^i, meaning one item per bit position in binary representation.
- For any number of coins n and k desserts, if k >= 30, all possible subsets of desserts costing less than or equal to n 
  can be considered (since 2^30 > 1e9).
- If k < 30, then we limit the maximum dessert index.
- The total valid combinations is simply min(n + 1, 2^k), because:
  - If n+1 <= 2^k, all numbers from 0 to n can be formed using the available powers of 2.
  - Otherwise, 2^k different subsets are possible (all subsets up to k-th power of 2).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    k = (k < 30 ? k : 30); // Limit k to avoid overflow; 2^30 > 1e9
    long m = (1 << k);     // Compute 2^k using bit shift
    long res = (n + 1 < m) ? (n + 1) : m; // Result is minimum of n+1 and 2^k
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/