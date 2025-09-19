/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <iostream>
using namespace std;

int main() {
  long numGroups;
  scanf("%lu\n", &numGroups);
  long groups[5] = {0};
  long temp;
  do {
    scanf("%lu", &temp);
    ++groups[temp];
  } while (--numGroups);

  long total = groups[4];
  total += groups[3];
  groups[1] -= groups[3];
  total += groups[2] / 2 + groups[2] % 2;
  groups[1] -= 2 * (groups[2] % 2);
  if (groups[1] > 0) {
    total += groups[1] / 4 + (groups[1] % 4 > 0);
  }

  printf("%lu\n", total);
  return 0;
}
