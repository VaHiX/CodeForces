// Problem: CF 2111 D - Creating a Schedule
// https://codeforces.com/contest/2111/problem/D

/*
 * Problem: D. Creating a Schedule
 * Algorithm/Technique: Sorting, Greedy Placement
 *
 * Time Complexity: O(m log m + n * m) where m is the number of classrooms and n is the number of groups.
 * Space Complexity: O(m) for storing classroom indices.
 *
 * Description:
 * Given n groups and m classrooms with distinct indices, we need to assign each group 6 classes
 * such that the total movement between floors (based on the prefix of the class index) is maximized.
 * The solution sorts classrooms by their indices and assigns them in an alternating pattern
 * to maximize floor differences. Each group gets consecutive slots in a specific pattern.
 */

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 1e5 + 10;
int a[N];

void solve() {
  int n, m;
  cin >> m >> n; // Read number of classrooms and groups
  for (int i = 0; i < n; ++i)
    cin >> a[i]; // Read classroom indices
  sort(a, a + n); // Sort classrooms by index to facilitate greedy assignment

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < 6; ++j) {
      // Alternate between low and high indexed classrooms to maximize floor movement
      if ((i + j) % 2 == 0)
        cout << a[i / 2] << ' '; // Use smaller indices (for even positions)
      else
        cout << a[n - i / 2 - 1] << ' '; // Use larger indices (for odd positions)
    }
    cout << '\n'; // End of row
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int _;
  cin >> _; // Read number of test cases
  while (_--)
    solve(); // Process each test case
  return 0;
}


// https://github.com/VaHiX/codeForces/