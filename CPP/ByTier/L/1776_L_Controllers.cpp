// Problem: CF 1776 L - Controllers
// https://codeforces.com/contest/1776/problem/L

/*
 * Problem: Game with Controllers
 * 
 * Purpose:
 *   Given a sequence of + and - symbols, determine if it's possible to achieve a score of 0
 *   by choosing which button to press in each round. Each controller has two buttons with values a and b.
 *   Pressing button 'a' increases the score by 'a' for '+' and decreases it by 'a' for '-',
 *   similar for button 'b'.
 *
 * Algorithm:
 *   - Preprocess the number of '+' signs (f) and '-' signs.
 *   - For each query (controller), consider two cases:
 *     1. If a == b, we can only use one type of button, so check if f == n - f (equal number of + and -)
 *     2. If a != b, simulate the effect: Let x < y be the smaller and larger button.
 *        - We can make at most f buttons of type 'x' and (n-f) buttons of type 'y'.
 *        - For valid solution, there exists an assignment such that total score = 0.
 *        - If we select k buttons of value x, then (f - k) buttons of value y to balance,
 *          the condition is: k * (x - y) + (n - f) * y = 0 => k = (n - f) * y / (y - x)
 *        - Check if this k is a valid number of buttons (between 0 and f).
 *
 * Time Complexity:
 *   - Preprocessing: O(n)
 *   - Queries: O(q), where q is the number of controllers
 *   - Overall: O(n + q)
 *
 * Space Complexity:
 *   - O(n) for storing the input string
 *   - O(1) additional space
 */

#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;
typedef long long ll;
char num[200010]; // Stores the sequence of rounds (1-indexed)

int main() {
  int n;
  scanf("%d%s", &n, num + 1); // Read n and string s (1-indexed)
  
  int t, f = 0; // f counts number of '+' characters
  for (int i = 1; i <= n; i++)
    f += (num[i] == '+'); // Count '+' signs

  scanf("%d", &t); // Read number of controllers
  f = min(f, n - f); // Minimize the number of + or - to reduce work (since we're checking for balance)

  while (t--) {
    int x, y;
    scanf("%d%d", &x, &y); // Read button values of current controller
    
    if (x == y) {
      // If both buttons have same value, only way to win is if #+ = #- 
      puts(2 * f == n ? "YES" : "NO");
      continue;
    }
    
    if (x > y)
      swap(x, y); // Ensure x <= y for easier computation
    
    // Key check:
    // Let k be number of times we press smaller button x
    // Then we must press larger button y exactly (f - k) times such that:
    // k * x + (f - k) * y = 0  =>  k = (f * y) / (y - x)
    
    ll mid = 1ll * x * (n - 2 * f); // Compute numerator for k = (f * y) / (y - x)
    if (mid % (y - x) == 0 && mid / (y - x) <= f) // Check if k is integer and in [0, f]
      puts("YES");
    else
      puts("NO");
  }
}


// https://github.com/VaHiX/codeForces/