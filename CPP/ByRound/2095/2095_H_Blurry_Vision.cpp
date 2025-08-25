/*
 * Problem URL : https://codeforces.com/problemset/problem/2095/H
 * Submit Date : 2025-08-20
 */

#include <iostream>
using namespace std;
int main() {
  int n;
  cin >> n;
  string s[11] = {"CODEFORCES", "EYE",   "TESTING",   "SYSTEM",
                  "APRIL",      "FOOLS", "YOU",       "READ",
                  "POORLY",     "GET",   "EYEGLASSES"};
  cout << s[n - 1];
}