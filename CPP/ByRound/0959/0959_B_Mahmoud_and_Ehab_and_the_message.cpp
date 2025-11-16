// Problem: CF 959 B - Mahmoud and Ehab and the message
// https://codeforces.com/contest/959/problem/B

/*
 * Problem: Mahmoud and Ehab and the message
 * Purpose: Find minimum cost to send a message by replacing words with cheaper alternatives in the same group.
 * Algorithm: 
 *   - Group words by their meaning.
 *   - For each group, find the minimum cost word.
 *   - Replace all words in the group with the minimum cost word.
 *   - Sum up the costs of the words in the message.
 * Time Complexity: O(n log n + m) where n is number of words and m is number of words in message
 * Space Complexity: O(n) for storing word costs and mapping
 */

#include <iostream>
#include <map>
#include <vector>
#include <string>

typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  ll n, k, m;
  std::cin >> n >> k >> m;
  std::vector<std::string> w(n);
  for (ll p = 0; p < n; p++) {
    std::cin >> w[p];
  }
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    std::cin >> a[p];
  }
  for (ll p = 0; p < k; p++) {
    ll x;
    std::cin >> x;
    ll mc(1e9 + 7); // Initialize with a large value to find minimum
    std::vector<ll> b(x);
    for (ll p = 0; p < x; p++) {
      std::cin >> b[p];
      --b[p]; // Convert to 0-based indexing
      mc = (mc < a[b[p]]) ? mc : a[b[p]]; // Find minimum cost in the group
    }
    for (ll p = 0; p < x; p++) {
      a[b[p]] = mc; // Update all words in group to minimum cost
    }
  }
  std::map<std::string, ll> cm;
  for (ll p = 0; p < n; p++) {
    cm[w[p]] = a[p]; // Map each word to its minimum cost
  }
  ll cost(0);
  while (m--) {
    std::string s;
    std::cin >> s;
    cost += cm[s]; // Add the cost of each word in the message
  }
  std::cout << cost << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/