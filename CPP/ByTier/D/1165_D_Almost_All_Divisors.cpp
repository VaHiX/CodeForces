/*
 * Problem URL : https://codeforces.com/problemset/problem/1165/D
 * Submit Date : 2025-08-16
 */

#include <iostream>
#include <set>
using namespace std;
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    long long N;
    set<int> S, D;
    cin >> n;
    while (n--) {
      cin >> N;
      S.insert(N);
    }
    N = (long long)*(S.begin()) * (*(S.rbegin()));
    for (n = 2; 1LL * n * n <= N; n++)
      if (N % n == 0) {
        D.insert(n);
        D.insert(N / n);
      }
    if (D == S)
      cout << N;
    else
      cout << -1;
    cout << endl;
  }
}
