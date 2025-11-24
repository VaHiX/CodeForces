// Problem: CF 2171 A - Shizuku Hoshikawa and Farm Legs
// https://codeforces.com/contest/2171/problem/A

/*
 * Problem: Shizuku Hoshikawa and Farm Legs
 * 
 * Purpose: Given the total number of legs 'n', determine how many different combinations of chickens (2 legs) 
 *          and cows (4 legs) can produce exactly 'n' legs.
 * 
 * Algorithm/Techniques:
 *   - Mathematical analysis: 
 *     Let c = number of chickens, w = number of cows.
 *     Then, 2*c + 4*w = n => c = (n - 4*w)/2
 *     For valid integer solutions, (n - 4*w) must be even and non-negative.
 *     Since n is even (as shown by the condition), n-4*w is even if w is integer.
 *     Also, c >= 0 implies w <= n/4.
 *     So, valid values of w range from 0 to n/4 (inclusive).
 *     Thus, the count of valid configurations is floor(n/4) + 1.
 * 
 * Time Complexity: O(1) - constant time per test case
 * Space Complexity: O(1) - only using a fixed amount of extra space
 */

#include <iostream>

using namespace std;
int main() {
  int t;
  int n;
  cin >> t;
  for (int i = 0; i < t; i++) {
    cin >> n;
    if (n % 2 == 1) // If n is odd, no valid combination exists (since both chicken and cow have even legs)
      cout << "0\n";
    else
      cout << n / 4 + 1 << "\n"; // Number of valid combinations is floor(n/4) + 1
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/