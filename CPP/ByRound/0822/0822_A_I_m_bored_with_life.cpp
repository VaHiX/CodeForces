/*
 * Problem URL : https://codeforces.com/contest/822/problem/A
 * Submit Date : 2025-09-01
 */

/*
 * Problem URL : https://codeforces.com/contest/822/problem/A
 * Submit Date : 2025-08-31
 */



#include <bits/stdc++.h>

typedef long long int ll;

#define pp pair<ll, ll>
#define dbg printf("in\n");
#define NL printf("\n");

#define inf 1000000000000

using namespace std;

int main() {

  ll i, j, k;
  ll n, m, x;

  cin >> n >> m;
  x = min(n, m);

  k = 1;
  while (x > 0) {
    k *= x;
    x--;
  }

  cout << k;

  return 0;
}
