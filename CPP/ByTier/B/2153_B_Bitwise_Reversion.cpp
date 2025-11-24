// Problem: CF 2153 B - Bitwise Reversion
// https://codeforces.com/contest/2153/problem/B

/*
B. Bitwise Reversion
Algorithms/Techniques: Bitwise operations, bitwise AND properties

Time Complexity: O(1) - Since we process at most 40 bits for each number (up to 10^9)
Space Complexity: O(1) - Fixed-size array of size 100 for digit counting

The problem checks whether there exist three non-negative integers a, b, c such that:
a & b = x
b & c = y  
a & c = z

Key insight:
If we consider each bit position independently, for bits at position i:
- Let a_i, b_i, c_i be the ith bits of a, b, c respectively.
- Then a_i & b_i = x_i, b_i & c_i = y_i, a_i & c_i = z_i
- This system is solvable if and only if (x & y) == 0, (y & z) == 0, (x & z) == 0.
But since we compute bits in a different way here for validation,
the logic checks: for each bit position k, count how many of the three pairs (a,b), (b,c), (a,c) have 1 in that bit.
If any bit position has exactly two 1s among all three pairs, then it's impossible. 
*/

#include <algorithm>
#include <iostream>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;

namespace solve {
const int N = 100;
int a, b, c;
int digits[N]; // Array to count bits for each position across all three numbers

void checkDigits(int x) {
  int cnt = 0;
  while (x) { // Extract each bit from number x and increment corresponding counter
    digits[++cnt] += x % 2; // Add 1 if this bit is set in x
    x /= 2; // Move to next bit
  }
}

void solve() {
  fill(digits + 1, digits + 1 + 40, 0); // Initialize the bits count array for current test case
  cin >> a >> b >> c;
  checkDigits(a);
  checkDigits(b);
  checkDigits(c);
  for (int i = 0; i < 40; i++) {
    if (digits[i] == 2) { // If exactly two numbers have bit 1 at this position, impossible
      cout << "NO" << '\n';
      return;
    }
  }
  cout << "YES" << '\n'; // Valid configuration exists
}

} // namespace solve

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve::solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/