// Problem: CF 1717 D - Madoka and The Corruption Scheme
// https://codeforces.com/contest/1717/problem/D

/*
 * Code Purpose: 
 *   This code computes the minimum possible number of the winner in a tournament
 *   where sponsors can change up to k match outcomes. The tournament follows
 *   an Olympic (single-elimination) system.
 * 
 * Algorithm/Techniques:
 *   - Uses combinatorial mathematics to calculate the minimal winning number.
 *   - Utilizes modular arithmetic and fast exponentiation for efficient computation.
 *   - The result corresponds to the sum of certain combinations modulo 10^9 + 7.
 * 
 * Time Complexity: O(min(n, k) * log MOD)
 *   - The loop runs up to min(n, k) and each iteration involves fast exponentiation.
 * 
 * Space Complexity: O(1)
 *   - Uses only a constant amount of extra space.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
#define LL long long
const int MOD = 1e9 + 7;

// Fast exponentiation function to compute (x^y) % MOD
LL fpow(LL x, int y) {
  LL res = 1;
  while (y) {
    if (y & 1)  // If y is odd, multiply res by x
      res = res * x % MOD;
    x = x * x % MOD;  // Square x
    y >>= 1;  // Divide y by 2
  }
  return res;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  
  LL c = 1, s = 1;  // c: combination coefficient, s: cumulative sum
  
  // Loop from 1 to min(n, k) to compute combinations and accumulate sum
  for (int i = 1; i <= min(n, k); i++) {
    // Compute combination C(n, i) = n! / (i! * (n-i)!)
    c = c * (n - i + 1) % MOD * fpow(i, MOD - 2) % MOD;
    s = (s + c) % MOD;  // Add current combination to cumulative sum
  }
  
  printf("%lld", s);  // Output final result
}


// https://github.com/VaHiX/CodeForces/