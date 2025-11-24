// Problem: CF 2167 A - Square?
// https://codeforces.com/contest/2167/problem/A

/*
Purpose: Determine if four given stick lengths can form a square.
Algorithm: Check if all four stick lengths are equal.
Time Complexity: O(1) - We only check 4 elements once.
Space Complexity: O(1) - Only using a fixed-size vector of 4 elements.

Techniques:
- Simple comparison of all elements in the input array
- Early termination if any two elements differ
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define int long long int
#define double long double
#define endl '\n'
const int MOD = 1000000007;

void solve() {
  vector<int> a(4, 0);  // Create a vector to store 4 stick lengths
  for (int i = 0; i < 4; i++)
    cin >> a[i];  // Read the four stick lengths

  // Compare each stick length with the previous one
  for (int i = 1; i < 4; i++) {
    if (a[i] != a[i - 1]) {  // If any two consecutive sticks differ
      cout << "No\n";       // Cannot form a square
      return;               // Exit immediately
    }
  }
  cout << "YES\n";  // All sticks are equal, so we can form a square
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;  // Read number of test cases
  while (t--) {
    solve();  // Process each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/