// Problem: CF 1955 F - Unfair Game
// https://codeforces.com/contest/1955/problem/F

/*
Code Purpose:
This program determines the maximum number of times Bob can win in a game where Alice and Bob play with a sequence of integers (0-4), and the winner is determined by whether the XOR of the sequence is zero or not. Eve removes numbers optimally to maximize Bob's wins. The key insight is that the XOR of the entire sequence can be analyzed in terms of parity of counts of each number (0,1,2,3,4), with special handling for odd counts of 1,2,3 to determine how many times the XOR becomes zero (Bob wins).

Algorithms/Techniques:
- Greedy counting of parity
- XOR properties analysis: 
  - XOR of all elements is 0 if and only if the overall parity is even for each number when considered independently
  - For numbers 1,2,3, we track how many are odd in count. If 1,2,3 all have odd counts, then one more step of removal can ensure Bob's win by making them even overall.

Time Complexity: O(1) - constant time per test case
Space Complexity: O(1) - constant space usage
*/

#include <iostream>

using namespace std;
#define ll long long
#define IOS cin.tie(0)->sync_with_stdio(0)
void solve() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  // Count how many pairs of each number we can form (each pair contributes 0 to XOR)
  int ans = a / 2 + b / 2 + c / 2 + d / 2;
  // If all of 1,2,3 have odd counts, one more removal (which can be done optimally) leads to a win for Bob
  // This condition checks that 1,2,3 all have odd numbers, and so removing one of them makes XOR = 0, hence Bob wins
  if (a % 2 && b % 2 && c % 2)
    ans++;
  cout << ans << '\n';
}
int main() {
  IOS;
  int tt;
  cin >> tt;
  while (tt--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/