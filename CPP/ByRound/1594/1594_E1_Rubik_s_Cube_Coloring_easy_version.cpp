// Problem: CF 1594 E1 - Rubik's Cube Coloring (easy version)
// https://codeforces.com/contest/1594/problem/E1

/*
E1. Rubik's Cube Coloring (easy version)
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

It is the easy version of the problem. The difference is that in this version, there are no nodes with already chosen colors.
Theofanis is starving, and he wants to eat his favorite food, sheftalia. However, he should first finish his homework. Can you help him with this problem?
You have a 
perfect
 binary tree of $$$2^k - 1$$$ nodes — a binary tree where all vertices $$$i$$$ from $$$1$$$ to $$$2^{k - 1} - 1$$$ have exactly two children: vertices $$$2i$$$ and $$$2i + 1$$$. Vertices from $$$2^{k - 1}$$$ to $$$2^k - 1$$$ don't have any children. You want to color its vertices with the $$$6$$$ Rubik's cube colors (White, Green, Red, Blue, Orange and Yellow).
Let's call a coloring 
good
 when all edges connect nodes with colors that are 
neighboring
 sides in the Rubik's cube.
 
 
A picture of Rubik's cube and its 2D map.
 
More formally: 
 
 a white node can 
not
 be neighboring with white and yellow nodes; 
 a yellow node can 
not
 be neighboring with white and yellow nodes; 
 a green node can 
not
 be neighboring with green and blue nodes; 
 a blue node can 
not
 be neighboring with green and blue nodes; 
 a red node can 
not
 be neighboring with red and orange nodes; 
 an orange node can 
not
 be neighboring with red and orange nodes; 
You want to calculate the number of the good colorings of the binary tree. Two colorings are considered different if at least one node is colored with a different color.
The answer may be too large, so output the answer modulo $$$10^9+7$$$.
Input
The first and only line contains the integers $$$k$$$ ($$$1 \le k \le 60$$$) — the number of levels in the perfect binary tree you need to color.
Output
Print one integer — the number of the different colorings modulo $$$10^9+7$$$.
Examples
Input

3

Output

24576

Input

14

Output

934234

Note
In the picture below, you can see one of the correct colorings of the first example.

Algorithm: 
- Fast exponentiation (binary exponentiation) is used to compute modular powers efficiently.
- The number of valid colorings of a perfect binary tree with k levels is given by:
  - Each non-leaf node contributes a factor of 6 (initial colors)
  - For each level from bottom up, we compute how many valid configurations are possible for the subtree rooted at that level
  - The result uses a recurrence relation over powers of 4 (as there are 4 color choices per edge in specific constraints)

Time Complexity: O(k * log k) 
Space Complexity: O(log k) due to recursive stack usage in fastpow function
*/

#include <cstdio>
typedef long long ll;

// Fast exponentiation: computes (a^x) % mod efficiently using binary exponentiation
ll fastpow(ll a, ll x, ll mod) {
  if (a <= 1) {
    return a % mod;
  }
  if (x <= 0) {
    return 1;
  }
  ll tmp = fastpow(a, x / 2, mod);          // Recursive call with half exponent
  ll ans = ((tmp * tmp) % mod) * (x % 2 ? a : 1) % mod; // Combine results, multiply by 'a' if x is odd
  return ans % mod;
}

int main() {
  const ll MOD = 1e9 + 7;
  ll k;
  scanf("%lld", &k);
  ll exptwo = (1LL << k) - 2;                // 2^k - 2 represents number of edges in subtree
  ll ans = 6 * fastpow(4, exptwo, MOD) % MOD; // Final formula for count of valid colorings
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/