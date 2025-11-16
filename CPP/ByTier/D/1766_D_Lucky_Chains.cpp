// Problem: CF 1766 D - Lucky Chains
// https://codeforces.com/contest/1766/problem/D

/*
Algorithm: 
- Precompute smallest prime factor (SPF) for all numbers up to 1e7 using sieve of Eratosthenes.
- For each query pair (x, y), compute the length of the longest lucky chain starting from (x, y).
- A chain (x, y), (x+1, y+1), ..., (x+k, y+k) is lucky if gcd(x+i, y+i) = 1 for all i in [0, k].
- Key observation:
  - gcd(x+i, y+i) = gcd(x+i, y-x) (since (y+i)-(x+i) = y-x)
  - So we only need to check if gcd(x+i, y-x) = 1 for all valid i.
  - We can determine the maximum such i by analyzing when x+i shares a common prime factor with y-x.
  - If y-x has a prime factor p, then x+i ≡ 0 mod p, which means i ≡ -x mod p.
  - We find the minimum such value of i (if valid) for each prime factor of (y-x).
  - The final answer is the minimum among these i values, unless we can continue indefinitely (i.e., gcd(x,y) = 1 but no common factors between (y-x) and any x+i).

Time Complexity: O(N log log N + n * log(max(y-x))) where N = 1e7 and n is number of pairs.
Space Complexity: O(N) for the sieve array.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 1e7;
int a, x, y, b[N]; // b[i] stores smallest prime factor of i
int main() {
  cin >> a;
  // Sieve of Eratosthenes to precompute SPF
  for (int i = 2; i <= 1e7; ++i)
    if (!b[i])
      for (int j = i; j <= 1e7; j += i)
        b[j] = i;
  while (a--) {
    scanf("%d%d", &x, &y);
    // If not lucky pair, length = 0
    if (__gcd(x, y) != 1) {
      printf("0\n");
      continue;
    }
    int t = 1e9; // Initialize to large number
    // Factorize (y - x) and for each prime factor p, determine the minimum i such that (x + i) % p == 0
    for (int c = y - x; c > 1; c /= b[c]) {
      if (x % b[c] == 0) {
        t = 0; // If x is divisible by prime factor, chain stops immediately
        break;
      }
      // Calculate how much we need to increment x to make (x + i) divisible by b[c]
      t = min(b[c] - x % b[c], t);
    }
    // If t > 1e8, it means no bounds were hit, so chain is infinite
    printf("%d\n", t > 1e8 ? -1 : t);
  }
}


// https://github.com/VaHiX/CodeForces/