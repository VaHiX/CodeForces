#include <bits/stdc++.h>
char s[105];
int T, n;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    puts(s[1] == s[n] ? "No" : "Yes");
  }
  return 0;
}