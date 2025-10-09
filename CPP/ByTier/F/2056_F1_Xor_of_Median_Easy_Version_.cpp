/*
 * Problem URL : https://codeforces.com/problemset/problem/2056/F1
 * Submit Date : 2025-08-24
 */

#include <iostream>
using namespace std;
const int N = 100005;
int T, K, m;
char s[N];
int main() {
  int i, c, x;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &K, &m);
    scanf("%s", s + 1);
    int B = 0, Ans = 0;
    for (i = 1; i <= K; i++) {
      if (s[i] == '1')
        B++;
    }
    for (c = 0; c < B; c++) {
      if (((B - (c + 1)) & (c >> 1)) == 0) {
        for (x = 0; x < m; x++) {
          if ((x & c) == c) {
            Ans ^= x;
          }
        }
      }
    }
    printf("%d\n", Ans);
  }
}