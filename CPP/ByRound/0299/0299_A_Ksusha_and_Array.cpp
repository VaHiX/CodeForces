/*
 * Problem URL : https://codeforces.com/problemset/problem/299/A
 * Submit Date : 2025-08-16
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/299/A
 * Submit Date : 2025-08-16
 */

#include <cstdio>

int main() {

  long n(0);
  scanf("%ld\n", &n);
  long *array = new long[n];
  long currentMin(1e9);
  for (long k = 0; k < n; k++) {
    scanf("%ld", array + k);
    if (array[k] < currentMin) {
      currentMin = array[k];
    }
  }
  for (long k = 0; k < n; k++) {
    if (array[k] % currentMin != 0) {
      currentMin = -1;
      break;
    }
  }
  printf("%ld\n", currentMin);
  return 0;
}
