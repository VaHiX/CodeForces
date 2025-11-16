// Problem: CF 798 A - Mike and palindrome
// https://codeforces.com/contest/798/problem/A

/*
Purpose: Determine if exactly one character in a string can be changed to make it a palindrome.
Algorithm: 
- Compare characters from both ends moving towards the center.
- Count mismatches between symmetric positions.
- For even-length strings, exactly one mismatch allows a solution.
- For odd-length strings, at most one mismatch allows a solution.
Time Complexity: O(n), where n is the length of the string.
Space Complexity: O(1), only using a constant amount of extra space.
*/

#include <iostream>
#include <string>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n;
  string s;
  cin >> s;
  n = s.length();
  
  if (n % 2 == 0) {
    // For even-length strings, check all pairs from outside to inside
    j = n - 1;  // Right pointer
    k = 0;      // Mismatch counter
    for (i = 0; i < n / 2; i++) {
      if (s[i] != s[j])  // If characters don't match
        k++;             // Increment mismatch counter
      j--;               // Move right pointer left
    }
    if (k == 1)          // Exactly one mismatch?
      cout << "YES";
    else
      cout << "NO";
  } else {
    // For odd-length strings, same logic but we ignore the middle character
    j = n - 1;
    k = 0;
    for (i = 0; i < n / 2; i++, j--) {  // Loop until middle
      if (s[i] != s[j])
        k++;
    }
    if (k <= 1)  // At most one mismatch allowed
      cout << "YES";
    else
      cout << "NO";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/