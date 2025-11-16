// Problem: CF 1084 C - The Fair Nut and String
// https://codeforces.com/contest/1084/problem/C

/*
C. The Fair Nut and String
Algorithm: Dynamic Programming
Time Complexity: O(n)
Space Complexity: O(1)

The problem asks to count the number of strictly increasing sequences of 'a' characters,
where between any two consecutive 'a's there must be at least one 'b'.

The approach:
- We use two variables:
  - r: total number of valid sequences ending at current position
  - t: number of valid sequences that can be extended by the next 'a'
- When we see an 'a':
  - We add (t + 1) to r (t sequences that can be extended, plus one new sequence starting here)
  - We increment t to account for a new valid prefix ending in this 'a'
- When we see a 'b':
  - We update t to the current value of r (the number of valid sequences so far)

This solution processes each character once, giving linear time complexity.
*/

#include <iostream>
#include <string>

typedef long long ll;
int main() {
  const ll MOD = 1e9 + 7;
  std::ios_base::sync_with_stdio(false);
  std::string s;
  std::cin >> s;
  ll r(0), t(0);  // r: total sequences, t: sequences that can be extended
  for (char c : s) {
    if (c == 'a') {
      r += (t + 1);  // Add the new sequence starting at this 'a' and all prefixes extending to here
      r %= MOD;
    } else if (c == 'b') {
      t = r;  // Update t with current number of valid sequences that can be extended
    }
  }
  std::cout << r << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/