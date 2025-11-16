// Problem: CF 876 B - Divisiblity of Differences
// https://codeforces.com/contest/876/problem/B

/*
Algorithm: Divisibility of Differences
Purpose: Given a multiset of integers, select exactly k integers such that the difference between any two of them is divisible by m.
Techniques: 
- Group numbers by their remainder when divided by m.
- For each group, if it has at least k elements, output the first k elements.
Time Complexity: O(n + m)
Space Complexity: O(n)

The key insight is that if all selected numbers have the same remainder when divided by m, 
then their pairwise differences will be multiples of m.
*/

#include <cstdio>
#include <vector>
int main() {
  long n, k, m;
  scanf("%ld %ld %ld", &n, &k, &m);
  std::vector<std::vector<long>> v(m);  // Create buckets for remainders 0 to m-1
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    v[a % m].push_back(a);  // Place each number in the bucket corresponding to its remainder
  }
  bool possible(false);
  for (long p = 0; p < m; p++) {
    if (v[p].size() < k) {
      continue;  // Skip buckets with fewer than k elements
    }
    possible = true;
    puts("Yes");
    for (long u = 0; u < k; u++) {
      printf("%ld ", v[p][u]);  // Output first k elements from the valid bucket
    }
    puts("");
    break;
  }
  if (!possible) {
    puts("No");  // No valid group found
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/