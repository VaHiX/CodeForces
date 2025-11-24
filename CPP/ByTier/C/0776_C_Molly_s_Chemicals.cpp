// Problem: CF 776 C - Molly's Chemicals
// https://codeforces.com/contest/776/problem/C

/*
C. Molly's Chemicals
time limit per test
2.5 seconds
memory limit per test
512 megabytes
input
standard input
output
standard output
Molly Hooper has n different kinds of chemicals arranged in a line. Each of the chemicals has an affection value, The i-th of them has affection value a_i.
Molly wants Sherlock to fall in love with her. She intends to do this by mixing a contiguous segment of chemicals together to make a love potion with total affection value as a non-negative integer power of k. Total affection value of a continuous segment of chemicals is the sum of affection values of each chemical in that segment.
Help her to do so in finding the total number of such segments.

Algorithm: 
- Uses prefix sums and hash map to count subarrays with sums equal to powers of k.
- For each power of k up to a reasonable limit, compute how many subarrays have sum equal to that power.
- Time complexity: O(n * log(maxTarget)) where maxTarget is 51 (since we iterate up to k^50).
- Space complexity: O(n) for prefix sums and hash map.

Input:
The first line of input contains two integers, n and k, the number of chemicals and the number, such that the total affection value is a non-negative power of this number k. (1 ≤ n ≤ 10^5, 1 ≤ |k| ≤ 10).
Next line contains n integers a_1, a_2, ..., a_n ( - 10^9 ≤ a_i ≤ 10^9) — affection values of chemicals.

Output:
Output a single integer — the number of valid segments.
*/
#include <stdint.h>
#include <cstdio>
#include <map>
#include <vector>

int64_t countSums(const std::vector<int64_t> &cs, int64_t target) {
  int64_t count(0);
  std::map<int64_t, int64_t> m;
  for (long p = cs.size() - 1; p >= 0; p--) {
    int64_t seek = cs[p] + target; // Look for prefix sum that would give us 'target'
    if (m.count(seek) > 0) {       // If such a prefix exists
      count += m[seek];            // Add number of times we've seen it
    }
    if (m.count(cs[p]) <= 0) {     // Initialize if not present
      m[cs[p]] = 0;
    }
    ++m[cs[p]];                    // Increment count of current prefix sum
  }
  return count;
}

int main() {
  const int64_t maxTarget = 51;
  int64_t n, k;
  scanf("%lld %lld\n", &n, &k);
  std::vector<int64_t> a(n);
  for (int64_t p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  std::vector<int64_t> cs(n + 1, 0); // Prefix sum array
  for (long p = 1; p <= n; p++) {
    cs[p] = cs[p - 1] + a[p - 1]; // Build prefix sums
  }
  double kp(1);
  int64_t total(0);
  for (int64_t p = 1; p < maxTarget; p++) {
    total += countSums(cs, kp);  // Count subarrays with sum equal to current power of k
    kp *= k;                     // Update next power
    if (kp == 1) {               // Avoid infinite loop when k=1
      break;
    }
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/