// Problem: CF 1867 E1 - Salyg1n and Array (simple version)
// https://codeforces.com/contest/1867/problem/E1

/*
Purpose: Solve the interactive problem of finding the XOR of all elements in an array
         using queries of XOR of subarrays of length k, with the constraint that
         each subarray queried gets reversed.

Algorithms/Techniques:
    - Use XOR properties: XOR of a subarray can be used to deduce XOR of overlapping subarrays
    - For even n, process all k-sized segments separately
    - For odd n, adjust the handling to avoid double counting elements
    - Queries are made in a pattern to maximize information gain with limited queries (100)

Time Complexity: O(n/k) per test case, which is effectively O(n) since k <= n
Space Complexity: O(1) - only using a few variables for computation

*/
#include <iostream>

#define forn(i, aa, bb) for (int i = aa; i <= bb; ++i)
#define LL long long
using namespace std;
const LL mod = 998244353;
const int N = 1e5 + 5;
int n, k;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> k;
    int ans = 0;
    if (n % k == 0) {
      // If n is divisible by k, process all segments of size k
      for (int i = 1; i <= n; i += k) {
        cout << "? " << i << '\n';
        cout.flush();
        int x;
        cin >> x;
        ans ^= x; // XOR all segment XORs to get final result
      }
      cout << "! " << ans << '\n';
      cout.flush();
      continue;
    }
    // If n is not divisible by k, process full segments and handle remainder
    for (int i = 1; i <= n; i += k) {
      if (i + k - 1 > n)
        break;
      cout << "? " << i << '\n';
      cout.flush();
      int x;
      cin >> x;
      ans ^= x;
    }
    int num = n % k;
    // Query overlapping segment to resolve the remainder part
    cout << "? " << n - k - num / 2 + 1 << '\n';
    cout.flush();
    int x;
    cin >> x;
    ans ^= x;
    // Query another overlapping segment
    cout << "? " << n - k + 1 << '\n';
    cout.flush();
    cin >> x;
    ans ^= x;
    cout << "! " << ans << '\n';
    cout.flush();
  }
}


// https://github.com/VaHiX/CodeForces/