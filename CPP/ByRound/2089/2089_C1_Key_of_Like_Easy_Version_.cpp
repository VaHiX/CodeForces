/*
 * Problem URL : https://codeforces.com/problemset/problem/2089/C1
 * Submit Date : 2025-08-22
 */

#include "iostream"

using namespace std;

typedef long long int lli;

#define fori(x) for (int i = 0; i < (x); i++)
#define MOD (1000000000 + 7)

#define N 100
#define L 5000

int p[2][N];
int e[N];

int invMod(int a) {
  return a <= 1 ? a : MOD - (long long)(MOD / a) * invMod(MOD % a) % MOD;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, l, k;
    cin >> n >> l >> k;

    int prv = 0;
    int crt = 1;

    fori(n) {
      p[prv][i] = 0;
      p[crt][i] = 0;
      e[i] = 0;
    }

    int inv_l = invMod(l);
    int acc = ((l / n) * (lli)inv_l) % MOD;

    fori(n) {
      p[prv][i] = acc;
      if (i < (l % n))
        p[prv][i] = (p[prv][i] + inv_l) % MOD;
    }

    fori(n) e[i] = p[prv][i];

    for (int j = l - 1; j >= 1; j--) {
      inv_l = invMod(j);
      fori(n) p[prv][i] = (p[prv][i] * (lli)inv_l) % MOD;

      acc = ((j / n) * (lli)inv_l) % MOD;
      fori(j % n) acc = (acc + p[prv][n - 1 - i]) % MOD;

      int accl = (n - (j % n)) % n;
      fori(n) {
        p[crt][i] = acc;
        acc = (((lli)acc - p[prv][accl] + MOD) + p[prv][i]) % MOD;
        accl = (accl + 1) % n;
      }

      fori(n) e[i] = (e[i] + p[crt][i]) % MOD;
      crt = (crt + 1) % 2;
      prv = (prv + 1) % 2;
    }

    fori(n) cout << e[i] << " ";
    cout << endl;
  }

  return 0;
}
