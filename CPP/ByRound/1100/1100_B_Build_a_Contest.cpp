// Problem: CF 1100 B - Build a Contest
// https://codeforces.com/contest/1100/problem/B

#include <cstdio>
#include <vector>
// Problem: Determine after which problems Arkady holds a round
// Algorithm: Use a frequency counter for difficulties. When we have all n difficulties,
//            we hold a round and reset the counter. 
// Time Complexity: O(m), where m is the number of problems created
// Space Complexity: O(n), for the frequency array
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  long cnt(0);
  // a[x] keeps track of how many problems of difficulty x we have in our pool
  std::vector<long> a(n + 1, 0);
  for (long p = 0; p < m; p++) {
    long x;
    scanf("%ld", &x);
    // If this is the first problem of difficulty x, increment the count of distinct difficulties
    if (a[x] == 0) {
      ++cnt;
    }
    // Add the problem to the pool
    ++a[x];
    // If we have all n difficulties, hold a round
    if (cnt == n) {
      cnt = 0;
      // Remove all problems used in the round
      for (long u = 1; u <= n; u++) {
        --a[u];
        // Update the count of distinct difficulties
        cnt += (a[u] > 0);
      }
      printf("1");
    } else {
      printf("0");
    }
  }
  puts("");
  return 0;
}

// https://github.com/VaHiX/CodeForces/