// Problem: CF 2067 B - Two Large Bags
// https://codeforces.com/contest/2067/problem/B

/*
B. Two Large Bags

Algorithm: Greedy with frequency counting and simulation of operations
Time Complexity: O(n) per test case
Space Complexity: O(n) due to the vector of size n+1

The problem is about determining whether we can make two bags equal by:
1. Moving numbers from first bag to second.
2. Increasing a number in first bag if it exists in second bag.

Key idea:
- Count frequency of each number in first bag.
- Process numbers in ascending order:
  - If frequency is 1, impossible (can't pair it).
  - If frequency > 2, carry over excess to next number (simulate increasing).
- Check last element; must be even for valid pairing.

Approach:
- Use vector v to track how many of each number exist.
- Process frequencies from 1 to n.
- Simulate carrying excess counts forward to simulate increment operations.
- Final check: last number must have even count for balanced pairings.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n + 1); // Frequency array for numbers 1 to n
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++v[x]; // Count occurrences of each number
    }
    bool ans(n % 2 == 0); // Initially assume possible if n is even
    for (long p = 1; ans && p <= n; p++) {
      if (!v[p]) {
        continue; // No elements of value p
      } else if (v[p] == 1) {
        ans = false; // Cannot pair a single element
      } else if (p < n) {
        v[p + 1] += v[p] - 2; // Carry over excess to next number
      }
    }
    if (v.back() % 2) {
      ans = false; // Last count must be even for balanced result
    }
    puts(ans ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/