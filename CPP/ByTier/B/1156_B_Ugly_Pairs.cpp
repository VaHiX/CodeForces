// Problem: CF 1156 B - Ugly Pairs
// https://codeforces.com/contest/1156/problem/B

/*
Algorithm/Technique:
The approach separates the characters of the string into two groups based on their ASCII value parity (even/odd). 
Then, each group is sorted individually. The algorithm checks if placing one group before the other avoids adjacent 
alphabetical characters by comparing the last character of the first group with the first character of the second group, 
and vice versa. If neither arrangement works, it outputs "No answer".

Time Complexity: O(n log n) where n is the length of the string due to sorting operations.
Space Complexity: O(n) for storing the two separated strings.

*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    string s1, s2;
    // Separate characters based on whether their ASCII value is odd or even
    for (int i = 0; i < s.size(); i++)
      if (s[i] & 1)  // Check if ASCII value is odd
        s1 += s[i];
      else
        s2 += s[i];
    
    // Sort both groups
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    
    // Check if placing s1 followed by s2 avoids ugly pairs
    if (abs(s2[0] - s1[s1.size() - 1]) != 1)
      cout << s1 + s2 << endl;
    // Check if placing s2 followed by s1 avoids ugly pairs
    else if (abs(s2[s2.size() - 1] - s1[0]) != 1)
      cout << s2 + s1 << endl;
    else
      cout << "No answer" << endl;
  }
}


// https://github.com/VaHiX/CodeForces/