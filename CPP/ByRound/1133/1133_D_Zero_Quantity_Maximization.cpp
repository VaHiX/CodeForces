// Problem: CF 1133 D - Zero Quantity Maximization
// https://codeforces.com/contest/1133/problem/D

/*
Problem: D. Zero Quantity Maximization
Purpose: Given two arrays a and b of n integers, find the maximum number of zeros in array c where c[i] = d * a[i] + b[i] for some real number d.

Approach:
- For each element pair (a[i], b[i]), we calculate the ratio -b[i]/a[i] when a[i] != 0.
- We store these ratios in a map to count how many times each ratio appears.
- The maximum count gives the maximum number of zeros achievable by choosing an optimal d.
- Special cases:
    * If a[i] == 0 and b[i] == 0, it contributes directly to trivial solution (zero for any d).
    * If a[i] == 0 but b[i] != 0, it cannot produce zero regardless of d.
- To avoid negative signs in ratios, we ensure that the denominator is always positive.

Time Complexity: O(n * log(n)) due to map operations and GCD computation
Space Complexity: O(n) for storing elements in the map and vectors

Algorithms/Techniques:
- GCD (Euclidean algorithm)
- Map (hash table for ratio counting)
- Rational number normalization (sign handling)

*/

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> b(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p]);
  }
  std::map<std::pair<long, long>, long> m; // Stores normalized ratios as key and their counts as value
  long trivial(0); // Count of positions where both a[i] and b[i] are zero
  for (long p = 0; p < n; p++) {
    if (a[p] == 0 && b[p] == 0) {
      ++trivial;
      continue;
    } else if (a[p] == 0) {
      continue; // Cannot form a valid ratio - skip this position
    }
    int s = 1; // Sign of the ratio
    if (a[p] < 0) {
      s *= -1;
      a[p] = -a[p]; // Make numerator positive by flipping signs
    }
    if (b[p] < 0) {
      s *= -1;
      b[p] = -b[p];
    }
    long g = gcd(a[p], b[p]); // Simplify the fraction
    ++m[std::make_pair(s * b[p] / g, a[p] / g)]; // Insert normalized ratio into map
  }
  long mx(0);
  for (std::map<std::pair<long, long>, long>::iterator it = m.begin();
       it != m.end(); it++) {
    long cnt = it->second;
    mx = (mx > cnt) ? mx : cnt; // Find maximum count among all unique ratios
  }
  printf("%ld\n", mx + trivial); // Add the count of trivial zeros to max ratio count
  return 0;
}


// https://github.com/VaHiX/codeForces/