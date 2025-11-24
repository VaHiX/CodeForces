// Problem: CF 1955 B - Progressive Square
// https://codeforces.com/contest/1955/problem/B

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, c, d;
    scanf("%ld %ld %ld", &n, &c, &d);
    std::vector<long> b(n * n);
    for (int p = 0; p < b.size(); p++) {
      scanf("%ld", &b[p]);
    }
    sort(b.begin(), b.end());
    std::vector<long> v;
    // Generate all possible values of a[i][j] - a[0][0] for a progressive square,
    // where a[i][j] = a[0][0] + i * c + j * d
    for (int row = 0; row < n; row++) {
      for (int col = 0; col < n; col++) {
        v.push_back(row * c + col * d);
      }
    }
    sort(v.begin(), v.end());
    bool ans(true);
    // For each element in the sorted array b, check if it matches the expected value
    // assuming a[0][0] is the smallest element of b (which it should be)
    for (int p = 0; ans && p < n * n; p++) {
      if (b[0] + v[p] != b[p]) {
        ans = false;
      }
    }
    puts(ans ? "YES" : "NO");
  }
}

// https://github.com/VaHiX/codeForces/