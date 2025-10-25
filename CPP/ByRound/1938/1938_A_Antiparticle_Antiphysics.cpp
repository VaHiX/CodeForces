/*
 * Problem URL : https://codeforces.com/contest/1938/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back

const int N = 1e5 + 5;
char S[N], E[N];
int n, m, i, j, a, p, T, s1, s2, e1, e2;
vector<pair<string, int>> ans;

void add(int x) {
  int len = strlen(S);
  if (S[x] == 'A') {
    ans.pb({"+A", x + 1});
    while (len > x)
      S[len + 2] = S[len], --len;
    S[x] = S[x + 2] = 'P', S[x + 1] = 'A';
  } else {
    ans.pb({"+P", x + 1});
    while (len > x)
      S[len + 2] = S[len], --len;
    S[x] = S[x + 2] = 'A', S[x + 1] = 'P';
  }
}

void sub(int x) {
  int len = strlen(S);
  if (S[x] == 'A') {
    ans.pb({"-A", x + 1});
    while (x + a <= len)
      S[x] = S[x + a], ++x;
  } else {
    ans.pb({"-P", x + 1});
    while (x + p <= len)
      S[x] = S[x + p], ++x;
  }
}

bool Wrk() {
  s1 = s2 = e1 = e2 = 0;
  for (i = 0; i < n; i++)
    S[i] == 'A' ? ++s1 : ++s2;
  for (i = 0; i < m; i++)
    E[i] == 'A' ? ++e1 : ++e2;
  if (!(a % 2) && (s1 - e1) & 1)
    return false;
  if (!(p % 2) && (s2 - e2) & 1)
    return false;
  if (!(a % 4) && !(p % 4)) {
    int cnt = 0;
    for (i = 0; i < n; i++)
      for (j = i + 1; j < n; j++)
        cnt += (S[i] == 'P' && S[j] == 'A');
    for (i = 0; i < m; i++)
      for (j = i + 1; j < m; j++)
        cnt += (E[i] == 'P' && E[j] == 'A');
    if ((cnt + (s1 - e1) / 2 + (s2 - e2) / 2) & 1)
      return false;
  }

  for (i = 0; i < m; i++)
    if (S[i] != E[i]) {
      if (S[i] != 0)
        add(i);
      else
        add(i - 1), add(i - 1), --i;
    }

  n = strlen(S), s1 = s2 = 0;
  for (i = m; i < n; i++)
    S[i] == 'A' ? ++s1 : ++s2;

  if (s1 || s2) {
    if (!s1 || !s2)
      add(m), (!s1) ? s1 = 2 : s2 = 2;
    if (a % 4) {
      for (i = m;; i++)
        if (S[i] == 'A')
          break;
      while (s2 % p)
        add(i), ++i, s2 += 2;

      for (i = m; S[i]; i++)
        if (S[i] == 'A') {
          j = i;
          while (S[j] == 'A')
            ++j;
          if (S[j] == 0)
            break;
          while ((j - i) % a)
            add(j), ++j;
          while (j - i > 0)
            sub(i), j -= a;
        }

      if (S[i] == 'A') {
        while (j - i >= a)
          sub(i), j -= a;

        while ((j - i) % 4) {
          for (int k = 0; k < a; k++)
            add(i - 1 + k);
          sub(i - 1), j += a;
        }

        for (int t = 0; t < (j - i) / 4; t++) {
          for (int k = 0; k < p - 1; k++)
            add(i + 2 * t + k);
          sub(i + 2 * t - 1), add(i + 2 * t + p - 1), sub(i + 2 * t);
        }
        j = i - 1 + (j - i) / 2, --i;
        while ((j - i) % a)
          add(j), ++j;
        while (j - i >= a)
          sub(j + 1), sub(i), j -= a;
      }
      while (s2)
        sub(m), s2 -= p;
    } else {
      for (i = m;; i++)
        if (S[i] == 'P')
          break;
      while (s1 % a)
        add(i), ++i, s1 += 2;

      for (i = m; S[i]; i++)
        if (S[i] == 'P') {
          j = i;
          while (S[j] == 'P')
            ++j;
          if (S[j] == 0)
            break;
          while ((j - i) % p)
            add(j), ++j;
          while (j - i > 0)
            sub(i), j -= p;
        }

      if (S[i] == 'P') {
        while (j - i >= p)
          sub(i), j -= p;

        while ((j - i) % 4) {
          for (int k = 0; k < p; k++)
            add(i - 1 + k);
          sub(i - 1), j += p;
        }

        for (int t = 0; t < (j - i) / 4; t++) {
          for (int k = 0; k < a - 1; k++)
            add(i + 2 * t + k);
          sub(i + 2 * t - 1), add(i + 2 * t + a - 1), sub(i + 2 * t);
        }
        j = i - 1 + (j - i) / 2, --i;
        while ((j - i) % p)
          add(j), ++j;
        while (j - i >= p)
          sub(j + 1), sub(i), j -= p;
      }
      while (s1)
        sub(m), s1 -= a;
    }
  }
  return true;
}

void sol() {
  scanf("%d%d%s%s", &a, &p, S, E);
  n = strlen(S), m = strlen(E);
  ans.clear();
  if (!Wrk())
    return puts("-1"), void();
  printf("%d\n", (int)ans.size());
  for (auto i : ans)
    cout << i.fi << ' ' << i.se << '\n';
}

int main() {
  scanf("%d", &T);
  while (T--)
    sol();
  return 0;
}