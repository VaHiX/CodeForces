// Problem: CF 1833 F - Ira and Flamenco
// https://codeforces.com/contest/1833/problem/F

/*
 * Problem: Ira and Flamenco
 * 
 * Purpose: Count the number of "magnificent dances" that can be formed from a list of student levels.
 * A magnificent dance involves exactly m students, all with distinct levels, and the absolute difference
 * between any two levels is strictly less than m.
 * 
 * Key Techniques:
 * - Sorting the array to group same levels together
 * - Sliding window technique using a queue to maintain valid ranges of levels
 * - Modular arithmetic with modular inverse for division
 * 
 * Time Complexity: O(n log n + n) per test case due to sorting and single pass through array
 * Space Complexity: O(n) for storing the array and queue
 * 
 * Algorithm:
 * 1. Sort the student levels.
 * 2. Use a sliding window approach with a queue to maintain valid groups of m distinct levels.
 * 3. For each unique level, update the count of ways to form valid combinations.
 * 4. Apply modular arithmetic to handle large numbers.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;
#define lli long long int
#define mp make_pair
#define pb push_back
const lli mod = 1000000007;
lli gcdEx(lli a, lli b, lli &x, lli &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  lli x1, y1;
  lli d = gcdEx(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}
lli modInverse(lli a) {
  lli x, y;
  gcdEx(a, mod, x, y);
  return (x % mod + mod) % mod;
}
int a[200005], x;
lli ans, k, cnt, tmp;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
      cin >> a[i];
    sort(a, a + n);
    ans = 0;
    k = 1;
    queue<pair<int, lli>> q;
    for (int i = 0; i < n; i++) {
      x = a[i];
      cnt = 0;
      while (i < n && a[i] == x) {
        cnt++;
        i++;
      }
      i--; // Adjust i back since outer loop will increment it
      if (q.size() == m) {
        // Remove the first element from queue and update k accordingly
        tmp = modInverse(q.front().second);
        k = (k * tmp) % mod;
        q.pop();
      }
      while (q.size() > 0 && a[i] - q.front().first >= m) {
        // Remove outdated entries whose difference with current level is >= m
        tmp = modInverse(q.front().second);
        k = (k * tmp) % mod;
        q.pop();
      }
      k = (k * cnt) % mod; // Multiply k by current count of elements with same level
      q.push(mp(x, cnt));  // Push current level and its count
      if (q.size() == m)
        ans = (ans + k) % mod; // If we have m elements, add k to answer
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/