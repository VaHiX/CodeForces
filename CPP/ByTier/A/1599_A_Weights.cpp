// Problem: CF 1599 A - Weights
// https://codeforces.com/contest/1599/problem/A

/*
Algorithm: Greedy with Sorting
Approach:
1. Sort the weights in ascending order.
2. Count the number of transitions in the string S (i.e., where 'L' changes to 'R' or vice versa).
3. Based on the transitions and the first character of S, determine how to assign weights to maintain the required balance.
4. Greedily assign the largest available weights to satisfy the string constraints.

Time Complexity: O(N log N) due to sorting
Space Complexity: O(N) for storing the weights array
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  int hat[n];
  for (int i = 0; i < n;)
    cin >> hat[i++];
  sort(hat, hat + n); // Sort weights in ascending order
  string s;
  cin >> s;
  int change = 0;
  for (int i = 1; i < n; i++)
    change += (s[i] != s[i - 1]); // Count transitions in string S
  int l = n - 2 - change; // Pointer for left side weights
  int r = n - change;     // Pointer for right side weights
  cout << hat[r - 1] << " " << s[0] << "\n"; // Output first weight based on first character of S
  bool right = s[0] == 'R';
  bool left = right; // Initialize left based on first character
  for (int i = 1; i < n; i++) {
    if (s[i - 1] == s[i]) {
      // If consecutive characters are same, toggle direction and use l pointer
      right ^= 1;
      if (right)
        cout << hat[l--] << " R\n";
      else
        cout << hat[l--] << " L\n";
    } else {
      // If characters are different, toggle direction and use r pointer
      left ^= 1;
      if (left)
        cout << hat[r++] << " R\n";
      else
        cout << hat[r++] << " L\n";
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/