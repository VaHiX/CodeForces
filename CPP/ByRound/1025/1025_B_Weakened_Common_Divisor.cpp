// Problem: CF 1025 B - Weakened Common Divisor
// https://codeforces.com/contest/1025/problem/B

#include <cstdio>
#include <set>
#include <vector>
// Flowerbox describing the code purpose, algorithms, time and space complexity
/*
 * Problem: Weakened Common Divisor (WCD)
 * 
 * Approach:
 * 1. For the first pair (a1, b1), compute all prime factors of a1 and b1 and store them in a set.
 * 2. For each subsequent pair (ai, bi), check which prime factors from the set divide at least one element of the current pair.
 *    Remove from the set those prime factors that do not satisfy the condition (i.e., divide neither ai nor bi).
 * 3. After processing all pairs, if the set is not empty, output the smallest element in the set as the WCD.
 *    If it is empty, output -1.
 *
 * Time Complexity: O(n * sqrt(max(a_i, b_i)))
 *   - For each pair, we factorize two numbers and iterate through current prime factors.
 *   - In the worst case, number of prime factors is small and the loop over set is efficient.
 * Space Complexity: O(sqrt(max(a_i, b_i))) 
 *   - Space used to store prime factors of numbers.
 */

int main() {
  long n;
  scanf("%ld", &n);
  long a, b;
  scanf("%ld %ld", &a, &b);
  std::set<long> s; // Store prime factors of the first pair
  long d(2);
  // Factorize 'a' and insert its prime factors into the set
  while (d * d <= a) {
    if (a % d == 0) {
      s.insert(d);
      while (a % d == 0) {
        a /= d;
      }
    }
    ++d;
  }
  if (a > 1) {
    s.insert(a);
  }
  d = 2;
  // Factorize 'b' and insert its prime factors into the set
  while (d * d <= b) {
    if (b % d == 0) {
      s.insert(d);
      while (b % d == 0) {
        b /= d;
      }
    }
    ++d;
  }
  if (b > 1) {
    s.insert(b);
  }
  // Process remaining pairs
  for (long p = 1; p < n; p++) {
    scanf("%ld %ld", &a, &b);
    std::vector<long> v; // Stores prime factors to be removed
    // Check each existing prime factor
    for (std::set<long>::iterator it = s.begin(); it != s.end(); it++) {
      d = *it;
      // If current prime factor divides neither 'a' nor 'b', it should be removed
      if ((a % d) && (b % d)) {
        v.push_back(d);
      }
    }
    // Remove invalid prime factors
    for (long p = 0; p < v.size(); p++) {
      s.erase(v[p]);
    }
  }
  // If set is not empty, output the smallest valid WCD
  if (s.size()) {
    printf("%ld\n", *s.begin());
  } else {
    puts("-1");
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/