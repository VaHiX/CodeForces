// Problem: CF 1642 B - Power Walking
// https://codeforces.com/contest/1642/problem/B

/*
B. Power Walking
Algorithm: For each team size k from 1 to n, we need to distribute all n power-ups among k children such that each child gets at least one power-up and the sum of strengths (number of distinct power-up types per child) is minimized.

Key insight:
- The minimum strength sum for a team of size k is at least the number of distinct power-up types.
- If k >= number of distinct types, then we can assign each type to a separate child, making the sum equal to the number of distinct types.
- Otherwise, some children must share types, so we aim to minimize the extra "cost" due to sharing.

Approach:
1. Count unique power-up types using a set.
2. For each k from 1 to n:
   - If k >= count of unique types: answer is count of unique types.
   - Else: answer is k (each child gets at least one power-up, but we might have to "spread" types among them).

Time Complexity: O(n) per test case (since each element inserted once into set)
Space Complexity: O(n) for the set storing distinct elements
*/

#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<long> s; // Set to store unique power-up types
    long cnt(0);      // Count of distinct types
    for (long p = 0; p < n; p++) { // Read all power-ups
      long x;
      scanf("%ld", &x);
      if (s.count(x)) { // If type already exists, skip
        continue;
      }
      s.insert(x);  // Insert new type
      ++cnt;        // Increment distinct count
    }
    for (long p = 1; p <= n; p++) { // For each team size from 1 to n
      printf("%ld ", (p > cnt) ? p : cnt); // If k > distinct types, we have at least k children who get no extra type beyond what's needed
    }
    puts(""); // Print newline after each test case
  }
}


// https://github.com/VaHiX/codeForces/