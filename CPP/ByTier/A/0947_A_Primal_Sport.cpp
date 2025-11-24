// Problem: CF 947 A - Primal Sport
// https://codeforces.com/contest/947/problem/A

/*
Purpose: 
  This program finds the minimum possible starting number X0 such that after two turns of the game,
  the number reaches the given value X2. The game involves players selecting primes less than the current
  number and moving to the smallest multiple of that prime which is not smaller than the current number.
  
Algorithm:
  - Sieve of Eratosthenes is used to precompute the smallest prime factor (SPF) for all numbers up to 10^6.
  - For a given X2, we iterate through possible values from (X2 - smallest_prime_factor(X2) + 1) to X2.
  - For each candidate value i, we determine if it can be reached in two moves from some X0.
  - The condition i - d[i] >= 2 ensures that a valid previous state (X1) exists such that:
    X1 = i - d[i] + 1 and X2 = min multiple of a prime p < X1 that is >= X1.

Time Complexity: O(N log log N + X2), where N = 10^6
Space Complexity: O(N)
*/
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1 << 20;
int d[N] = {0}; // Array to store smallest prime factor (SPF) for each number
int main() {
  // Sieve of Eratosthenes to compute SPF for all numbers up to N
  for (int i = 2; i < N; i++)
    if (d[i] <= 0)
      for (int j = i; j < N; j += i)
        d[j] = i;
  
  int n, ans = N;
  scanf("%d", &n);
  
  // Iterate possible values of X1 (the number before the last move)
  // X1 ranges from (X2 - d[X2] + 1) to X2
  for (int i = n - d[n] + 1; i <= n; i++)
    if (i - d[i] >= 2) // Check if this value can lead to a valid X0
      ans = min(ans, i - d[i] + 1);
  
  printf("%d\n", ans);
}


// https://github.com/VaHiX/CodeForces/