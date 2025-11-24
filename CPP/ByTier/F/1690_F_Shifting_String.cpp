// Problem: CF 1690 F - Shifting String
// https://codeforces.com/contest/1690/problem/F

/*
Algorithm: 
- This problem involves finding the minimum number of operations to return a string to its original state after repeatedly applying a permutation.
- The key insight is that each permutation can be decomposed into cycles.
- For each cycle, we determine the length of the cycle (i.e., how many operations it takes for the elements in that cycle to return to their original positions).
- The answer is the least common multiple (LCM) of all these cycle lengths.

Time Complexity: O(n^2) in the worst case due to string matching in the 'find' operation.
Space Complexity: O(n) for storing the permutation and visited array.

The solution works by:
1. Identifying all cycles in the permutation.
2. For each cycle, constructing the string formed by elements in that cycle.
3. Determining the minimal rotation of that string which equals the original (this is the cycle length).
4. Taking LCM of all cycle lengths.
*/
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    long long n, ans = 1;
    string s;
    cin >> n;
    vector<long long> v(n + 1), vis(n + 1);
    cin >> s;
    for (int i = 1; i <= n; i++) {
      cin >> v[i];
    }
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        string t;
        for (int j = i; !vis[j]; j = v[j]) {
          vis[j] = 1;
          t += s[j - 1];  // Build the cycle string by appending characters
        }
        int cnt = (t + t).find(t, 1);  // Find the minimal rotation period of the cycle
        ans = lcm(ans, cnt);  // Update the answer with LCM of all cycle lengths
      }
    }
    cout << ans << endl;
  }
}


// https://github.com/VaHiX/CodeForces/