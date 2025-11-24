// Problem: CF 1983 C - Have Your Cake and Eat It Too
// https://codeforces.com/contest/1983/problem/C

/*
Algorithm/Techniques: 
- Greedy approach with three pointers to find valid contiguous subarrays for each person
- Try all 6 possible orderings of assigning subarrays to Alice, Bob, Charlie
- For each ordering, use a helper function `ok` to validate if a valid assignment exists
- Time Complexity: O(n) for each test case, since we are scanning the array at most twice per call to the helper function.
- Space Complexity: O(1) extra space excluding input storage

The problem is about fairly distributing a cake among three people such that:
1. Each gets a contiguous slice
2. Each slice is worth at least ceil(tot/3) to the respective owner
3. No piece is assigned to more than one person

We try all 6 possible permutations of assigning the three slices to Alice, Bob, and Charlie, and for each permutation,
we attempt to find a valid assignment using a greedy approach.
*/

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using namespace __gnu_pbds;
template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag,
                              tree_order_statistics_node_update>;
#define Chaawal25                                                              \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define ll long long
#define endl '\n'

// Helper function to determine if a valid assignment exists with given orderings
pair<int, int> ok(vector<int> &a, vector<int> &b, vector<int> &c, ll tot) {
  int n = a.size();
  int l = 0, r = -1, r1;
  ll as = 0;
  // Find minimum subarray for Alice (start from beginning)
  while (l < n) {
    as += a[l];
    l++;
    if (as >= tot)
      break;
  }
  if (as < tot)
    return {-1, -1}; // Not enough value for Alice
  ll bs = 0;
  r = l; // Start from where Alice finishes
  // Find minimum subarray for Bob 
  while (r < n) {
    bs += b[r];
    r++;
    if (bs >= tot)
      break;
  }
  if (bs < tot)
    return {-1, -1}; // Not enough value for Bob
  ll cs = 0;
  r1 = r; // Start from where Bob finishes
  // Find minimum subarray for Charlie
  while (r1 < n) {
    cs += c[r1];
    r1++;
    if (cs >= tot)
      break;
  }
  if (cs < tot)
    return {-1, -1}; // Not enough value for Charlie
  return {l, r}; // Return indices for Alice and Bob (Charlie gets the rest)
}

int main() {
  Chaawal25 int tc = 1;
  cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> b[i];
    for (int i = 0; i < n; i++)
      cin >> c[i];
    ll tot = 0;
    for (int i = 0; i < n; i++) {
      tot += a[i];
    }
    // Calculate minimum required value each person should receive
    if (tot % 3)
      tot = tot / 3 + 1;
    else
      tot /= 3;
    pair<int, int> ans = ok(a, b, c, tot);
    if (ans.first != -1) {
      // Output assignment: Alice, Bob, Charlie
      cout << 1 << " " << ans.first << " ";
      cout << ans.first + 1 << " " << ans.second << " ";
      cout << ans.second + 1 << " " << n << " ";
      cout << endl;
      continue;
    }
    ans = ok(a, c, b, tot); // Try different orderings
    if (ans.first != -1) {
      cout << 1 << " " << ans.first << " ";
      cout << ans.second + 1 << " " << n << " ";
      cout << ans.first + 1 << " " << ans.second << " ";
      cout << endl;
      continue;
    }
    ans = ok(b, a, c, tot);
    if (ans.first != -1) {
      cout << ans.first + 1 << " " << ans.second << " ";
      cout << 1 << " " << ans.first << " ";
      cout << ans.second + 1 << " " << n << " ";
      cout << endl;
      continue;
    }
    ans = ok(b, c, a, tot);
    if (ans.first != -1) {
      cout << ans.second + 1 << " " << n << " ";
      cout << 1 << " " << ans.first << " ";
      cout << ans.first + 1 << " " << ans.second << " ";
      cout << endl;
      continue;
    }
    ans = ok(c, a, b, tot);
    if (ans.first != -1) {
      cout << ans.first + 1 << " " << ans.second << " ";
      cout << ans.second + 1 << " " << n << " ";
      cout << 1 << " " << ans.first << " ";
      cout << endl;
      continue;
    }
    ans = ok(c, b, a, tot);
    if (ans.first != -1) {
      cout << ans.second + 1 << " " << n << " ";
      cout << ans.first + 1 << " " << ans.second << " ";
      cout << 1 << " " << ans.first << " ";
      cout << endl;
      continue;
    }
    cout << -1 << endl; // No valid assignment found
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/