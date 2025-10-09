/*
 * Problem URL : https://codeforces.com/problemset/problem/1342/A
 * Submit Date : 2025-08-19
 */

#import <iostream>
long long t, a, b, x, y;
main() {
  for (scanf("%lld", &t); t--;
       printf("%lld\n", b > 2 * a ? (x + y) * a : (y - x) * a + x * b)) {
    std::cin >> x >> y >> a >> b;
    if (x > y)
      std::swap(x, y);
  }
}