// Problem: CF 1733 D1 - Zero-One (Easy Version)
// https://codeforces.com/contest/1733/problem/D1

/*
Algorithm/Technique: Greedy, Two Pointers
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing positions of differing bits

The problem involves transforming string 'a' into string 'b' using specific operations.
Each operation flips two bits at indices l and r. If l+1 == r, cost is x; otherwise, cost is y.
The key insight is that we only need to flip bits that differ between the strings.
We can group these differing positions and determine the minimum cost by analyzing:
1. If there's an odd number of differing bits, it's impossible.
2. If there are exactly two differing bits and they are adjacent, choose the cheaper operation.
3. Otherwise, it's optimal to pair up differing bits greedily, choosing between adjacent (cost x) or non-adjacent (cost y) operations.

*/
#include <algorithm>
#include <iostream>
#include <string>

#define ll long long
using namespace std;
const ll N = 1e5 + 50;
ll T, n, x, y, p[N], tot, ans;
string a, b;
int main() {
  cin >> T;
  while (T--) {
    cin >> n >> x >> y;
    cin >> a >> b;
    tot = ans = 0;
    // Store positions of differing bits
    for (ll i = 0; i < n; i++)
      if (a[i] != b[i])
        p[++tot] = i;
    // If number of differing bits is odd, impossible to pair all
    if (tot & 1) {
      cout << "-1\n";
      continue;
    }
    // Special case: only two differing bits and they are adjacent
    if (tot == 2 && p[1] == p[2] - 1) {
      cout << min(y * 2, x) << '\n';
      continue;
    }
    // General case: pair up all differing positions optimally
    cout << y * tot / 2 << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/