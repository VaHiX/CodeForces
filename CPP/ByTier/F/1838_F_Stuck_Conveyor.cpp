// Problem: CF 1838 F - Stuck Conveyor
// https://codeforces.com/contest/1838/problem/F

/*
Algorithm: Binary search on the stuck conveyor position combined with directional checks
Time Complexity: O(n^2 * log(n^2)) due to binary search over n^2 positions and 
                 each query taking O(n^2) time to process
Space Complexity: O(n^2) for storing the grid and path information

Approach:
- The solution uses a two-phase strategy:
  1. First, determine if there's an infinite loop by trying to detect which row/column
     the stuck conveyor is likely on
  2. If there's no infinite loop, use binary search to find the stuck conveyor's row/col
  3. Then, determine the direction by trying all four directions with a fixed position
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define endl '\n'
#define prec(x)                                                                \
  cout << fixed;                                                               \
  cout.precision(x);
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
#define all(v) v.begin(), v.end()
#define minpq(T) priority_queue<T, vector<T>, greater<T>>
#define For(i, j, k) for (int i = (int)(j); i <= (int)(k); i++)
#define Rep(i, j, k) for (int i = (int)(j); i >= (int)(k); i--)
#define debug1(x, y) cout << x << " :: " << y << " "
#define coutn cout << "\n"
#define INF 1987654321
vpii vt;
string s[4], query[123];
int n;
void SolveProblem() {
  cin >> n;
  s[1] += 'v';
  s[3] += '^';
  for (int i = 0; i < n - 1; i++) {
    s[0] += '>';
    s[1] += '<';
    s[2] += '>';
    s[3] += '<';
  }
  s[0] += 'v';
  s[2] += '^';
  int flag = 0;
  cout << "? 1 1" << endl;
  for (int i = 0; i < n; i++)
    cout << s[i % 2] << endl;
  cout << flush;
  int x, y;
  cin >> x >> y;
  if (x == y && x == -1) {
    // If infinite loop detected, perform binary search over positions
    for (int i = 1; i <= n; i++) {
      if (i % 2)
        for (int j = 1; j <= n; j++)
          vt.push_back(pii(i, j));
      else
        for (int j = n; j >= 1; j--)
          vt.push_back(pii(i, j));
    }
    for (int i = 0; i < n; i++)
      query[i] = s[i % 2];
    int l = 0, r = n * n - 1, mid;
    while (l < r) {
      mid = (l + r + 1) / 2;
      cout << "? " << vt[mid].first << ' ' << vt[mid].second << endl;
      for (int i = 0; i < n; i++)
        cout << query[i] << endl;
      cout << flush;
      cin >> x >> y;
      if (x == -1)
        l = mid;
      else
        r = mid - 1;
    }
    cout << "? " << vt[l].first << ' ' << vt[l].second << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        cout << 'v';
      cout << endl;
    }
    cout << flush;
    cin >> x >> y;
    cout << "! " << vt[l].first << ' ' << vt[l].second << ' ';
    if (x == -1) {
      cout << '^' << endl;
      cout << flush;
    } else if (y == vt[l].second + 1) {
      cout << '>' << endl;
      cout << flush;
    } else {
      cout << '<' << endl;
      cout << flush;
    }
  } else if (n % 2 && x == n + 1 && y == n ||
             n % 2 == 0 && x == n + 1 && y == 1) {
    // Different logic for even/odd cases
    for (int i = n; i >= 1; i--) {
      if (i % 2)
        for (int j = n; j >= 1; j--)
          vt.push_back(pii(i, j));
      else
        for (int j = 1; j <= n; j++)
          vt.push_back(pii(i, j));
    }
    for (int i = 0; i < n; i++)
      query[i] = s[(i + 1) % 2 + 2];
    int l = 1 - n * n, r = n * n - 1, mid;
    while (l < r) {
      mid = (l + r + 1) / 2;
      cout << "? " << vt[mid].first << ' ' << vt[mid].second << endl;
      for (int i = 0; i < n; i++)
        cout << query[i] << endl;
      cout << flush;
      cin >> x >> y;
      if (x == n + 1) {
        cout << "! " << vt[0].first << ' ' << vt[0].second << " v " << endl;
        cout << flush;
        return;
      }
      if (x == -1)
        l = mid;
      else
        r = mid - 1;
    }
    cout << "? " << vt[l].first << ' ' << vt[l].second << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        cout << '^';
      cout << endl;
    }
    cout << flush;
    cin >> x >> y;
    cout << "! " << vt[l].first << ' ' << vt[l].second << ' ';
    if (x == -1 || x == n + 1) {
      cout << 'v' << endl;
      cout << flush;
    } else if (y == vt[l].second + 1) {
      cout << '>' << endl;
      cout << flush;
    } else {
      cout << '<' << endl;
      cout << flush;
    }
  } else {
    // Determine direction based on final exit point
    if (x == 0) {
      cout << "! " << x + 1 << ' ' << y << ' ' << '^' << endl;
      cout << flush;
    } else if (x == n + 1) {
      cout << "! " << x - 1 << ' ' << y << ' ' << 'v' << endl;
      cout << flush;
    } else if (y == 0) {
      cout << "! " << x << ' ' << y + 1 << ' ' << '<' << endl;
      cout << flush;
    } else {
      cout << "! " << x << ' ' << y - 1 << ' ' << '>' << endl;
      cout << flush;
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int test_case = 1;
  for (int tc = 1; tc <= test_case; tc++) {
    SolveProblem();
  }
}


// https://github.com/VaHiX/CodeForces/