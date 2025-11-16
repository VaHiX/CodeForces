// Problem: CF 733 A - Grasshopper And the String
// https://codeforces.com/contest/733/problem/A

/*
Purpose: 
  To find the minimum jump ability required for a grasshopper to traverse a string 
  by only landing on vowels. The jump ability is the maximum distance the grasshopper 
  can jump, and the goal is to reach the end of the string by jumping only on vowels.

Algorithms/Techniques:
  - Linear scan of the string
  - Track the maximum gap between vowels
  - Use a counter to track consecutive non-vowel characters

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) as we use only a constant amount of extra space

*/

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main() {
  int i, j, k;
  int len;
  int count = 1, max = 0; // 'count' tracks current gap, 'max' tracks maximum gap
  char s[200];
  scanf("%s", &s);
  strcat(s, "A"); // Append a vowel to handle the last segment
  len = strlen(s);
  for (i = 0; i < len; i++) {
    // If current character is a vowel
    if (s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' ||
        s[i] == 'U' || s[i] == 'Y') {
      // Update max if current gap is larger
      if (count > max) {
        max = count;
        count = 1; // Reset count after updating max
      } else
        count = 1; // Reset count
    } else
      count++; // Increment gap counter for non-vowel characters
  }
  cout << max;
  return 0;
}


// https://github.com/VaHiX/CodeForces/