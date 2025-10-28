// Problem: CF 2037 D - Sharky Surfing
// https://codeforces.com/contest/2037/problem/D

/*
D. Sharky Surfing
Purpose: Determine the minimum number of power-ups Mualani must collect to surf from position 1 to L,
         avoiding hurdles and utilizing power-ups to increase jump power.
Algorithms/Techniques: 
  - Two-pointer technique for processing hurdles and power-ups.
  - Greedy selection using a max multiset (std::multiset with std::greater) to select the largest
    available power-ups when needed to cover distance.
Time Complexity: O(n + m)
Space Complexity: O(m)

Input Format:
- t (number of test cases)
- For each case:
  - n, m, L (number of hurdles, power-ups, end position)
  - n pairs of (l, r) for hurdles
  - m pairs of (x, v) for power-ups

Output:
- Minimum number of power-ups to reach L, or -1 if impossible.
*/

#include <cstdio>
#include <set>
#include <vector>
#include <functional>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, L;
    scanf("%ld %ld %ld", &n, &m, &L);
    std::vector<std::pair<long, long>> h(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld %ld", &h[p].first, &h[p].second); // Read hurdle intervals
    }
    std::vector<std::pair<long, long>> w(m);
    for (long p = 0; p < m; p++) {
      scanf("%ld %ld", &w[p].first, &w[p].second); // Read power-up positions and values
    }
    std::multiset<long, std::greater<long>> s; // Max multiset to track available power-ups
    long idx(0), cnt(0), mjl(1); // idx: power-up index, cnt: number of collected power-ups, mjl: current jump length
    for (long p = 0; p < h.size(); p++) {
      // Add all power-ups that are positioned before the current hurdle's start
      while (idx < m && w[idx].first < h[p].first) {
        s.insert(w[idx].second); // Insert power-up value into multiset
        ++idx;
      }
      // Calculate distance to cover from current position to hurdle end
      long dist = h[p].second - h[p].first + 2;
      // Greedily consume the largest available power-ups until enough jump length is achieved
      while (!s.empty() && mjl < dist) {
        long add = *s.begin(); // Get the maximum available power-up value (since multiset is sorted desc)
        s.erase(s.begin());    // Remove it from multiset
        mjl += add;            // Increase jump length
        ++cnt;                 // Increment count of collected power-ups
      }
      if (mjl < dist) {   // If we still cannot cover the hurdle, it's impossible
        cnt = -1;
        break;
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/