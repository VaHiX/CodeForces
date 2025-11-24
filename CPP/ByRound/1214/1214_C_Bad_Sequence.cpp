// Problem: CF 1214 C - Bad Sequence
// https://codeforces.com/contest/1214/problem/C

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long cnt(0);
  for (long p = 0; p < n; p++) {
    cnt += (s[p] == '(') - (s[p] == ')'); // Increment for '(', decrement for ')'
    if (cnt < -1) { // If at any point we have more ')' than '(', break
      break;
    }
  }
  if (cnt != 0) { // If the total count is not zero, sequence is invalid
    cnt = -2; // Mark as invalid
  }
  std::cout << (cnt ? "No" : "Yes") << std::endl;
  return 0;
}

// https://github.com/VaHiX/codeForces/