/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
void print_vec(vector<int> &a) {
  for (int i : a) {
    cout << i << " ";
  }
  cout << '\n';
}
int main() {
  string s;
  cin >> s;
  int n = s.length();
  vector<int> z(n, 0);
  int l = 0, r = 0;
  for (int i = 1; i < n; ++i) {
    if (r > i)
      z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] > r) {
      r = i + z[i];
      l = i;
    }
  }
  int ans = 0;
  set<int> st;
  set<int> remain;
  unordered_map<int, int> freq;
  for (int i = 1; i < n; ++i) {
    if (z[i] + i == n) {
      st.insert(z[i]);
    } else {
      remain.insert(z[i]);
    }
    freq[z[i]]++;
  }
  int ct = 0;
  for (auto i = st.rbegin(); i != st.rend(); ++i) {
    auto v = remain.lower_bound(*i);
    if (v != remain.end()) {
      ans = *i;
      break;
    } else {
      if (ct) {
        ans = *i;
        break;
      }
    }
    ct++;
  }
  if (ans == 0) {
    cout << "Just a legend\n";
  } else {
    for (int i = 0; i < ans; ++i) {
      cout << s[i];
    }
  }
}