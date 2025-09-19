/*
 * Problem URL : https://codeforces.com/problemset/problem/28/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
const int MAX = 509;
int x[MAX], y[MAX], nl[MAX], m[MAX], l[MAX], N, M;
bool fl[MAX];
int length(int a, int b) { return abs(x[a] - x[b]) + abs(y[a] - y[b]); }
int index(int i) { return (i + N) % N; }
void go(int num, int cnt) {
  if (cnt == N / 2) {
    cout << "YES\n";
    for (int i = 0; i < N; i++)
      cout << m[i] << ' ';
    exit(0);
  }
  for (int i = 0; i < M; i++)
    if (!fl[i] && nl[num] == l[i]) {
      fl[i] = true;
      m[num] = i + 1;
      go(num + 2, cnt + 1);
      return;
    }
}
int main() {
  cin >> N >> M;
  for (int i = 0; i < N; i++)
    cin >> x[i] >> y[i];
  for (int i = 0; i < M; i++)
    cin >> l[i];
  for (int i = 0; i < N; i++)
    nl[i] = length(index(i - 1), i) + length(i, index(i + 1)), m[i] = -1;
  go(0, 0);
  for (int i = 0; i < M; i++)
    fl[i] = 0;
  for (int i = 0; i < N; i++)
    m[i] = -1;
  go(1, 0);
  cout << "NO";
}