/*
 * Problem URL : https://codeforces.com/contest/319/problem/A
 * Submit Date : 2025-09-06
 */

#include <iostream>
using namespace std;
long long a, l = 1, M = 1000000007;
string S;
int main() {
  cin >> S;
  for (int i = S.length() - 1; i >= 0; i--) {
    a = (2 * a + l * (S[i] == '1')) % M;
    l = 4 * l % M;
  }
  cout << a;
}