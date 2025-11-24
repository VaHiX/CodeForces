// Problem: CF 1070 K - Video Posts
// https://codeforces.com/contest/1070/problem/K

#include <cstdio>
#include <vector>
// Problem: Split n videos into exactly k posts such that each post has same total duration
// Algorithm: Greedy approach - for each post, take videos from left until target sum is reached
// Time Complexity: O(n)
// Space Complexity: O(k)
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n), v(k);
  long long s(0);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    s += a[p];
  }
  if (s % k) { // If total sum is not divisible by k, impossible
    puts("No");
    return 0;
  }
  long target = s / k; // Each post must have this sum
  long idx(0);
  bool possible(true);
  for (long p = 0; p < k; p++) {
    long cnt(0), dur(0);
    while (idx < n && dur < target) { // Accumulate videos until target is reached
      dur += a[idx++];
      ++cnt;
    }
    if (dur != target) { // If we couldn't reach exactly target sum, impossible
      possible = false;
      break;
    }
    v[p] = cnt; // Store number of videos in this post
  }
  if (possible) {
    puts("Yes");
    for (long p = 0; p < k; p++) {
      printf("%ld ", v[p]);
    }
    puts("");
  } else {
    puts("No");
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/