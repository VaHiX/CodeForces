// Problem: CF 1862 G - The Great Equalizer
// https://codeforces.com/contest/1862/problem/G

/*
 * Problem: G. The Great Equalizer
 * 
 * Purpose: Simulate a device that processes an array through a series of operations,
 *          including sorting, deduplication, appending arithmetic progressions, and
 *          maintaining the maximum element of the final array after each operation.
 * 
 * Techniques:
 *  - Multiset for maintaining sorted unique elements
 *  - Priority queue to track differences between adjacent elements
 *  - Efficient update of difference tracking when elements are modified
 * 
 * Time Complexity: O((n + q) * log n) per test case due to multiset and priority queue operations
 * Space Complexity: O(n) for storing the array and auxiliary data structures
 * 
 * Algorithm Overview:
 *  1. Preprocess the initial array into a multiset for sorted unique values
 *  2. Compute initial differences between adjacent elements using a priority queue
 *  3. For each query:
 *     a. Remove old element from multiset and insert new one
 *     b. Update difference tracking accordingly
 *     c. Remove outdated differences from priority queue
 *     d. Output result based on max element + min difference
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>

using namespace std;
using ll = long long;
#define MAX 300005
#define ii pair<int, int>
int tc;
ll n, a[MAX], q;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> tc;
  while (tc--) {
    multiset<ll> s;
    priority_queue<ll> dis, dis_tmp;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1; i <= n; i++)
      s.insert(a[i]);
    for (auto it = s.begin(); it != s.end(); it++) {
      auto next = it;
      next++;
      if (next == s.end())
        break;
      dis.push(*next - *it);
    }
    cin >> q;
    while (q--) {
      ll i, x;
      cin >> i >> x;
      if (n == 1) {
        cout << x << " ";
        a[i] = x;
        continue;
      }
      auto it = s.find(a[i]);
      auto next = it, prev = it;
      next++;
      prev--;
      if (it == s.begin()) {
        dis_tmp.push(*next - *it);
      } else if (next == s.end()) {
        dis_tmp.push(*it - *prev);
      } else {
        dis_tmp.push(*it - *prev);
        dis_tmp.push(*next - *it);
        dis.push(*next - *prev);
      }
      s.erase(it);
      s.insert(x);
      it = s.find(x);
      next = it, prev = it;
      next++;
      prev--;
      if (it == s.begin()) {
        dis.push(*next - *it);
      } else if (next == s.end()) {
        dis.push(*it - *prev);
      } else {
        dis_tmp.push(*next - *prev);
        dis.push(*next - *it);
        dis.push(*it - *prev);
      }
      while (!dis_tmp.empty() && dis.top() == dis_tmp.top()) {
        dis.pop();
        dis_tmp.pop();
      }
      a[i] = x;
      auto element_max = s.end();
      element_max--;
      cout << *element_max + dis.top() << " ";
    }
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/