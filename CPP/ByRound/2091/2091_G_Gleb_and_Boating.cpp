/*
 * Problem URL : https://codeforces.com/problemset/problem/2091/G
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
  int t;
  cin >> t;
  long long n, tam;
  while (t--) {
    cin >> n >> tam;
    long long i, f;
    i = n % tam, f = n % tam;
    while (true) {
      if (i == 0)
        break;
      tam = tam - 2;
      if (tam == 0 || tam == 1) {
        tam = 1;
        break;
      }
      i = (i + 1);
      // int rest_tam=((n-f)/(tam+1))*(tam+1);
      f = f + (n - f) / (tam + 1) + (n - (f)) / (tam + 2) - 1;
      // cout<<"i: "<<i<<" f: "<<f<<" tam: "<<tam<<endl;
      long long dif = f - i;
      i = i % tam;
      if (i == 0)
        break;
      if (i + dif >= tam)
        break;
      f = f % tam;
    }
    cout << tam << endl;
  }
  return 0;
}
