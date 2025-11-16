// Problem: CF 1199 A - City Day
// https://codeforces.com/contest/1199/problem/A

/*
Problem: City Day
Algorithm: Brute Force
Time Complexity: O(n * (x + y))
Space Complexity: O(n)

For years, the Day of city N was held in the most rainy day of summer. New mayor decided to break this tradition and select a 
not-so-rainy day for the celebration. The mayor knows the weather forecast for the n days of summer. On the i-th day, a_i millimeters of rain will fall. All values a_i are distinct.
The mayor knows that citizens will watch the weather x days before the celebration and y days after. Because of that, he says that a day d is 
not-so-rainy if a_d is smaller than rain amounts at each of x days before day d and and each of y days after day d. In other words, a_d < a_j should hold for all d - x <= j < d and d < j <= d + y. Citizens only watch the weather during summer, so we only consider such j that 1 <= j <= n.
Help mayor find the earliest not-so-rainy day of summer.
*/

#include <cstdio>
#include <vector>
int main() {
  long n, x, y;
  scanf("%ld %ld %ld", &n, &x, &y);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long ans(0);
  for (long p = 0; p < n; p++) {
    long least(true); // indicates if current day is not-so-rainy
    for (long u = 1; least && (u <= x); u++) {
      if (p - u >= 0 && a[p - u] < a[p]) { // check previous x days
        least = false;
      }
    }
    for (long u = 1; least && (u <= y); u++) {
      if (p + u < n && a[p + u] < a[p]) { // check next y days
        least = false;
      }
    }
    if (least) {
      ans = p + 1; // 1-indexed answer
      break;
    }
  }
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/