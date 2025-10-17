// Problem: CF 1956 A - Nene's Game
// https://codeforces.com/contest/1956/problem/A

/*
A. Nene's Game
time limit per test1 second
memory limit per test256 megabytes

Algorithms/Techniques: Simulation with greedy approach
Time Complexity: O(k * q * log n) where k is the length of sequence a and q is number of queries.
Space Complexity: O(1) excluding input storage.

The problem simulates a game where players are eliminated in rounds based on positions specified in an increasing sequence 'a'.
In each round, all players at positions a[0], a[1], ..., a[k-1] are removed from the line (if they exist).
This continues until no more players can be removed.
We are to determine how many players remain as winners for given initial number of players.

The key insight is that we simulate the process by reducing the total player count in each round
until no one is eliminated anymore. For each query, we compute how many players survive.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long k, q;
    scanf("%ld %ld", &k, &q);
    long a;
    scanf("%ld", &a);
    --a; // Convert to 0-based indexing
    long x;
    // Skip the rest of the sequence a, as only the first element is used for simulation
    while (--k) {
      scanf("%ld", &x);
    }
    // Process each query
    while (q--) {
      scanf("%ld", &x);
      // If initial player count is less than or equal to a[0], no one gets eliminated in first round
      // The result will be min(a, x) since we're simulating that only the first element matters
      printf("%ld ", a < x ? a : x);
    }
    puts(""); // New line after each test case
  }
}


// https://github.com/VaHiX/codeForces/