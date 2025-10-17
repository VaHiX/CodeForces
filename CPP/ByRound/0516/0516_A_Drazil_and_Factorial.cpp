/*
 * Problem URL : https://codeforces.com/contest/516/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
string s, M[] = {"", "", "2", "3", "322", "5", "53", "7", "7222", "7332"};
long long a;
int main() {
  cin >> a >> a;
  while (a)
    s += M[a % 10], a /= 10;
  sort(s.rbegin(), s.rend());
  cout << s;
}
