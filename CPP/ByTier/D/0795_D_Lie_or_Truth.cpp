// Problem: CF 795 D - Lie or Truth
// https://codeforces.com/contest/795/problem/D

/*
Purpose: Determine if Stepan's claim about swapping cubes within a range [l, r] is truthful or a lie.
         The algorithm checks if elements outside the range [l, r] are the same in both sequences.
         If they differ, then Stepan must have changed something outside the claimed range, which is impossible.
         Then, it verifies if the elements within range [l, r] can be rearranged to match in the second sequence.

Algorithms/Techniques: 
- Linear scan to compare elements outside the range [l, r]
- No sorting or advanced algorithm needed since we only check positions outside the range

Time Complexity: O(n), where n is the number of cubes.
Space Complexity: O(n), due to storing two vectors of size n.

*/
#include <algorithm>
#include <iostream>
#include <vector>

#define int long long
#define endl "\n"
using namespace std;
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int a, l, r;
  cin >> a >> l >> r;
  vector<int> v(a);  // Original sequence
  vector<int> v1(a); // Modified sequence
  for (int i = 0; i < a; i++) {
    cin >> v[i];
  }
  for (int i = 0; i < a; i++) {
    cin >> v1[i];
  }
  // Check if elements outside the range [l, r] are the same in both sequences
  for (int i = 0; i < a; i++) {
    if (i < l - 1 || i > r - 1) {  // If current index is outside the claimed swap range
      if (v[i] != v1[i]) {         // If elements differ at this position
        cout << "LIE";
        return 0;  // Since Stepan only swapped within [l, r], elements outside should be same
      }
    }
  }
  cout << "TRUTH";
}


// https://github.com/VaHiX/CodeForces/