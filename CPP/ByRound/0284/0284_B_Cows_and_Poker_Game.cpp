/*
 * Problem URL : https://codeforces.com/problemset/problem/284/B
 * Submit Date : 2025-08-08
 */

#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
  int n;
  char ch[200001];
  scanf("%d%s", &n, ch);
  int allin = count(ch, ch + n, 'A');
  int in = count(ch, ch + n, 'I');
  int folded = count(ch, ch + n, 'F');
  if (in == 1) {
    printf("1\n");
  } else if (in == 0) {
    printf("%d\n", allin);
  } else {
    printf("0\n");
  }
  return 0;
}
