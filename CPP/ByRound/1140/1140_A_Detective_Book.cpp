// Problem: CF 1140 A - Detective Book
// https://codeforces.com/contest/1140/problem/A

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1); // Array to store the explanation page for each mystery
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]); // Read the explanation page for mystery on page p
  }
  long page(1), mx(0), cnt(0); // page: current page being read, mx: max page reached so far, cnt: day counter
  while (page <= n) {
    ++cnt; // Increment day count
    do {
      mx = (mx > a[page]) ? mx : a[page]; // Update maximum page that needs to be reached
      ++page; // Move to next page
    } while (page <= mx); // Continue until all mysteries are resolved
  }
  printf("%ld\n", cnt); // Print total number of days
  return 0;
}

// https://github.com/VaHiX/codeForces/