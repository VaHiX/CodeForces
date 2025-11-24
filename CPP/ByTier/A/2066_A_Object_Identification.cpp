// Problem: CF 2066 A - Object Identification
// https://codeforces.com/contest/2066/problem/A

/*
Interactive problem to determine if the jury has hidden Object A (directed graph) or Object B (points on a plane).
Algorithm:
- For each test case, we first check for a missing value in x array to detect unique structure.
- If the missing value is found, do 1 query and analyze result to determine object.
- Otherwise, find positions of 1 and n in x array.
- Perform two queries between these positions and compare the responses.
Time Complexity: O(n) per test case
Space Complexity: O(n)
*/
#include <iostream>

using namespace std;
typedef long long LL;
const int MAXN = 2e5 + 5;
int n, x[MAXN];
bool vis[MAXN];
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i)
      vis[i] = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> x[i], vis[x[i]] = 1; // Mark all elements in x as visited
    }
    int a, b;
    for (int i = 1; i <= n; ++i) {
      if (!vis[i]) { // Find the missing number from 1 to n
        cout << "? " << i << ' ' << (i == 1 ? 2 : 1) << endl; // Query with a fixed node (1 or 2)
        int res;
        cin >> res;
        if (res == 0)
          cout << "! A" << endl; // If distance is 0, it's likely Object A (graph)
        else
          cout << "! B" << endl; // Otherwise it's Object B (points)
        goto end; // End the current test case
      }
    }
    // If all values from 1 to n are present in x
    for (int i = 1; i <= n; ++i) {
      if (x[i] == 1)
        a = i;   // Position of value 1 in x
      if (x[i] == n)
        b = i;   // Position of value n in x
    }
    cout << "? " << a << ' ' << b << endl; // Query between positions of 1 and n
    int A;
    cin >> A;
    cout << "? " << b << ' ' << a << endl; // Reverse query
    int B;
    cin >> B;
    if (A < n - 1 || B < n - 1)   // If either distance is less than n-1, it's likely Graph (A)
      cout << "! A" << endl;
    else
      cout << "! B" << endl; // Otherwise, it's Points (B)
  end:;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/