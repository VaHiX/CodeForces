// Problem: CF 998 B - Cutting
// https://codeforces.com/contest/998/problem/B

/*
Algorithm: Greedy + Prefix Sum
Approach:
- Use a running balance (cnt) to track the difference between even and odd numbers.
  - Increment by 1 for odd numbers, decrement by 1 for even numbers.
- When balance reaches 0, it means we have an equal number of odds and evens up to that point.
  - This is a valid cutting position.
- Store the cost (absolute difference) of each valid cut in a vector.
- Sort the costs in ascending order to apply greedy strategy (cut cheapest first).
- Make as many cuts as possible within budget.

Time Complexity: O(n log n)
Space Complexity: O(n)
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, b;
  scanf("%ld %ld", &n, &b);
  std::vector<long> v(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &v[p]);
  }
  long cnt(0); // Tracks balance of even/odd count
  std::vector<long> a; // Stores costs of valid cuts
  for (long p = 0; p < n; p++) {
    cnt += 2 * (v[p] % 2) - 1; // Increment for odd (1), decrement for even (-1)
    if (p + 1 < n && cnt == 0) { // At a valid cut point
      long diff = v[p + 1] - v[p]; // Cost of cut
      if (diff < 0) {
        diff = -diff; // Ensure positive cost
      }
      a.push_back(diff); // Store cost
    }
  }
  sort(a.begin(), a.end()); // Sort to apply greedy strategy
  long cuts(0);
  for (long p = 0; p < a.size(); p++) {
    if (a[p] <= b) { // If within budget
      ++cuts; // Make the cut
      b -= a[p]; // Deduct cost
    }
  }
  printf("%ld\n", cuts);
  return 0;
}


// https://github.com/VaHiX/CodeForces/