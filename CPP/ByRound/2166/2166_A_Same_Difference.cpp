// Problem: CF 2166 A - Same Difference
// https://codeforces.com/contest/2166/problem/A

/*
Code Purpose:
This program calculates the minimum number of operations needed to make all characters in a string the same.
Each operation allows changing a character at position i to the character at position i+1.
The strategy is to count how many characters from the start match the last character,
then the number of operations is the total length minus this count.

Algorithms/Techniques:
- Greedy approach: we try to convert all characters to the last character in the string
- Single pass through the string to count matching characters

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables for counting and iteration
*/

#include <iostream>
#include <string>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = 1; // Start with 1 since we're counting from the last character
    for (int i = 0; i < n - 1; i++) {
      if (s[i] == s[n - 1]) { // If current character matches the last one
        cnt++; // Increment the count
      }
    }
    cout << n - cnt << endl; // Minimum operations = total length - matched characters
  }
}


// https://github.com/VaHiX/CodeForces/