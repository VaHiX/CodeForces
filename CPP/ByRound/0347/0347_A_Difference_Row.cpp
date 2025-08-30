/*
 * Problem URL : https://codeforces.com/problemset/problem/347/A
 * Submit Date : 2025-08-15
 */

#include <bits/stdc++.h>

typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, ll>
#define inf 1000000000

using namespace std;

int main() {

  int i, j, k;
  int n;

  cin >> n;

  int a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];

  sort(a, a + n);
  swap(a[0], a[n - 1]);

  for (i = 0; i < n; i++)
    cout << a[i] << " ";

  return 0;
}
