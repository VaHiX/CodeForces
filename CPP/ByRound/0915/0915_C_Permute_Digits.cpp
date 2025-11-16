// Problem: CF 915 C - Permute Digits
// https://codeforces.com/contest/915/problem/C

#include <iostream>
#include <string>

typedef long long ll;
int main() {
  std::string sa;
  std::cin >> sa;
  ll t;
  std::cin >> t;
  ll cnt[10] = {0};
  for (int p = 0; p < sa.size(); p++) {
    ++cnt[sa[p] - '0']; // Count frequency of each digit in 'a'
  }
  ll ans(0);
  for (int p = 1; p <= sa.size(); p++) {
    ll res(ans);
    for (int d = 9; d >= 0; d--) { // Try digits from 9 down to 0
      if (cnt[d] <= 0) {
        continue; // Skip if digit not available
      }
      ll cur = res * 10 + d; // Form candidate number with current digit
      --cnt[d]; // Use up one instance of the digit
      for (int k = 0; k <= 9; k++) {
        for (int tr = 0; tr < cnt[k]; tr++) {
          cur = cur * 10 + k; // Append remaining digits in ascending order
        }
      }
      if (cur <= t) { // Check validity
        ans = ans * 10 * 1LL + d; // Update final answer
        break;
      }
      ++cnt[d]; // Backtrack: restore the digit count
    }
  }
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/