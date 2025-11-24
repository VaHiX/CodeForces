// Problem: CF 466 C - Number of Ways
// https://codeforces.com/contest/466/problem/C

/*
 * Problem: Number of Ways to Split Array into Three Parts with Equal Sum
 *
 * Algorithm:
 * 1. Compute total sum of the array.
 * 2. If sum is not divisible by 3, return 0.
 * 3. Let each part sum to third = sum / 3.
 * 4. Use cumulative sums from left to count how many times we reach 'third' sum so far.
 * 5. Traverse from right to count valid splits where right part equals 'third'.
 * 6. For each valid right split, add the number of valid left splits before it.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <cstdio>
#include <vector>
int main() {
  long long n;
  scanf("%lld", &n);
  std::vector<long long> array(n, 0);
  long long sum(0);
  for (long long p = 0; p < n; p++) {
    scanf("%lld", &array[p]);
    sum += array[p];
  }
  if (sum % 3 != 0) {
    puts("0");
    return 0;
  }
  long long third = sum / 3;
  std::vector<long long> cumLeftThird(n, 0);
  long long cumsum(0), thirdCount(0);
  for (long p = 0; p < n; p++) {
    cumsum += array[p];
    if (cumsum == third) {
      ++thirdCount;
    }
    cumLeftThird[p] = thirdCount;
  }
  cumsum = 0;
  long long total = 0;
  for (long p = n - 1; p >= 2; p--) {
    cumsum += array[p];
    if (cumsum == third) {
      total += cumLeftThird[p - 2]; // Add valid left splits before this right part
    }
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/