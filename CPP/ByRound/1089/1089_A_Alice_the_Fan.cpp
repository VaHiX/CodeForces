/*
 * Problem URL : https://codeforces.com/contest/1089/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

int n;
int r[20][2];

int disA(int a, int b, int ma, int mb) {
  int d;
  for (int i = 0; i < mb; i++)
    d = max(0, min(a, r[i][1] - 2 - r[i][0])), r[i][0] += d, a -= d;
  return a;
}

int disB(int a, int b, int ma, int mb) {
  int d;
  for (int i = 0; i < ma; i++)
    d = max(0, min(b, r[i + mb][0] - 2 - r[i + mb][1])), r[i + mb][1] += d, b -= d;
  return b;
}

bool isPos(int a, int b, int ma, int mb) {
  if (ma != 3 && mb != 3 || ma + mb == 6)
    return false;
  if (ma != 3) {
    bool ip = isPos(b, a, mb, ma);
    if (ip) {
      for (int i = 0; i < ma + mb; i++)
        swap(r[i][0], r[i][1]);
    }
    return ip;
  }
  // ma = 3, mb < 3
  int mas = 1000, asub = 0, mbs = 1000, bsub = 0;
  for (int i = 0; i < mb; i++)
    r[i][0] = 0, r[i][1] = 25, b -= 25, asub += 23, mas = 23;
  for (int i = 0; i < ma; i++)
    r[i + mb][0] = (i + mb == 4 ? 15 : 25), r[i + mb][1] = 0, a -= r[i + mb][0], bsub += r[i + mb][0] - 2, mbs = r[i + mb][0] - 2;
  if (a < 0 || b < 0)
    return false;
  if (a <= asub && b <= bsub) {
    a = disA(a, b, ma, mb);
    b = disB(a, b, ma, mb);
    return true;
  }
  int as, bs, d;
  as = a - mas;
  d = max(0, min(as, b));
  bs = b - d;
  as -= d;
  if (as >= 0 && bs >= 0 && as <= asub - mas && bs <= bsub) {
    r[0][0] += mas + d;
    a -= mas + d;
    r[0][1] += d;
    b -= d;
    a = disA(a, b, ma, mb);
    b = disB(a, b, ma, mb);
    return true;
  }
  bs = b - mbs;
  d = max(0, min(bs, a));
  as = a - d;
  bs -= d;
  if (as >= 0 && bs >= 0 && as <= asub && bs <= bsub - mbs) {
    r[ma + mb - 1][1] += mbs + d;
    b -= mbs + d;
    r[ma + mb - 1][0] += d;
    a -= d;
    a = disA(a, b, ma, mb);
    b = disB(a, b, ma, mb);
    return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(12);
  cin >> n;
  int a, b;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    int wa = 0, wb = 0;
    bool fs = false;
    for (int j = 3; j >= 0 && !fs; j--)
      for (int k = 0; k <= 3 && !fs; k++)
        wa = j, wb = k, fs = isPos(a, b, j, k);
    if (!fs)
      cout << "Impossible\n";
    else {
      cout << wa << ":" << wb << "\n";
      for (int i = 0; i < wa + wb; i++)
        cout << r[i][0] << ":" << r[i][1] << (i < wa + wb - 1 ? " " : "\n");
    }
  }
}
