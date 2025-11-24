// Problem: CF 1877 B - Helmets in Night Light
// https://codeforces.com/contest/1877/problem/B

/*
 * Problem: B. Helmets in Night Light
 * 
 * Purpose: To find the minimum cost to notify all residents in a village using
 *          direct sharing and magical helmet devices with specific costs and
 *          capacities.
 *
 * Algorithm: Greedy approach
 *   1. Sort residents by their sharing cost (b_i) in ascending order.
 *   2. Initially, notify one resident directly (cost p).
 *   3. Then, for each remaining resident:
 *       - If current resident's sharing cost is greater than or equal to p,
 *         break the loop.
 *       - Otherwise, use as many of this resident as possible to cover
 *         remaining residents, considering their sharing capacity (a_i).
 *   4. For any remaining residents that couldn't be covered by the above,
 *      notify them directly (cost p each).
 *
 * Time Complexity: O(n log n) due to sorting + O(n) for the greedy loop = O(n log n)
 * Space Complexity: O(n) for storing the pair of (a_i, b_i) for all residents
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <utility>

#define ll long long
#define int ll
using namespace std;
const int N = 2e5 + 5;
int t, n, p;
pair<int, int> people[N]; // Pair of (a_i, b_i) for each resident
char getch() {
  static char buf[100000], *s1, *s2;
  return (s1 == s2) && (s2 = (s1 = buf) + fread(buf, 1, 100000, stdin)),
         s1 == s2 ? EOF : *s1++;
}
int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (!isdigit(ch)) {
    if (ch == '-')
      w = -1;
    ch = getch();
  }
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getch();
  return x * w;
}
void init() {}
void charming() {
  init();
  n = read(), p = read();
  for (int i = 1; i <= n; ++i) {
    people[i].first = read();  // Read a_i (capacity)
  }
  for (int i = 1; i <= n; ++i) {
    people[i].second = read(); // Read b_i (cost per share)
  }
  // Sort by b_i in ascending order to get cheapest sharing cost first
  sort(people + 1, people + 1 + n,
       [](pair<int, int> x, pair<int, int> y) { return x.second < y.second; });
  int ans = p;                  // Pay for the first direct share
  int remain = n - 1;           // Remaining residents to be notified
  for (int i = 1; i <= n; ++i) {
    if (people[i].second >= p)  // If the current share cost is >= direct cost
      break;
    else {
      if (people[i].first >= remain) { // If this person can cover all remaining
        ans += people[i].second * remain;
        remain = 0;
        break;
      } else {
        // Use this person to cover as many as possible
        ans += people[i].first * people[i].second;
        remain -= people[i].first;
      }
    }
  }
  // Pay for remaining residents directly (each costs p)
  ans += remain * p;
  printf("%lld\n", ans);
}
signed main() {
  t = read();
  while (t--)
    charming();
  return 0;
}


// https://github.com/VaHiX/CodeForces/