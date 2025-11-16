// Problem: CF 1881 G - Anya and the Mysterious String
// https://codeforces.com/contest/1881/problem/G

/*
Problem: Determine if a substring of a modified string is "beautiful"
         (i.e., contains no palindromic substrings of length >= 2).

Approach:
- Use Binary Indexed Trees (Fenwick Trees) to efficiently handle range updates and queries.
- Maintain two BITs:
  - bit1: tracks differences between adjacent characters (d[i] = s[i] - s[i-1])
  - bit2: tracks differences between characters two positions apart (e[i] = s[i] - s[i-2])
- A substring is beautiful if:
  - No adjacent characters are the same (bit1 query)
  - No three-character palindromes exist (bit2 query)
- For range updates, apply delta to specific indices using BIT range update technique.

Time Complexity: O((n + m) * log n) per test case
Space Complexity: O(n) for storing the string and BITs

Key Concepts:
- Fenwick Tree (Binary Indexed Tree) for efficient prefix/suffix operations
- Difference arrays for range updates
- Palindrome check optimization using two difference arrays
*/

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
typedef long long LL;
typedef pair<int, int> PairII;
typedef pair<LL, LL> PairLL;
const int MAX_N = 2e5 + 3;
int n, q, op, l, r, x, d[MAX_N], e[MAX_N];
struct BIT {
  int tree[MAX_N];
  void update(int idx, int val) {
    for (; idx <= n; idx += idx & -idx) {
      tree[idx] += val;
    }
  }
  int query(int idx) {
    int result = 0;
    for (; idx; idx -= idx & -idx) {
      result += tree[idx];
    }
    return result;
  }
  int query(int left, int right) {
    if (left > right)
      return 0;
    return query(right) - query(left - 1);
  }
  void clear() { memset(tree, 0, sizeof(int) * (n + 1)); }
} bit1, bit2;
void update1(int idx, int val) {
  if (!d[idx])
    bit1.update(idx, -1);  // Remove the previous contribution if it was zero
  d[idx] = (d[idx] + val) % 26;
  if (!d[idx])
    bit1.update(idx, 1);   // Add the new contribution if it became zero
}
void update2(int idx, int val) {
  if (!e[idx])
    bit2.update(idx, -1);  // Remove the previous contribution if it was zero
  e[idx] = (e[idx] + val) % 26;
  if (!e[idx])
    bit2.update(idx, 1);   // Add the new contribution if it became zero
}
bool query1(int left, int right) { return !bit1.query(left + 1, right); }  // Check no adjacent same chars
bool query2(int left, int right) { return !bit2.query(left + 2, right); }  // Check no 3-char palindromes
string s;
void solve() {
  cin >> n >> q >> s;
  s = " " + s;  // Prepend space to make indexing easier
  for (int i = 2; i <= n; ++i) {
    d[i] = (s[i] - s[i - 1] + 26) % 26;  // Calculate difference with modulo 26
    if (!d[i])
      bit1.update(i, 1);  // Track zeros in d array (same adjacent chars)
  }
  for (int i = 3; i <= n; ++i) {
    e[i] = (s[i] - s[i - 2] + 26) % 26;  // Calculate difference with modulo 26
    if (!e[i])
      bit2.update(i, 1);  // Track zeros in e array (palindromic triplets)
  }
  while (q--) {
    cin >> op >> l >> r;
    if (op == 1) {
      cin >> x;
      x %= 26;  // Reduce x modulo 26 to avoid unnecessary operations
      if (l >= 2)
        update1(l, x);  // Update difference array for adjacent chars
      if (r + 1 <= n)
        update1(r + 1, 26 - x);  // Cancel out the impact on next element
      if (r - l >= 1) {  // At least one gap between l and r
        if (l >= 3)
          update2(l, x);  // Update difference array for palindromic triplets
        if (l + 1 >= 3)
          update2(l + 1, x);  // Update for l+1
        if (r + 1 <= n)
          update2(r + 1, 26 - x);  // Cancel out next element's impact
        if (r + 2 <= n)
          update2(r + 2, 26 - x);  // Cancel out element after next
      } else {  // l and r are adjacent
        if (l >= 3)
          update2(l, x);  // Update difference array
        if (r + 2 <= n)
          update2(r + 2, 26 - x);  // Cancel out next element
      }
    } else {
      if (query1(l, r) && query2(l, r))  // Check both conditions
        cout << "YES\n";
      else
        cout << "NO\n";
    }
  }
  bit1.clear();  // Clear the BITs for next test case
  bit2.clear();
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/