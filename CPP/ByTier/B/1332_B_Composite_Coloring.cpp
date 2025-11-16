// Problem: CF 1332 B - Composite Coloring
// https://codeforces.com/contest/1332/problem/B

#include <cstdio>
#include <map>
#include <vector>
/*
Code Purpose:
This program solves the "Composite Coloring" problem by assigning colors to a sequence of composite numbers such that:
1. Each color from 1 to m is used at least once.
2. Any two numbers assigned the same color share a common factor greater than 1 (i.e., their GCD > 1).
The algorithm uses the first 11 prime numbers to find shared prime factors among composite numbers and assigns colors accordingly.

Algorithm:
- Predefined list of first 11 primes: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}
- For each number in input:
  - Check if it's divisible by any of the first 11 primes.
  - Assign a unique color to each prime factor found.
  - Numbers sharing a prime factor are given the same color.

Time Complexity: O(n * k)
Where:
- n is the number of elements in the input array.
- k is the number of predefined primes (11 in this case).
So effectively it's O(n) since k is constant.

Space Complexity: O(n + k)
Where:
- n is size of the result array.
- k is size of the prime vector (constant 11).
*/
int main() {
  const std::vector<long> v = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0);
    std::map<long, long> m; // Maps prime to color number
    std::vector<long> res(n);
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      for (long q = 0; q < v.size(); q++) {
        if (a % v[q]) {
          continue; // If not divisible, skip to next prime
        }
        int col(0);
        if (!m.count(v[q])) {
          m[v[q]] = ++cnt; // Assign new color if prime not seen before
        }
        res[p] = m[v[q]]; // Assign color to current number
        break; // Break after first found prime factor to avoid overcoloring
      }
    }
    printf("%ld\n", cnt);
    for (long p = 0; p < n; p++) {
      printf("%ld ", res[p]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/