/*
 * Problem URL : https://codeforces.com/contest/418/problem/A
 * Submit Date : 2025-09-06
 */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory.h>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  if (k > (n - 1) / 2) {
    printf("%d\n", -1);
  } else {
    printf("%d\n", n * k);
    for (int i = 1; i <= n; i++)
      for (int j = 0; j < k; j++)
        printf("%d %d\n", i, (i + j) % n + 1);
  }
  return 0;
}
