// Problem: CF 2022 D2 - Asesino (Hard Version)
// https://codeforces.com/contest/2022/problem/D2

#include <iostream>

using namespace std;
int query(int i, int j) {
  cout << "? " << i << ' ' << j << endl;
  int ans;
  cin >> ans;
  return ans;
}
void done(int i) { cout << "! " << i << endl; }
void solve() {
  int n;
  cin >> n;
  if (n == 3)
    done(query(1, 2) == query(2, 1) ? 3 : query(2, 3) == query(3, 2) ? 1 : 2);
  int nt = 0;
  while (n > 5) {
    if (query(n - 1, n) == query(n, n - 1)) {
      if (!nt)
        nt = n;
      n -= 2;
    } else {
      if (!nt)
        nt = 1;
      done(n - (query(nt, n) == query(n, nt)));
      return;
    }
  }
  if (n == 4)
    done((query(1, 3) == query(3, 1)) + 2 * (query(1, 2) == query(2, 1)) + 1);
  if (n == 5) {
    int a = query(1, 2), b = query(2, 3), c = query(3, 1);
    if ((a + b + c) & 1)
      done(query(1, 4) == query(4, 1) ? 5 : 4);
    else
      done(a == query(2, 1) ? 3 : (b != query(3, 2)) + 1);
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/