// Problem: CF 1268 A - Long Beautiful Integer
// https://codeforces.com/contest/1268/problem/A

/*
 * Problem: A. Long Beautiful Integer
 * Algorithm/Technique: Simulation with pattern matching and incrementing
 *
 * Task:
 * Given an integer x of n digits, and a positive integer k < n,
 * we need to find the smallest beautiful integer y such that y >= x.
 * A beautiful integer has a repeating pattern every k digits.
 *
 * Time Complexity: O(n) - single pass through string with possible inner loop
 * Space Complexity: O(n) - for storing the string of digits
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  
  int n, m; // n is number of digits in input, m will be used for pattern length
  cin >> n >> m;
  
  string s;
  cin >> s;
  
  int ls = s.size(); // Length of the input string
  
  // Loop from index m to end of string to look for where we need to increment
  for (int i = m; i < ls; i++) {
    // If current digit is greater than its corresponding digit in the repeating pattern
    if (s[i] > s[i % m]) {
      int j = 1;
      // Handle carry propagation when incrementing
      while (s[m - j] == '9') {
        s[m - j] = '0';
        j++;
      }
      ++s[m - j]; // Increment the appropriate digit
      break; // Break after making adjustment
    }
    
    // If current digit is smaller than its corresponding digit in pattern, no need to adjust further
    if (s[i] < s[i % m])
      break;
  }
  
  // Output number of digits in result (always n)
  cout << n << '\n';
  
  // Print the beautiful integer using modulo arithmetic to cycle through pattern
  for (int i = 0; i < n; i++)
    cout << s[i % m];
  cout << '\n';
  
  return 0;
}


// https://github.com/VaHiX/codeForces/