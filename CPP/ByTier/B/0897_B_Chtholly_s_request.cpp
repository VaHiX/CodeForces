// Problem: CF 897 B - Chtholly's request
// https://codeforces.com/contest/897/problem/B

/*
 * Problem: Compute the sum of the k smallest "zcy numbers" modulo p.
 * A zcy number is a palindrome with an even-length decimal representation.
 * 
 * Approach:
 * - Generate palindromes with even digit lengths.
 * - For each even length, we generate half of the palindrome and mirror it.
 * - The function `zcy` is used to generate the next zcy number based on input.
 * - Iteratively compute sum of first k zcy numbers and take modulo p.
 *
 * Time Complexity: O(k * d) where d is the average number of digits in zcy numbers.
 * Space Complexity: O(d) for storing digits of a number.
 */
#include <cstdio>
#include <vector>
typedef long long ll;

// Function to generate a zcy number based on input
// It constructs a palindrome by mirroring the digits
ll zcy(ll x) {
  std::vector<int> v;
  ll z(0);
  while (x > 0) {
    v.push_back(x % 10);  // Extract digits
    x /= 10;
  }
  for (ll p = v.size() - 1; p >= 0; p--) {
    z = 10 * z + v[p];  // Build first half of palindrome
  }
  for (ll p = 0; p < v.size(); p++) {
    z = 10 * z + v[p];  // Append mirrored half
  }
  return z;
}

int main() {
  ll k, M;
  scanf("%lld %lld", &k, &M);
  ll sum(0);
  for (ll p = 1; p <= k; p++) {
    sum += zcy(p);  // Add the p-th zcy number
    sum %= M;       // Keep sum within modulo
  }
  printf("%lld\n", sum);
  return 0;
}


// https://github.com/VaHiX/CodeForces/