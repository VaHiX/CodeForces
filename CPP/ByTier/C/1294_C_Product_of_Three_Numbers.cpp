// Problem: CF 1294 C - Product of Three Numbers
// https://codeforces.com/contest/1294/problem/C

/*
C. Product of Three Numbers
Algorithm: Factorization and decomposition into three distinct factors.
Approach:
- For each number n, find its prime factorization.
- Try to group these factors into three distinct integers a, b, c such that a*b*c = n.
- If we have at least 3 prime factors (or enough repeated factors), then it's possible.
- The algorithm attempts to build the first two numbers using small primes and assigns remaining product to third number.

Time Complexity:
- O(sqrt(n)) per test case due to factorization loop.
- For up to 100 test cases, total time is O(t * sqrt(max_n)) where max_n = 1e9.
Space Complexity:
- O(log n) for storing the prime factors in vector.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> div; // Store prime factors of n
    long m(n);
    for (long p = 2; p * p <= m + 10; p++) { // Iterate up to sqrt(m)+10 to cover edge cases
      if (n % p) {
        continue;
      }
      while (n % p == 0) { // Extract all instances of prime p
        div.push_back(p);
        n /= p;
      }
    }
    if (n > 1) { // If n is still greater than 1, it's a prime factor
      div.push_back(n);
    }
    bool possible(div.size() >= 3); // At least 3 factors needed to split into 3 distinct numbers >=2
    long a(1), b(1), c(1);
    if (possible) {
      a = div[0]; // Assign first factor to a
      long idx(2);
      if (div[0] == div[1]) { // If first two factors are same, merge them into b
        b = div[1] * div[2];
        ++idx;
      } else {
        b = div[1]; // Assign second factor to b
      }
      for (long p = idx; p < div.size(); p++) { // Multiply remaining factors to get c
        c *= div[p];
      }
      if (c <= 1 || c == a || c == b) { // Ensure c is valid and different from a,b
        possible = false;
      }
    }
    if (possible) {
      printf("YES\n%ld %ld %ld\n", a, b, c);
    } else {
      puts("NO");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/