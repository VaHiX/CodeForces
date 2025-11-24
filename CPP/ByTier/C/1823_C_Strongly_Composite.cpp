// Problem: CF 1823 C - Strongly Composite
// https://codeforces.com/contest/1823/problem/C

/*
C. Strongly Composite
Algorithm: Prime factorization + greedy approach to maximize the number of strongly composite numbers.

The problem asks us to decompose the product of given integers into the maximum number of strongly composite numbers.
A strongly composite number is one where the count of its prime divisors is less than or equal to the count of its composite divisors.

Approach:
1. For each input number, compute its prime factorization.
2. Count how many times each prime appears across all numbers (total multiplicity).
3. Use greedy strategy:
   - Each pair of same primes can form one composite number (e.g., 2*2 = 4).
   - If we have an odd count, one prime remains unpaired.
   - Triplets of pairs (i.e., 6 primes total) can be grouped into one strongly composite (as they will make up for 3 primes and 3 composites).
4. Total count is number of pairs plus triplets.

Time Complexity: O(n * sqrt(max(a_i))) where max(a_i) <= 1e7, so roughly O(n * 10^3)
Space Complexity: O(log(max(a_i))) due to storing prime factors
*/

#include <cstdio>
#include <map>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m; // Map to store prime -> count of occurrences
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      for (long u = 2; u * u <= x; u++) {
        while (x % u == 0) {
          x /= u;
          ++m[u]; // Count the occurrence of prime factor u
        }
      }
      if (x > 1) {
        ++m[x]; // If x is still > 1, then it's a prime factor
      }
    }

    long cnt(0), rem(0);
    for (std::pair<long, long> w : m) {
      long mult = w.second;
      cnt += mult / 2;   // Each pair contributes one composite number
      rem += mult % 2;   // Remaining odds that cannot be paired yet
    }
    cnt += rem / 3;        // Triplets of pairs can form another composite
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/