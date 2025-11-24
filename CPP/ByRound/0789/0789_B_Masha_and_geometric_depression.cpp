// Problem: CF 789 B - Masha and geometric depression
// https://codeforces.com/contest/789/problem/B

/*
Algorithm: Geometric Progression with Bad Numbers Removal
Approach:
- Generate terms of the geometric progression b, b*q, b*q^2, ...
- For each term, check if its absolute value is within the limit l
- Skip any term that is in the set of "bad" numbers
- Count valid terms until either:
  1. The absolute value of term exceeds l
  2. We've generated more than MAX_COUNT terms (to detect infinite cases)
- If too many terms are generated without termination, output "inf"

Time Complexity: O(m + MAX_COUNT) where m is number of bad numbers and MAX_COUNT is a small constant (50)
Space Complexity: O(m) for storing the bad numbers in a set
*/

#include <stdint.h>
#include <cmath>
#include <cstdio>
#include <set>

int main() {
  const int MAX_COUNT = 50;  // Maximum number of terms to check before determining infinity
  int64_t b, q, l, m;
  scanf("%lld %lld %lld %lld", &b, &q, &l, &m);
  std::set<int64_t> a;  // Set to store bad numbers for efficient lookup
  for (long p = 0; p < m; p++) {
    int64_t x;
    scanf("%lld", &x);
    a.insert(x);  // Insert each bad number into the set
  }
  long ans = 0, cnt = 0;  // ans: count of valid terms, cnt: number of terms processed
  int64_t term = b;  // Start with first term of the geometric progression
  while (std::fabs(term) <= l && (cnt < MAX_COUNT)) {  // Continue while within bounds and not too many terms
    if (!a.count(term)) {  // If term is not bad
      ans++;  // Increment valid term count
    }
    term *= q;  // Calculate next term in progression
    ++cnt;  // Increment term counter
  }
  if ((cnt == MAX_COUNT) && ans > 10) {  // If we processed many terms and have many valid ones
    puts("inf");  // Output infinity
  } else {
    printf("%ld\n", ans);  // Print the count of valid terms
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/