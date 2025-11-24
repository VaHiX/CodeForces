// Problem: CF 1043 F - Make It One
// https://codeforces.com/contest/1043/problem/F

/*
F. Make It One
Purpose: Given a sequence of integers, find the minimum number of elements to select such that their GCD equals 1.
Algorithms/Techniques:
- Sieve of Euler for computing phi and mu functions (Euler's totient and Mertens function)
- inclusion-exclusion principle with Möbius function
- GCD properties and subset enumeration
Time Complexity: O(N log N + N), where N = 300000
Space Complexity: O(N)

Input:
The first line contains an only integer n (1 ≤ n ≤ 300000) — the number of integers in the sequence.
The second line contains n integers a_1, a_2, ..., a_n (1 ≤ a_i ≤ 300000).

Output:
If there is no subset of the given sequence with gcd equal to 1, output -1.
Otherwise, output exactly one integer — the size of the smallest subset with gcd equal to 1.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define N 300030
int runs, p[N], phi[N], mu[N];

// Preprocessing primes and Euler's totient function and Möbius function using sieve of Euler
void ppm() {
  phi[1] = 1, mu[1] = 1;
  for (int i = 2; i < N; i++) {
    if (!phi[i])
      p[++runs] = i, phi[i] = i - 1, mu[i] = -1;
    for (int j = 1; j <= runs && i * p[j] < N; j++) {
      int k = i * p[j];
      phi[k] = phi[i] * (p[j] - 1);
      if (i % p[j] == 0) {
        phi[k] = phi[i] * p[j];
        break;
      }
      mu[k] = -mu[i];
    }
  }
}

int n, a[N], b[N]; // b[i] stores frequency of number i
long long f[N], g[N]; // f[i]: count of multiples of i; g[i]: Möbius function

int main() {
  ppm();
  cin >> n;
  int d = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    d = __gcd(d, a[i]); // if overall GCD > 1, impossible to get 1
    b[a[i]]++; // count frequency of each number
  }
  if (d > 1) { // if all numbers share a common factor > 1, return -1
    puts("-1");
    return 0;
  }
  
  // f[i] counts how many elements in array are divisible by i
  for (int i = 1; i < N; i++)
    for (int j = i; j < N; j += i)
      f[i] += b[j]; // accumulate count of multiples of i

  int cnt = 0;
  for (int i = 1; i < N; i++)
    g[i] = mu[i]; // prepare Möbius function into g

  while (1) {
    cnt++; // increment step counter
    for (int i = 1; i < N; i++) {
      g[i] *= f[i]--; // multiply g[i] by f[i], then decrement f[i]
    }
    long long ans = 0;
    for (int i = 1; i < N; i++)
      ans += g[i]; // accumulate result using inclusion-exclusion
    if (ans) { // if final answer is non-zero, we found smallest subset size
      cout << cnt;
      break;
    }
  }
}


// https://github.com/VaHiX/codeForces/