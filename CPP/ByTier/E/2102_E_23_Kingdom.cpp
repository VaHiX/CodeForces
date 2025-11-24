// Problem: CF 2102 E - 23 Kingdom
// https://codeforces.com/contest/2102/problem/E

/*
 * Problem: E. 23 Kingdom
 * Purpose: Find the maximum beauty of any "nice" array derived from input array,
 *          where a nice array has elements bounded by the input array and beauty 
 *          is defined as sum of max gaps between occurrences of each value.
 * 
 * Algorithm:
 * - For each element in the array, we track how far we can extend to the left/right
 *   without exceeding the bounds of the input array.
 * - We precompute prefix and suffix arrays where pref[i] represents maximum gap 
 *   to the left at position i, and suf[i] represents maximum gap to the right.
 * - For each valid split point (i, i+1), we take minimum of pref[i] and suf[i+1]
 *   and accumulate to get final answer.
 *
 * Time Complexity: O(n log n) per test case due to set operations
 * Space Complexity: O(n)
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

#define FAST                                                                   \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;

int main() {
  FAST;
  int Tt;
  cin >> Tt;
  while (Tt--) {
    int n;
    cin >> n;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
      cin >> v[i];
    vector<int> pref(n + 1);   // prefix gap array
    vector<int> suf(n + 1);    // suffix gap array
    set<int> s;                // set of available indices
    for (int i = 1; i <= n; i++)
      s.insert(i);
    for (int i = 1; i <= n; i++) {
      auto it = s.upper_bound(v[i]);   // find first index > v[i]
      if (it != s.begin())             // if there exists such an index
        s.erase(prev(it));             // remove the one just before it
      pref[i] = n - s.size();          // store remaining size as gap
    }
    for (int i = 1; i <= n; i++)
      s.insert(i);
    for (int i = n; i >= 1; i--) {
      auto it = s.upper_bound(v[i]);   // find first index > v[i]
      if (it != s.begin())             // if there exists such an index
        s.erase(prev(it));             // remove the one just before it
      suf[i] = n - s.size();           // store remaining size as gap
    }
    long long ans = 0;
    for (int i = 1; i < n; i++)
      ans += min(pref[i], suf[i + 1]);   // accumulate min of left/right gaps
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/