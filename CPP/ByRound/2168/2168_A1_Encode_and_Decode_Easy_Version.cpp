// Problem: CF 2168 A1 - Encode and Decode (Easy Version)
// https://codeforces.com/contest/2168/problem/A1

/*
 * Purpose: Encode and decode an array of integers using a run-twice communication strategy.
 * 
 * Algorithm:
 * - First run (mode == "first"): 
 *   - Reads array elements (each in range [1, 26])
 *   - Encodes each element by converting it to a lowercase letter (1 -> 'a', 2 -> 'b', ..., 26 -> 'z')
 *   - Outputs the resulting string s
 * - Second run (mode == "second"):
 *   - Reads the encoded string s
 *   - Decodes each character back to its corresponding integer value
 *   - Outputs n (length of original array) and the decoded array elements
 * 
 * Time Complexity: O(n) for both encoding and decoding phases.
 * Space Complexity: O(n) for storing the encoded string and the decoded array.
 */

#include <stdio.h>
#include <iostream>
#include <string>

#define ll long long
#define db double
#define sti string
#define vt vector
#define INF ((int)1e9)
#define MOD 1000000007
#define pii pair<int, int>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define pll pair<ll, ll>
#define pdd pair<db, db>
#define all(x) x.begin(), x.end()
#define dbg(x) cerr << #x << " = " << x << '\n';
#define bit(mask, i) ((mask >> i) & 1)
#define fi first
#define sc second
using namespace std;
const sti name = "";
const int MAXN = 1e6;
inline void file() {
  freopen((name + ".inp").c_str(), "r", stdin);
  freopen((name + ".out").c_str(), "w", stdout);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  sti mode;
  cin >> mode;
  if (mode[0] == 'f') {
    // First run: Encoding phase
    int n;
    cin >> n;
    while (n--) {
      int a;
      cin >> a;
      // Convert integer a (1-26) to corresponding lowercase letter ('a'-'z')
      cout << char(a + 'a' - 1);
    }
  } else {
    // Second run: Decoding phase
    sti s;
    cin >> s;
    // Output the size of original array
    cout << s.size() << '\n';
    // Decode each character back to integer
    for (char &c : s)
      cout << (c - 'a' + 1) << ' ';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/