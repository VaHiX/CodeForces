// Problem: CF 2072 D - For Wizards, the Exam Is Easy, but I Couldn't Handle It
// https://codeforces.com/contest/2072/problem/D

/*
D. For Wizards, the Exam Is Easy, but I Couldn't Handle It
Problem: Minimize inversions in an array by performing one cyclic left shift on a subarray.

Algorithms/Techniques:
- Brute-force approach over all possible subarrays [l, r]
- For each subarray, simulate a left cyclic shift and compute the number of inversions.
- Keep track of the best (minimum) inversion count and corresponding subarray indices.

Time Complexity: O(n^3) per test case — nested loops for subarrays and inversion counting.
Space Complexity: O(n) — to store the array elements.

*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
      cin >> x;
    
    int best = 0, L = 1, R = 1; // Initialize with default values
    
    for (int i = 0; i < n; i++) {
      int d = 0; // Count of inversions for current subarray shift
      for (int j = i + 1; j < n; j++) {
        if (a[j] > a[i])
          d++;
        else if (a[j] < a[i])
          d--;
        if (d < best) { // Update minimum inversion count and indices
          best = d;
          L = i + 1;
          R = j + 1;
        }
      }
    }
    cout << L << " " << R << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/