/*
 * Problem URL : https://codeforces.com/problemset/problem/621/A
 * Submit Date : 2025-08-16
 */

#include <iostream>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  long long sum = 0, mini = (1LL << 30);
  while (n--) {
    int a;
    scanf("%d", &a);
    sum += a;
    if (a % 2 && a < mini)
      mini = a;
  }
  if (sum % 2)
    sum -= mini;
  printf("%I64d", sum);
}
