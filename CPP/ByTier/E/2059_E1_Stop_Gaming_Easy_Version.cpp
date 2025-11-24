// Problem: CF 2059 E1 - Stop Gaming (Easy Version)
// https://codeforces.com/contest/2059/problem/E1

/*
E1. Stop Gaming (Easy Version)
Algorithms/Techniques: Simulation, Two Pointers

Time Complexity: O(n * m) amortized per test case
Space Complexity: O(n * m)

The problem involves transforming n arrays of size m each from an initial state 'a' to a final state 'b'
using a specific operation where we can prepend an element to arrays and shift following arrays.

This solution uses a simulation approach with two pointers to find the minimum number of operations
by comparing elements in both arrays and tracking mismatches.
*/
#include <iostream>
using namespace std;
const int N = 3e5 + 10;
int a[N], b[N];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n * m; i++)
    cin >> a[i];
  for (int i = 0; i < n * m; i++)
    cin >> b[i];
  
  int pa = 0, pb = 0, flag = 1, ans = n * m;
  
  while (flag) {
    // Move pb forward until we find a matching element or reach end
    while (pb != n * m && b[pb] != a[pa])
      pb++;
    
    if (pb == n * m)
      break; // No more matches, stop searching
    
    // If elements are in the same row (array)
    if (pa / m == pb / m) {
      pa++, pb++; // Advance both pointers
      
      // Check if current row elements match
      while (pa % m != 0 && pa / m == pb / m) {
        if (a[pa] != b[pb]) {
          flag = 0; // Mismatch found, stop
          break;
        }
        pa++, pb++; // Move to next element in row
      }
    } else {
      // If elements are in different rows, only advance both pointers
      pa++, pb++;
    }
    
    if (flag)
      ans = n * m - pa; // Update answer with remaining elements to process
  }
  
  cout << ans << endl;
  return;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int _;
  cin >> _;
  while (_--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/