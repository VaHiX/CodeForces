// Problem: CF 2089 D - Conditional Operators
// https://codeforces.com/contest/2089/problem/D

/*
D. Conditional Operators
Problem Description:
Given a binary string of length 2n+1, determine if we can insert n conditional operators (?:) such that the resulting expression evaluates to 1.
The expression uses right-associativity for ?: operators.
Algorithms/Techniques:
- Recursive backtracking with memoization or pattern matching based on first and last characters
- String manipulation and parsing logic to build valid expressions
Time Complexity: O(N^2) average case, where N = 2n+1 is the length of the string due to recursive calls and string operations
Space Complexity: O(N^2) for recursion stack and intermediate string constructions

Code Purpose:
This code solves a problem related to evaluating conditional expressions from binary strings.
It checks if a given string of length 2n+1 can be structured as an expression with n conditional operators
that evaluates to 1. It returns either "Yes" or "No". If yes, it gives a valid expression.
*/

#include <assert.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
using ll = long long;
const ll ILL = 2167167167167167167;
const int INF = 2100000000;
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
#define all(p) p.begin(), p.end()
template <class T> using _pq = priority_queue<T, vector<T>, greater<T>>;
template <class T> int LB(vector<T> &v, T a) {
  return lower_bound(v.begin(), v.end(), a) - v.begin();
}
template <class T> int UB(vector<T> &v, T a) {
  return upper_bound(v.begin(), v.end(), a) - v.begin();
}
template <class T> bool chmin(T &a, T b) {
  if (b < a) {
    a = b;
    return 1;
  } else
    return 0;
}
template <class T> bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return 1;
  } else
    return 0;
}
template <class T> void So(vector<T> &v) { sort(v.begin(), v.end()); }
template <class T> void Sore(vector<T> &v) {
  sort(v.begin(), v.end(), [](T x, T y) { return x > y; });
}
bool yneos(bool a, bool upp = false) {
  if (a) {
    cout << (upp ? "YES\n" : "Yes\n");
  } else {
    cout << (upp ? "NO\n" : "No\n");
  }
  return a;
}
template <class T> void vec_out(vector<T> &p, int ty = 0) {
  if (ty == 2) {
    cout << '{';
    for (int i = 0; i < (int)p.size(); i++) {
      if (i) {
        cout << ",";
      }
      cout << '"' << p[i] << '"';
    }
    cout << "}\n";
  } else {
    if (ty == 1) {
      cout << p.size() << "\n";
    }
    for (int i = 0; i < (int)(p.size()); i++) {
      if (i)
        cout << " ";
      cout << p[i];
    }
    cout << "\n";
  }
}
template <class T> T vec_min(vector<T> &a) {
  assert(!a.empty());
  T ans = a[0];
  for (auto &x : a)
    chmin(ans, x);
  return ans;
}
template <class T> T vec_max(vector<T> &a) {
  assert(!a.empty());
  T ans = a[0];
  for (auto &x : a)
    chmax(ans, x);
  return ans;
}
template <class T> T vec_sum(vector<T> &a) {
  T ans = T(0);
  for (auto &x : a)
    ans += x;
  return ans;
}
int pop_count(long long a) {
  int res = 0;
  while (a) {
    res += (a & 1), a >>= 1;
  }
  return res;
}
template <class T> T square(T a) { return a * a; }
string fill(string S) {
  int M = S.size();
  string T;
  rep(i, 0, M) {
    if (i % 2 == 0) {
      T += "(";
      T += S[i];
    } else {
      T += "?";
      T += S[i];
      T += ":";
    }
  }
  rep(i, 0, M / 2 + 1) T += ")";
  return T;
}
string solve_sub(string S) {
  int N = (int)(S.size()) / 2; // compute half size of string
  if (N == 0) {                // base case: only one char
    if (S[0] == '1')
      return S;
    return "?";
  }
  if (S[0] == '1') {
    int ind = 1;           // start from index 1
    while (ind <= N * 2 && S[ind] == '0') // skip zeros to find first non-zero after opening
      ind += 2;
    if (ind <= N * 2) {       // there is a valid choice for left side
      return "1?(" + fill(S.substr(1, ind)) + "):(" +
             fill(S.substr(ind + 1, N * 2 - ind)) + ")";
    }
    auto tmp = solve_sub(S.substr(1, N * 2 - 1)); // recurse deeper
    if (tmp != "?") {
      return "1?(" + tmp + "):" + S.back(); // append the final char to right side
    }
  }
  int ind = N * 2; // last character index
  if (S[ind] == '0') {  // check if last character is zero
    ind--;
    while (0 < ind && S[ind] == '0') // find first non-zero before last char going backward
      ind -= 2;
    int mid = ind; // this marks midpoint of current segment
    ind--;
    while (0 <= ind && S[ind] == '0') // continue until first non-zero
      ind -= 2;
    if (ind < 0) {
      return "?"; // no good way to resolve
    }
    mid = ind + 1; // update middle index properly
    while (S[mid] == '0') // move to next non-zero
      mid += 2;
    if (ind == 0) { // special case when we start at position 0
      return "1?" + fill(S.substr(1, mid)) + ":" +
             fill(S.substr(mid + 1, N * 2 - mid));
    }
    if (S[0] == '0') {
      return "0?" + fill(S.substr(1, ind - 1)) + ":(1?" +
             fill(S.substr(ind + 1, mid - ind)) + ":" +
             fill(S.substr(mid + 1, N * 2 - mid)) + ")";
    }
    if (ind != 2) { // check if we can use special format
      return fill(S.substr(0, 3)) + "?" + fill(S.substr(3, ind - 3)) + ":(1?" +
             fill(S.substr(ind + 1, mid - ind)) + ":" +
             fill(S.substr(mid + 1, N * 2 - mid)) + ")";
    }
    return "?"; // fallback
  } else { // last char is '1'
    if (S[0] == '0') {
      return "0?" + fill(S.substr(1, N * 2 - 1)) + ":1";
    } else if (N == 1) {
      return "?"; // fallback for single pair
    } else {
      return fill(S.substr(0, 3)) + "?" + fill(S.substr(3, N * 2 - 3)) + ":1";
    }
  }
}
void solve();
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  rep(i, 0, t) solve();
}
void solve() {
  int N;
  cin >> N;
  string S;
  cin >> S;
  auto ans = solve_sub(S);
  if (yneos(ans != "?"))
    cout << ans << "\n";
}


// https://github.com/VaHiX/codeForces/