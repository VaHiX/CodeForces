// Problem: CF 1974 G - Money Buys Less Happiness Now 
// https://codeforces.com/contest/1974/problem/G

/*
 * Problem: G. Money Buys Less Happiness Now
 * Purpose: Maximize the number of happiness units Charlie can buy given monthly income and costs.
 * Algorithm: Greedy with Priority Queue (Max-Heap)
 * Time Complexity: O(m * log m) per test case, where m is the number of months.
 * Space Complexity: O(m) for the priority queue and input storage.
 *
 * Techniques:
 * - Use a max-heap to keep track of the most expensive happiness units bought so far.
 * - For each month, try to buy the happiness unit of current cost.
 * - If total money becomes negative, remove the most expensive unit bought so far.
 * - Accumulate money from salary each month.
 *
 * Key Observations:
 * - At every step, we either buy the happiness unit or don't.
 * - The decision is made greedily: if buying the new unit makes us poorer than allowed,
 *   we remove the most expensively bought unit to maintain maximum happiness.
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>

#define int long long
#define pb push_back
#define pii pair<int, int>
#define fi first
#define se second
#define endl "\n"
#define pc putchar
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
using namespace std;
char buf[1 << 23], *p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;
#define gc()                                                                   \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
template <typename T> inline bool read(T &x) {
  x = 0;
  int f = 1;
  char c = gc();
  for (; c != EOF && !isdigit(c); c = gc())
    if (c == '-')
      f = -1;
  if (c == EOF)
    return 0;
  for (; c != EOF && c >= '0' && c <= '9'; c = gc())
    x = (x << 1) + (x << 3) + (c ^ 48);
  x *= f;
  return 1;
}
template <typename T, typename... Targs>
inline bool read(T &x, Targs &...args) {
  return read(x) && read(args...);
}
template <typename T> void print(T x) {
  if (x < 0)
    pc('-'), x = -x;
  if (x >= 10)
    print(x / 10);
  pc(x % 10 + '0');
}
int m, x;
int c[200005];
priority_queue<int> q;
void sol() {
  while (!q.empty())
    q.pop();
  read(m, x);
  for (int i = 1; i <= m; i++)
    read(c[i]);
  int mny = 0;
  int ans = 0;
  for (int i = 1; i <= m; i++) {
    q.push(c[i]); // Push the cost of current unit into max heap
    mny -= c[i];  // Deduct the cost from money
    ans++;        // Increment happiness count

    // If we're in debt (can't afford all units we've considered), remove the most expensive one
    if (mny < 0) {
      ans--;           // Decrement happiness because we're dropping one unit
      int h = q.top(); // Take the maximum cost unit from the heap
      q.pop();
      mny += h;        // Add back that cost to the money
    }

    mny += x; // Earn the monthly salary
  }
  cout << ans << endl;
}
int T;
signed main() {
  read(T);
  while (T--)
    sol();
  return 0;
}


// https://github.com/VaHiX/CodeForces/