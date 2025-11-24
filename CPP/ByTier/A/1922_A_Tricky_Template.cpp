// Problem: CF 1922 A - Tricky Template
// https://codeforces.com/contest/1922/problem/A

/*
Problem: Determine if there exists a template t such that strings a and b match it,
         while string c does not match it.

Algorithms/Techniques:
- Brute-force approach checking each position of the strings.
- For each character position, we analyze:
  - If c[i] == a[i], then a[i] and c[i] are the same. So for b[i] to match template,
    b[i] must also equal a[i], or we can use an uppercase letter in template to enforce
    that b[i] != a[i].
  - Otherwise, check if we can choose template such that both a[i] and b[i]
    differ from c[i]. If there's no such case possible within one of the positions,
    return NO.

Time Complexity: O(n) per test case where n is the length of strings (up to 20).
Space Complexity: O(1) — only using fixed variables regardless of input size.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a, b, c;
    std::cin >> a >> b >> c;
    bool res(false); // result flag indicating if valid template exists
    for (long p = 0; !res && p < n; p++) {
      if (c[p] != a[p] && c[p] != b[p]) {
        // If c[p] differs from both a[p] and b[p], we can construct a template
        // that allows a and b to match it but not c.
        res = true;
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/