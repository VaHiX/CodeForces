// Problem: CF 1056 A - Determine Line
// https://codeforces.com/contest/1056/problem/A

#include <cstdio>
#include <vector>
int main() {
  const int N = 107;
  long n;
  scanf("%ld", &n);
  std::vector<long> a(N, 0); // Array to count how many times each line appears
  for (long p = 0; p < n; p++) { // For each stop Arkady saw
    long k;
    scanf("%ld", &k);
    while (k--) { // For each tram line at this stop
      long x;
      scanf("%ld", &x);
      ++a[x]; // Increment count for this line
    }
  }
  for (long p = 0; p < N; p++) { // Check which lines appeared at all stops
    if (a[p] == n) { // If a line appears at every stop
      printf("%ld ", p); // Print that line
    }
  }
  puts("");
  return 0;
}

// https://github.com/VaHiX/codeForces/