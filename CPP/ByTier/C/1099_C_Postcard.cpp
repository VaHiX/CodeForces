// Problem: CF 1099 C - Postcard
// https://codeforces.com/contest/1099/problem/C

/*
Purpose: 
This code decrypts a postcard message that contains letters, snowflakes ('?'), and candy canes ('*').
The snowflake means the preceding letter can be repeated multiple times or removed.
The candy cane means the preceding letter can be removed or kept.
The goal is to determine if the given string can decode into a message of exactly k letters.

Algorithms/Techniques:
- Greedy string manipulation: 
  - First, we calculate the minimum possible length of the string (only letters).
  - Then, we process each character from left to right:
    - For '*', if the current string length is less than k, we insert the previous letter multiple times to reach exactly k.
    - For '?' or '*', if the current length exceeds k, we remove characters greedily.
- Backtracking is implicitly handled via greedy removal and insertion.

Time Complexity: O(n * k) where n is the length of the string and k is the target length.
Space Complexity: O(n) for storing the string.
*/

#include <iostream>
#include <string>

using namespace std;
int i, k, c;
string s;
int main() {
  cin >> s >> k;
  // Count initial number of letters (excluding ? and *)
  for (auto e : s)
    c += e != '?' && e != '*';
  
  // Process each character to adjust length to match k
  for (i = 0; i < s.size(); i++)
    if (s[i] == '*' && c < k)
      // If we have less letters and encounter '*', insert the previous letter (k - c) times
      s.insert(i, k - c, s[i - 1]), c = k;
    else if (s[i] == '?' || s[i] == '*') {
      // If we have too many letters, remove current character
      s.erase(i--, 1);
      if (c > k)
        s.erase(i--, 1), c--;
    }
  
  // Output result if length matches k, otherwise print "Impossible"
  cout << (k == c ? s : "Impossible");
}


// https://github.com/VaHiX/CodeForces/