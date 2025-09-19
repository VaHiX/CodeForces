/*
 * Problem URL : https://codeforces.com/contest/608/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/608/problem/A
 * Submit Date : 2025-09-02
 */

#include <cstdio>

int main() {

  int n, s;
  scanf("%d %d\n", &n, &s);

  int res(s);
  while (n--) {
    int floor, time;
    scanf("%d %d\n", &floor, &time);
    res = (res > (floor + time)) ? res : (floor + time);
  }

  printf("%d\n", res);

  return 0;
}
