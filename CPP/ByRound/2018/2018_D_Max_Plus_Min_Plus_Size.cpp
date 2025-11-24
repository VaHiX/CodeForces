// Problem: CF 2018 D - Max Plus Min Plus Size
// https://codeforces.com/contest/2018/problem/D

/*
D. Max Plus Min Plus Size
Algorithm: Dynamic Programming + Segment Tree with Union-Find like logic for merging intervals
Time Complexity: O(n log n) per test case due to sorting and union-find operations
Space Complexity: O(n) for arrays and vectors

Problem Summary:
Given an array of positive integers, select a subset of elements such that no two adjacent elements are selected.
The score is defined as max(element) + min(element) + count(elements).
Goal is to find the maximum possible score.

Approach:
- Sort elements by value descending to process higher values first
- Use Union-Find like structure to track contiguous segments of selected elements
- For each element, determine optimal way to merge with adjacent selections to maximize score
- Track total number of elements and if there's a valid selection (non-zero count)
*/
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int a[200010], l[200010], r[200010], f[200010];
vector<int> u;
bool b[200010]; // marks if element is currently selected
int lms(int x) { return l[x] == l[l[x]] ? l[x] : l[x] = lms(l[x]); } // find leftmost in segment
int rms(int x) { return r[x] == r[r[x]] ? r[x] : r[x] = rms(r[x]); } // find rightmost in segment
inline bool check(int l, int r) {
  if (f[l] <= r)
    return true;
  if ((r - l + 1) % 2 == 0 && f[l + 1] <= r)
    return true;
  return false;
}
int main() {
  int t, n;
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], l[i] = r[i] = i;
      u.emplace_back(i);
    }
    sort(u.begin(), u.end(), [&](int x, int y) { return a[x] > a[y]; }); // Sort indices by value decreasing
    memset(f, 0x3f, (n + 5) << 2); // Initialize f array to infinity
    for (int i = n; i; i--) {
      f[i] = f[i + 2]; // Dynamic programming backward update for potential merges
      if (a[i] == a[u[0]]) // Only when current value equals max value
        f[i] = i;
    }
    int ans = 0, tot = 0, cnt = 0; // ans: final answer, tot: total number of elements, cnt: valid segments count
    for (const int &i : u) {
      b[i] = true; // Mark current element as selected
      if (b[i - 1]) { 
        // Previous element is selected -> merge intervals
        tot -= (i - lms(i - 1) + 1) / 2;
        cnt -= check(lms(i - 1), i - 1);
        l[i] = lms(i - 1); // Merge left boundary
        r[i - 1] = rms(i); // Merge right boundary
      }
      if (b[i + 1]) {
        // Next element is selected -> merge intervals
        tot -= (rms(i + 1) - i + 1) / 2;
        cnt -= check(i + 1, rms(i + 1));
        r[i] = rms(i + 1);
        l[i + 1] = lms(i);
      }
      tot += (rms(i) - lms(i) + 2) / 2; // Update number of elements in combined segments
      cnt += check(lms(i), rms(i));     // Check if segment is valid (has at least one element)
      ans = max(ans, a[u[0]] + a[i] + tot - !cnt); // Compute score with this pair
    }
    cout << ans << '\n';
    u.clear();
    memset(b, 0, n + 5);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/