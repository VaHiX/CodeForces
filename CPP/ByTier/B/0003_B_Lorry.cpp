/*
 * Problem URL : https://codeforces.com/problemset/problem/3/B
 * Submit Date : 2025-08-09
 */

#include <bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;

const int MaxN = 1e5;
int n, v;
int t, p;
int len1, sum1[MaxN + 10], len2, sum2[MaxN + 10];
pii p1[MaxN + 10], p2[MaxN + 10];
int mx_v, len;

int main() {
  scanf("%i%i", &n, &v);
  for (int i = 1; i <= n; ++i) {
    scanf("%i%i", &t, &p);
    if (t == 1) {
      p1[++len1] = {p, i};
    } else {
      p2[++len2] = {p, i};
    }
  }
  sort(&p1[1], &p1[len1] + 1, greater<>());
  for (int i = 1; i <= len1; ++i) {
    sum1[i] = sum1[i - 1] + p1[i].fir;
  }
  sort(&p2[1], &p2[len2] + 1, greater<>());
  for (int i = 1; i <= len2; ++i) {
    sum2[i] = sum2[i - 1] + p2[i].fir;
  }
  for (int i = 0; i <= len2; ++i) {
    if (0 <= v - 2 * i && sum2[i] + sum1[min(len1, v - 2 * i)] > mx_v) {
      mx_v = sum2[i] + sum1[min(len1, v - 2 * i)];
      len = i;
    }
  }
  printf("%i\n", mx_v);
  for (int i = 1; i <= len; ++i) {
    printf("%i ", p2[i].sec);
  }
  for (int i = 1; i <= min(len1, v - 2 * len); ++i) {
    printf("%i ", p1[i].sec);
  }
  printf("\n");
  return 0;
}