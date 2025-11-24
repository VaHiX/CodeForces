// Problem: CF 908 A - New Year and Counting Cards
// https://codeforces.com/contest/908/problem/A

/*
 * Problem: New Year and Counting Cards
 * 
 * Algorithm/Technique: 
 *   - Iterate through each character in the string
 *   - For each character:
 *     - If it's a vowel ('a', 'e', 'i', 'o', 'u'), we must check the other side
 *     - If it's an odd digit ('1', '3', '5', '7', '9'), we must check the other side
 *   - Count such characters that require flipping
 * 
 * Time Complexity: O(n) where n is the length of the input string
 * Space Complexity: O(1) - only using a few variables regardless of input size
 */

#include <cstdio>
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 1010
#define inf 10000000
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  string s;
  cin >> s;
  int cnt = 0;  // Counter for cards that need to be flipped
  int l = s.length();
  for (i = 0; i < l; i++) {
    // If it's a vowel, we must flip the card to verify the rule
    if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
      cnt++;
    // If it's an odd digit, we must flip the card to verify the rule
    else if (s[i] == '1' || s[i] == '3' || s[i] == '5' || s[i] == '7' ||
             s[i] == '9')
      cnt++;
  }
  printf("%d", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/