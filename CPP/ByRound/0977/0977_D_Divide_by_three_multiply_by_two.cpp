// Problem: CF 977 D - Divide by three, multiply by two
// https://codeforces.com/contest/977/problem/D

/*
Purpose: This code solves the problem of rearranging a sequence of numbers to match a valid sequence of operations where each number is either multiplied by 2 or divided by 3 from the previous one.
Algorithm: The approach uses a greedy method with a deque to build the sequence from both ends:
1. Start by placing the last element of the input in the deque.
2. For each subsequent step, try to find an unused number that fits the sequence rule (either x*2 or x/3).
3. Attach it to the front or back of the deque accordingly.
4. Output the final deque.

Time Complexity: O(n^2) due to nested loops checking all unused elements for each step.
Space Complexity: O(n) for storing the input, used flags, and deque.

Techniques:
- Greedy algorithm with deque to maintain order
- Backtracking through possible valid transitions
*/

#include <algorithm>
#include <cstdio>
#include <deque>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  std::vector<bool> used(n, 0); // Track which elements have been used
  std::deque<ll> d; // Deque to hold the final sequence
  d.push_back(a.back()); // Start with the last element
  used.back() = 1; // Mark it as used
  for (ll u = 1; u < n; u++) { // For each of the remaining n-1 elements
    for (ll p = 0; p < n; p++) { // Try all elements
      if (used[p]) {
        continue; // Skip if already used
      } else if (a[p] == 2 * d.back()) {
        // If current element is double of the last in deque, append it
        d.push_back(a[p]);
        used[p] = 1;
        break;
      } else if (2 * a[p] == d.front()) {
        // If current element is half of the first in deque, prepend it
        d.push_front(a[p]);
        used[p] = 1;
        break;
      } else if (3 * a[p] == d.back()) {
        // If current element is one-third of the last in deque, append it
        d.push_back(a[p]);
        used[p] = 1;
        break;
      } else if (a[p] == 3 * d.front()) {
        // If current element is triple of the first in deque, prepend it
        d.push_front(a[p]);
        used[p] = 1;
        break;
      }
    }
  }
  for (ll p = 0; p < n; p++) {
    printf("%lld ", d[p]); // Output the final sequence
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/