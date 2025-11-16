// Problem: CF 1144 C - Two Shuffled Sequences
// https://codeforces.com/contest/1144/problem/C

/*
Algorithm: Two Shuffled Sequences
Approach:
1. Sort the input array.
2. Check if any element appears more than twice - if so, it's impossible to split into strictly increasing and decreasing sequences.
3. If valid, split the sorted array into two parts:
   - First part (b): elements that appear once, forming strictly increasing sequence.
   - Second part (d): elements that appear twice, forming strictly decreasing sequence.
4. Output the split sequences.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the vectors
*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());
  bool possible(true);
  for (long p = 2; p < a.size(); p++) {
    if (a[p - 2] == a[p]) {
      possible = false;
      break;
    }
  }
  if (possible) {
    std::vector<long> b, d;
    b.push_back(a[0]);
    for (long p = 1; p < n; p++) {
      if (a[p - 1] != a[p]) {
        b.push_back(a[p]);
      } else {
        d.push_back(a[p]);
      }
    }
    puts("YES");
    printf("%ld\n", b.size());
    for (long p = 0; p < b.size(); p++) {
      printf("%ld ", b[p]);
    };
    puts("");
    printf("%ld\n", d.size());
    for (long p = d.size() - 1; p >= 0; p--) {
      printf("%ld ", d[p]);
    };
    puts("");
  } else {
    puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/