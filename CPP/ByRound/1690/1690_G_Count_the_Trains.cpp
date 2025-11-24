// Problem: CF 1690 G - Count the Trains
// https://codeforces.com/contest/1690/problem/G

/*
Algorithm: 
- Use a set to maintain the start positions of trains.
- Initially, process the array to determine the initial train formations.
- For each update operation, adjust the set of train starts based on the new speed of the affected carriage.
- Maintain the speed of each carriage and update the set accordingly to recompute train counts efficiently.

Time Complexity: O((n + m) * log n)
Space Complexity: O(n)

Techniques:
- Set data structure for efficient insertion and deletion of train start positions.
- Preprocessing to initialize the trains.
- Efficiently updating the set of train starts after each modification.

*/
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], k, d;
void solve() {
  set<int> s; // Set to store the start positions of trains
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  int pos = 0, minn = 2e9; // pos: last train start position, minn: minimum speed so far
  for (int i = 1; i <= n; i++) {
    // If current carriage's speed is less than the minimum seen so far, 
    // it starts a new train
    if (i == 1 || a[i] < minn)
      s.insert(i), pos = i;
    minn = min(minn, a[i]);
  }
  while (m--) {
    cin >> k >> d;
    // Remove any train starts that now fall under the new speed of carriage k
    while (s.lower_bound(k) != s.end() && a[*s.lower_bound(k)] >= a[k] - d)
      s.erase(s.lower_bound(k));
    // Insert k if it's a new train start
    if (s.lower_bound(k) == s.begin() || a[*(--s.lower_bound(k))] > a[k] - d)
      s.insert(k);
    a[k] -= d; // Update the speed of carriage k
    cout << s.size() << ' '; // Print number of trains after this update
  }
  cout << '\n';
  return;
}
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/