// Problem: CF 797 A - k-Factorization
// https://codeforces.com/contest/797/problem/A

/*
============================================================
* Problem: k-Factorization
* Algorithm: Prime factorization followed by grouping
* Time Complexity: O(sqrt(n) + k)
* Space Complexity: O(log n)
============================================================
*/
#include <cstdio>
#include <vector>
int main() {
  long n;
  int k;
  scanf("%ld %d", &n, &k);
  std::vector<long> factors; // Store all prime factors of n
  long div(2); // Start with smallest possible divisor
  while (n > 1) {
    if (n % div == 0) {
      factors.push_back(div); // If div divides n, it's a prime factor
      n /= div; // Reduce n by dividing it by the factor
    } else {
      ++div; // Try next potential divisor
    }
  }
  if (factors.size() < k) {
    puts("-1"); // Not enough prime factors to form k numbers
  } else {
    // Print first k-1 factors
    for (int p = 0; p < k - 1; p++) {
      printf("%ld ", factors[p]);
    }
    long lastFactor(1); // Combine the remaining factors into one
    for (long p = k - 1; p < factors.size(); p++) {
      lastFactor *= factors[p]; // Multiply remaining factors
    }
    printf("%ld\n", lastFactor); // Print final combined factor
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/