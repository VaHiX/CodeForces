// Problem: CF 1938 L - XOR Operations
// https://codeforces.com/contest/1938/problem/L

/*
 * Problem: Counting Possible XOR Sequences After Operations
 *
 * Algorithm: Gaussian elimination on XOR basis to find the rank of vectors.
 *
 * Time Complexity: O(n * 30) = O(n)
 * Space Complexity: O(30) = O(1)
 *
 * Description:
 * Given n integers a[0], a[1], ..., a[n-1], we start with a sequence B of all zeros.
 * We perform operations where for indices i and j, we simultaneously update:
 *   B[i] = B[i] ^ a[i] ^ a[j]
 *   B[j] = B[j] ^ a[i] ^ a[j]
 *
 * This is essentially computing the number of distinct vectors reachable from the zero vector
 * using linear combinations with the given set of vectors. It's a classic problem involving
 * vector space over GF(2) (binary field).
 *
 * The key insight is that the operations generate a subspace, and their number of basis
 * elements determines how many independent directions there are.
 *
 * To solve:
 * 1. XOR all elements with first element to get differences (a[i] ^= a[0])
 * 2. Gaussian elimination using bit manipulation to find a basis of the space
 * 3. The final answer is 2^(rank) where rank is the number of linearly independent vectors
 *
 * Key steps:
 * - Use a vector of size 30 to store pivot elements (for each bit position)
 * - For every new element, reduce it using existing pivots
 * - If after reduction it's non-zero, use it as a new pivot and increment rank
 * - Compute final result as 2^(n*rank - rank*(rank+1)/2) mod 998244353
 */

#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>

#pragma GCC optimize("Ofast")
using namespace std;
const int mod = 998244353;
typedef long long LL;

// Fast exponentiation to compute (x^n) % mod
LL fastpo(LL x, LL n, LL mod) {
  LL res = 1;
  while (n) {
    if (n & 1) {
      res = res * x % mod; // If n is odd, multiply result by x
    }
    x = x * x % mod; // Square x
    n /= 2; // Divide n by 2
  }
  return res;
}

const int N = 200022;
int a[N];

int main() {
  int n;
  scanf("%d", &n);
  
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    if (i) {
      a[i] ^= a[0]; // XOR all elements with first one to get differences
    }
  }
  
  vector<int> b(30); // Basis vectors (stores pivot elements)
  int cnt = 0;       // Count of linearly independent vectors
  
  for (int i = 1; i < n; i++) {
    int x = a[i];
    // Reduce x using existing basis vectors
    for (int j = 0; j < 30; j++) {
      if (b[j] != 0) {
        if (x & (1 << j)) { // If current bit is set in x
          x ^= b[j];        // Eliminate it using basis vector at position j
        }
      }
    }
    
    // If x is not zero after reduction, add it to basis
    if (x != 0) {
      int pos = ilogb(x & -x); // Find the least significant bit set (position of pivot)
      b[pos] = x;
      cnt++;
    }
  }
  
  // Calculate power exponent: n * cnt - (cnt + 1) * cnt / 2
  int pw = cnt == 0 ? 0 : n * cnt - (cnt + 1) * cnt / 2;
  printf("%d\n", fastpo(2, pw, mod));
}


// https://github.com/VaHiX/codeForces/