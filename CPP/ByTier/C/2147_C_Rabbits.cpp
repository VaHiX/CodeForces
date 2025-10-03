// Problem: CF 2147 C - Rabbits
// https://codeforces.com/contest/2147/problem/C

/*
C. Rabbits
Algorithm: Greedy approach to check for valid rabbit placements
Time Complexity: O(n) per test case, where n is the length of string s
Space Complexity: O(1) additional space (excluding input storage)

The problem involves placing rabbits in empty pots such that none jump into another pot.
We look for specific 3-character patterns in the string representing empty pots with neighbors,
and attempt to assign directions to avoid conflicts. The algorithm scans for forbidden configurations
and immediately returns "NO" if any are found, otherwise "YES".
*/
#include <stddef.h>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;
long long int a[200000], b[200000], c1[200000];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  cout.tie(NULL);
  long long int t, i, p, j, w, k, n, r, x, q, kib, l, z, y, f, g, d, h;
  set<long long int> s1;
  char c;
  string s;
  map<long long int, long long int> m;
  cin >> t;
  g = 0;
  while (t--) {
    cin >> n >> s;
    for (i = 0; i < n - 2; ++i) {
      // Check for the pattern "101" with surrounding '0's
      if ((s[i] == '1') && (s[i + 1] == '0') && (s[i + 2] == '1')) {
        // If both neighbors are '0', mark one of them as '2' to indicate conflict resolution
        if ((s[i - 1] == '0') && (s[i + 3] == '0')) {
          s[i - 1] = '2'; // Mark left neighbor as used
        } else if (s[i + 3] == '0') {
          s[i + 3] = '2'; // Mark right neighbor as used
          s[i + 1] = '2'; // Mark middle pot (occupied) as used to prevent jumping
        } else if (s[i - 1] == '0') {
          s[i + 1] = '2'; // Mark middle pot as used
        } else {
          cout << "No" << endl;
          goto kib; // Exit early if no valid assignment found
        }
      }
    }
    cout << "Yes" << endl;
  kib: {}
  }
}


// https://github.com/VaHiX/CodeForces/