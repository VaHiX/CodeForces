// Problem: CF 2004 E - Not a Nim Problem
// https://codeforces.com/contest/2004/problem/E

/*
E. Not a Nim Problem

This problem is a variant of the Nim game, where the allowed moves are restricted by the condition that the number of stones taken from a pile must be coprime with the current pile size.
The key insight is to use the Sprague-Grundy theorem to compute the Grundy number (nimber) for each pile size.

Approach:
1. Precompute Grundy numbers using a sieve-like method, similar to how primes are generated.
2. For odd numbers, mark them as unvisited and assign them a unique Grundy number based on their prime factors.
3. The Grundy number of a number is computed as the minimum excludant (mex) of the Grundy numbers of reachable states.
4. For each test case, XOR all Grundy numbers to determine if the total position is winning or losing.

Time Complexity: O(N log log N + sum(n)) where N = 10^7
Space Complexity: O(N) for the grundy array and bitset

Algorithms/Techniques:
- Sieve of Eratosthenes variant for computing Grundy numbers
- Sprague-Grundy theorem for game theory
- Bit manipulation with bitset for efficient marking
*/

#include <stdio.h>
#include <bitset>
#include <iostream>

using namespace std;
const int N = 10000010; // Maximum possible value of pile size
int grundy[N];          // Grundy number for each pile size
bitset<N> vis;          // Visited marker for sieve-like process

int main() {
  grundy[1] = 1;        // Grundy number for pile of size 1 is 1
  for (int i = 3, at = 1; i < N; i += 2) // Iterate through odd numbers starting from 3
    if (!vis[i]) {      // If number is unmarked (like a prime in sieve)
      ++at;             // Increment the counter for unique Grundy number
      for (int j = i; j < N; j += 2 * i) // Mark all multiples of i with same Grundy number
        if (!vis[j])    // Only process unmarked numbers
          vis[j] = 1, grundy[j] = at; // Mark and assign Grundy number
    }
  
  int t;
  cin >> t;
  while (t--) {
    int n;
    scanf("%d", &n);
    int sum = 0;                // Initialize XOR sum of Grundy numbers
    while (n--) {
      int x;
      scanf("%d", &x);
      sum ^= grundy[x];         // XOR with Grundy number of current pile size
    }
    puts(sum ? "Alice" : "Bob"); // If sum is non-zero, Alice wins; otherwise Bob wins
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/