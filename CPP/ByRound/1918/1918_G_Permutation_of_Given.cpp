// Problem: CF 1918 G - Permutation of Given
// https://codeforces.com/contest/1918/problem/G

/*
Algorithm/Technique: Pattern-based Construction
Purpose: This code solves a problem where we need to find a permutation of integers of length n such that when each element is replaced by the sum of its neighbors, the resulting array is a permutation of the original array.

Time Complexity: O(n), where n is the input number. The algorithm constructs the output array in linear time by using pre-defined patterns based on n % 6.
Space Complexity: O(1), as the space used does not depend on the input size beyond the output array.

The solution handles all cases by identifying patterns based on n modulo 6:
- For n = 3 or 5, it's impossible to construct such an array.
- For other values, it follows specific repeating patterns to form the solution array.
*/

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

#define pb push_back
#define all(n) n.begin(), n.end()
#define Z size()
#define S second
#define F first
#define ll long long
#define fo(x, y, z) for (ll x = y; x <= z; x++)
#define of(x, y, z) for (ll x = y; x >= z; x--)
using namespace std;
void value(int in) {
  cout << ((in) ? "YES\n" : "NO\n");
  return;
}
const ll md = 1e9 + 7, mod = 998244353;
ll n, m, k, xd, zd, ans;
ll a[500005], b[500005];
string s;
set<ll> f, g;
vector<ll> v;
queue<ll> q;
void CD() {
  cin >> n;
  if (n == 3 || n == 5) {
    value(0);
    return;
  }
  if (n % 6 == 0) {
    value(1);
    cout << "2 1 -1 ";
    fo(i, 1, n / 6 - 1) cout << "1 -1 -2 -1 1 2 ";
    cout << "1 -1 -2" << "\n";
    return;
  }
  if (n % 6 == 1) {
    value(1);
    cout << "-5 8 1 -3 -4 ";
    fo(i, 1, n / 6 - 1) cout << "-1 3 4 1 -3 -4 ";
    cout << "-2 5" << "\n";
    return;
  }
  if (n % 6 == 2) {
    value(1);
    fo(i, 1, n / 6) cout << "1 -1 -2 -1 1 2 ";
    cout << "1 -1" << "\n";
    return;
  }
  if (n % 6 == 3) {
    value(1);
    cout << "2 1 1 -3 -4 -1 3 ";
    fo(i, 1, n / 6 - 1) cout << "4 1 -3 -4 -1 3 ";
    cout << "3 -2" << "\n";
    return;
  }
  if (n % 6 == 4) {
    value(1);
    fo(i, 1, n / 6) cout << "1 -1 -2 -1 1 2 ";
    cout << "1 -1 1 2" << "\n";
    return;
  }
  if (n % 6 == 5) {
    value(1);
    cout << "-2 1 1 -3 -4 -1 3 ";
    fo(i, 1, n / 6 - 1) cout << "4 1 -3 -4 -1 3 ";
    cout << "2 -1 2 4" << "\n";
    return;
  }
}
int main() {
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(0);
  int t = 1;
  while (t--) {
    CD();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/