// Problem: CF 1454 F - Array Partition
// https://codeforces.com/contest/1454/problem/F

/*
Purpose: This code solves the problem of partitioning an array into three consecutive non-empty parts such that
         the maximum element of the first part equals the minimum element of the second part,
         which also equals the maximum element of the third part.

Algorithms/Techniques:
- Preprocessing to compute prefix maxima (ml) and suffix maxima (mr)
- Binary search or greedy approach to find valid split points
- Use of vector to store indices of maximum elements

Time Complexity: O(n) per test case, as we process each element a constant number of times.
Space Complexity: O(n) for storing arrays ml, mr and vector mx.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 7;
int n, a[N], ml[N], mr[N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    ml[0] = 0;
    mr[n + 1] = 0;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    // Compute prefix maximum values
    for (int i = 1; i <= n; i++)
      ml[i] = max(a[i], ml[i - 1]);
    // Compute suffix maximum values
    for (int i = n; i >= 1; i--)
      mr[i] = max(a[i], mr[i + 1]);
    // Collect all indices where maximum element occurs
    vector<int> mx;
    for (int i = 1; i <= n; i++)
      if (a[i] == ml[n])
        mx.push_back(i);
    int c = ml[n]; // The global maximum value
    int l = mx[mx.size() / 2], r = l; // Start from middle index of max elements
    while (true) {
      if (l == 1 || r == n) { // If either part is empty, no valid split
        cout << "NO\n";
        break;
      }
      // Check if current l and r give valid partitions
      if (ml[l - 1] == c && mr[r + 1] == c) {
        cout << "YES\n";
        cout << l - 1 << " " << r - l + 1 << " " << n - r << "\n";
        break;
      }
      int nxt_l = -1, nxt_r = -1;
      // Calculate next potential left boundary for improvement
      if (l - 2 >= 1)
        nxt_l = min(a[l - 1], ml[l - 2]);
      // Calculate next potential right boundary for improvement
      if (r + 2 <= n)
        nxt_r = min(a[r + 1], mr[r + 2]);
      
      // Greedily improve the candidate by choosing the direction yielding better min in next step
      if (nxt_l > nxt_r)
        c = min(c, a[--l]); // Move left and update c
      else
        c = min(c, a[++r]); // Move right and update c
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/