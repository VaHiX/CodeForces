/*
 * Problem URL : https://codeforces.com/problemset/problem/421/B
 * Submit Date : 2025-08-13
 */

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
char num[100005];

bool judge(char c) {
  if (c == 'A' || c == 'H' || c == 'I' || c == 'M' || c == 'O' || c == 'T' ||
      c == 'U' || c == 'V' || c == 'W' || c == 'X' || c == 'Y')
    return true;
  return false;
}
int main() {
  int flag = 1;
  scanf("%s", num);
  int n = strlen(num);

  for (int i = 0; i < n; i++) {
    if (num[i] == num[n - i - 1] && judge(num[i])) {
      // flag=1;
    } else
      flag = 0;
  }
  if (flag)
    printf("YES\n");
  else
    printf("NO\n");
  return 0;
}
