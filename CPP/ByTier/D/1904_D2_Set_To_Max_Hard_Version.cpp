// Problem: CF 1904 D2 - Set To Max (Hard Version)
// https://codeforces.com/contest/1904/problem/D2

/*
Algorithm:
This problem uses a deque-based approach to simulate the operations and
determine if array `a` can be transformed into array `b`. The key insight is
that we can only set a segment to the maximum value in that segment. So we
process the array from left to right and right to left, using a deque to
maintain the maximum value in the current window and check if the current
position can be set to the target value.

Time Complexity: O(n)
Space Complexity: O(n)

Methods:
- Two passes through the array (left to right and right to left)
- Using a deque to maintain the maximum element in the current window
- For each position, we check if we can set it to the desired value in `b`
*/
#include <algorithm>
#include <deque>
#include <iostream>
#include <stdio.h>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;
namespace Fread {
const int SIZE = 1 << 16;
char buf[SIZE], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SIZE, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread

void solve();
int main() {
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}
void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 2), b(n + 2);
  for (int x = 1; x <= n; x++)
    cin >> a[x];
  for (int x = 1; x <= n; x++)
    cin >> b[x];
  deque<int> dq;
  for (int x = 1; x <= n; x++) {
    // Remove elements from back that are smaller than or equal to current a[x]
    while (!dq.empty() && dq.back() <= a[x])
      dq.pop_back();
    // Remove elements from front that are greater than current b[x]
    while (!dq.empty() && dq.front() > b[x])
      dq.pop_front();
    // Add current a[x] to the back of deque
    dq.push_back(a[x]);
    // If the front of deque equals b[x], we can set a[x] to b[x]
    if (dq.front() == b[x])
      a[x] = b[x];
  }
  // Process from right to left
  for (int x = n; x >= 1; x--) {
    // Same logic as above
    while (!dq.empty() && dq.back() <= a[x])
      dq.pop_back();
    while (!dq.empty() && dq.front() > b[x])
      dq.pop_front();
    dq.push_back(a[x]);
    if (dq.front() == b[x])
      a[x] = b[x];
  }
  // Check if all elements in a match b
  for (int x = 1; x <= n; x++)
    if (a[x] != b[x]) {
      cout << "NO" << endl;
      return;
    }
  cout << "YES" << endl;
}

// https://github.com/VaHiX/CodeForces/