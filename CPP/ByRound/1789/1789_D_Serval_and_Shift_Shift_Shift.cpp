// Problem: CF 1789 D - Serval and Shift-Shift-Shift
// https://codeforces.com/contest/1789/problem/D

/*

Algorithm/Techniques: 
    - This problem involves transforming a binary string `a` to another binary string `b` using specific operations
    - Operation allowed: a = a XOR (a << k) or a = a XOR (a >> k) where k is the shift amount
    - The key insight is to analyze the bits and determine which operations (left or right shifts) can help transform one string to another
    - Preprocessing steps: check if transformation is even possible (both strings have same number of 1s)
    - The algorithm uses a greedy approach to find a sequence of at most n operations
    - Time and Space Complexity: O(n^2) time, O(n) space due to string manipulation and storing operations

Input:
    - Number of test cases t
    - For each test case:
        - n (number of bits)
        - Binary string a
        - Binary string b

Output:
    - If possible:
        - Number of operations m (0 to n)
        - List of operations k1, k2, ..., km (shift amounts)
    - If not possible:
        - -1

*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define int long long
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define RREP(i, a, b) for (int i = (a) - 1; i > (b) - 1; i--)
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define zero(a) memset(a, 0, sizeof(a))
#define neg(a) memset(a, -1, sizeof(a))
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef vector<long long> vll;
typedef long long ll;
typedef pair<double, double> pd;
typedef pair<long long, long long> pll;
int N = 998244353;
int fact[(1 << 20) + 2], rfact[(1 << 20) + 2];
int qpow(int a, int b) {
  int ans = 1;
  while (b != 0) {
    if (b % 2 == 0) {
      a = (int)a * a % N;
      b /= 2;
    } else {
      ans = ans * a % N;
      b--;
    }
  }
  return ans;
}
int inv(int a) { return qpow(a, N - 2); }
int choose(int n, int k) {
  if (k > n || k < 0)
    return 0;
  return fact[n] * rfact[k] % N * rfact[n - k] % N;
}
int gcd(int a, int b) {
  if (b > a)
    return gcd(b, a);
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    bool good = false, bad = false;
    REP(i, 0, n) if (b[i] == '1') good = true;
    REP(i, 0, n) if (a[i] == '1') bad = true;
    if (good != bad) {
      cout << "-1\n";
      continue;
    }
    if (!good && !bad) {
      cout << "0\n";
      continue;
    }
    int x;
    REP(i, 0, n) {
      if (a[i] == '1') {
        x = i;
        break;
      }
    }
    vi ans;
    string temp;
    REP(i, 0, n) {
      if (a[i] != b[i] && i != x) {
        ans.pb(i - x);
        temp = a;
        REP(j, i, min(n, n + i - x)) {
          if (a[j] != a[j + x - i])
            temp[j] = '1';
          else
            temp[j] = '0';
        }
        a = temp;
        if (i < x)
          x = i;
      }
    }
    int r;
    REP(i, 0, n) {
      if (a[i] == '1')
        r = i;
    }
    RREP(i, x + 1, 0) {
      if (a[i] != b[i]) {
        ans.pb(i - r);
        temp = a;
        REP(j, 0, n + i - r) {
          if (a[j] != a[j + r - i])
            temp[j] = '1';
          else
            temp[j] = '0';
        }
        a = temp;
      }
    }
    if (a != b || ans.size() > n)
      return 1;
    cout << ans.size() << "\n";
    if (ans.size() == 0)
      continue;
    REP(i, 0, ans.size()) cout << -ans[i] << " ";
    cout << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/