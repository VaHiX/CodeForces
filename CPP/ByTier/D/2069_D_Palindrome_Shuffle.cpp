// Problem: CF 2069 D - Palindrome Shuffle
// https://codeforces.com/contest/2069/problem/D

/*
Purpose: This code solves the problem of finding the minimum length of a substring that needs to be shuffled to make a given string into a palindrome.
The algorithm:
1. First, we find the longest prefix/suffix which are already matched from both ends.
2. Then, we process the middle part from left to right to determine the minimal extension needed to make it symmetrical for the first half.
3. Similarly, we process from right to left to determine the other side's minimal extension.
4. The minimum of these two extensions gives the answer.

Time Complexity: O(n), where n is the length of the string, since we do a constant number of passes through the string.
Space Complexity: O(1), as we use only a fixed-size array of size 200 for character counting, regardless of input size.
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

#define ll long long
using namespace std;

int t, cnt[200], l, r, ans, tot[200], x;
char s[300000];

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    l = 1, r = n;
    // Initialize character count arrays
    for (int i = 'a'; i <= 'z'; i++)
      tot[i] = cnt[i] = 0;
    
    // Move l and r towards each other while characters match
    while (l < r && s[l] == s[r])
      l++, r--;
    
    // Count characters in the remaining middle part
    for (int i = l; i <= r; i++)
      cnt[s[i]]++;
    
    x = l;
    // Traverse from left to right to find the minimal right boundary
    for (int i = l; i <= r; i++) {
      tot[s[i]]++;
      if (i > n / 2) {
        if (s[i] != s[n - i + 1])
          break;
      } else {
        if (tot[s[i]] * 2 > cnt[s[i]])
          break;
      }
      x = i + 1;
    }
    
    ans = r - x + 1; // Initial answer calculated from left to right
    x = r;
    
    // Reset the total count array
    for (int i = 'a'; i <= 'z'; i++)
      tot[i] = 0;
    
    // Traverse from right to left to find the minimal left boundary
    for (int i = r; i >= l; i--) {
      tot[s[i]]++;
      if (i <= n / 2) {
        if (s[i] != s[n - i + 1])
          break;
      } else {
        if (tot[s[i]] * 2 > cnt[s[i]])
          break;
      }
      x = i - 1;
    }
    
    ans = min(ans, x - l + 1); // Final answer: minimum of both directions
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/