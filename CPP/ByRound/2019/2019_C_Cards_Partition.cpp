// Problem: CF 2019 C - Cards Partition
// https://codeforces.com/contest/2019/problem/C

/*
C. Cards Partition
Algorithm: Binary search on answer + greedy validation
Time Complexity: O(n * log(max_sum))
Space Complexity: O(1)

The problem requires finding the maximum possible deck size after buying at most k cards,
such that all decks have equal size and no two cards with same value are in the same deck.

Key approach:
1. Use binary search on the answer (deck size).
2. For a given deck size s, check if we can form valid partitions:
   - Total cards needed = s * (number of decks)
   - Number of decks = total_cards / s
   - Each deck must have distinct values ⇒ max(cards_of_each_value) <= deck_size
   - We must be able to buy enough cards such that (total + buy) >= s * decks
*/

#include <algorithm>
#include <iostream>
using namespace std;
#define int long long

int T, n, m, sum, mx, ans, a[200005];

void solve() {
  cin >> n >> m, mx = sum = ans = 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i], sum += a[i], mx = max(mx, a[i]); // Read input and compute total cards and max frequency
  for (int i = 1; i <= n; i++)
    if ((sum + m) / i * i >= sum && (sum + m) / i >= mx) // Check valid deck sizes
      ans = i;
  cout << ans << '\n';
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/