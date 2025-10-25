#include <bits/stdc++.h>
using namespace std;
typedef long long l;
l n, a[15], b[2000];
int main() {
  cin >> n;
  while (clock() / CLOCKS_PER_SEC <= 1.00)
    ;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= n; i++)
    cout << a[i] << ' ';
  return 0;
}