/*
 * Problem URL : https://codeforces.com/problemset/problem/95/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
char s[110][110], w[110], ch;
int ok[110];
int main() {
  int n, i, j, k;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", s[i]);
  }
  scanf("%s %c", w, &ch);
  for (i = 0; i < n; i++) {
    int L = strlen(s[i]);
    for (j = 0; w[j]; j++) {
      for (k = 0; k < L; k++) {
        if (tolower(w[j + k]) != tolower(s[i][k]))
          break;
      }
      if (k < L)
        continue;
      for (k = 0; k < L; k++)
        ok[j + k] = 1;
    }
  }
  for (i = 0; w[i]; i++) {
    if (!ok[i])
      continue;
    if (islower(w[i]))
      w[i] = (w[i] == tolower(ch)) ? 'a' + (tolower(ch) == 'a') : tolower(ch);
    else
      w[i] = (w[i] == toupper(ch)) ? 'A' + (toupper(ch) == 'A') : toupper(ch);
  }
  puts(w);
  return 0;
}