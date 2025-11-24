// Problem: CF 1722 D - Line
// https://codeforces.com/contest/1722/problem/D

/*
D. Line
Algorithms/Techniques: Greedy with sorting, prefix sum

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing differences and prefix sums

Problem Description:
Given a line of people looking either left (L) or right (R), each person counts how many people they can see in their direction. The total value is the sum of these counts.
For each k from 1 to n, determine the maximum possible value by changing at most k people's directions.

Approach:
1. For each position, calculate initial count and potential gain if we flip direction
2. Sort gains in descending order
3. Greedily apply flips to maximize total value for each k
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  ll t;
  std::cin >> t;
  while (t--) {
    ll n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<ll> diffs(n, 0);
    ll sum(0);
    for (ll p = 0; p < n; p++) {
      // Calculate current count for person at position p
      ll cur = (s[p] == 'L') ? p : n - p - 1;
      // Maximum possible count if we flip this person's direction (this is the gain)
      ll mx = (p > (n - p - 1)) ? p : (n - p - 1);
      sum += cur; // Add current count to total sum
      ll diff = mx - cur; // Difference represents potential gain from flipping
      diffs[p] = diff;
    }
    sort(diffs.rbegin(), diffs.rend()); // Sort gains in descending order to greedily use best flips first
    for (ll p = 0; p < n; p++) {
      sum += diffs[p]; // Add best available gain
      std::cout << sum << " ";
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/