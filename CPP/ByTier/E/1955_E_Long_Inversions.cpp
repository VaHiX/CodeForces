// Problem: CF 1955 E - Long Inversions
// https://codeforces.com/contest/1955/problem/E

/*
Purpose: 
This code solves the problem of finding the maximum value of k such that 
a binary string can be transformed into all '1's using operations that invert 
k consecutive characters. The approach uses a transformation of the input string 
and checks for each possible k whether it's valid.

Algorithms/Techniques:
- Transformation of input string into a toggle sequence.
- For each possible k from n down to 2, test if the transformation allows inversion.
- Mathematical property: the number of operations needed for each group is determined 
  by checking if the count of '1's in each segment is even.

Time Complexity: O(n^3) in worst case due to nested loops checking each k and segment.
Space Complexity: O(n) for storing the transformed string t.

*/

#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  string t;
  char prv = '1';
  for (char c : s) {
    if (c != prv)
      t.push_back('1'); // If current char differs from previous, mark a toggle
    else
      t.push_back('0');
    prv = c;
  }
  if (s.back() != '1')
    t.push_back('1'); // Add a marker at the end based on final character
  else
    t.push_back('0');
  // Try k from n down to 2, to find the maximum valid k
  for (int k = n; k >= 2; k--) {
    bool ok = 1;
    for (int i = 0; i < k; i++) {
      int cnt = 0;
      // Count '1's in every k-th position starting from i
      for (int j = i; j <= n; j += k) {
        if (t[j] == '1')
          cnt++;
      }
      // If odd number of '1's, this k is invalid
      if (cnt % 2) {
        ok = 0;
        break;
      }
    }
    if (ok) {
      cout << k << '\n';
      return;
    }
  }
  cout << "1\n"; // If no valid k > 1, return 1
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/