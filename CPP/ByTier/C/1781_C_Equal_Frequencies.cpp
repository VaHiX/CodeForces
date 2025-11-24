// Problem: CF 1781 C - Equal Frequencies
// https://codeforces.com/contest/1781/problem/C

/*
 * Problem: Equal Frequencies
 * Purpose: Given a string s of lowercase English letters, find a balanced string t 
 *          of the same length that differs from s in as few positions as possible.
 *          A balanced string is one where all characters that appear have the same frequency.
 *          
 * Algorithm:
 *   - Count the frequency of each character in s.
 *   - Try different numbers of unique characters (from 1 to 26) that could form a balanced string.
 *   - For each possible number of unique characters (k), calculate how many changes are needed:
 *     if the total length n is divisible by k, then each character must appear exactly n/k times.
 *   - Choose the k that minimizes the number of operations.
 *   - Construct the balanced string t with exactly k unique characters, each appearing n/k times.
 *   - Replace characters in s with those from t such that number of differences is minimal.
 *   
 * Time Complexity: O(n * log(n)) per test case, due to sorting and iterating through possible k values.
 * Space Complexity: O(n) for storing the input string and auxiliary arrays.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 1e6 + 10;
int t[26], T, n, len, p[26], ans, w;
char s[N], q[N];

// Comparator to sort characters by frequency in descending order
bool cmp(int x, int y) { return t[x] > t[y]; }

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s);
    // Count frequency of each character
    for (int i = 0; i < n; i++)
      t[s[i] - 'a']++;
    
    // Initialize permutation array to store indices 0-25
    for (int i = 0; i < 26; i++)
      p[i] = i;
    
    // Sort character indices by frequency in descending order
    sort(p, p + 26, cmp);
    
    // Initialize answer to large value
    ans = 99999999;
    
    // Try all possible numbers of unique characters from 1 to 26
    for (int i = 1; i <= 26; i++) {
      // If n is not divisible by i, then cannot evenly distribute n characters among i types
      if (n % i)
        continue;
      
      int x = n / i, s = 0;
      // Compute number of operations needed for i unique characters
      for (int j = 0; j < i; j++)
        s += max(0, x - t[p[j]]);
      
      if (s < ans)
        ans = s, w = i; // Update the best number of characters
    }
    
    // Reset len for building the replacement string q
    len = 0;
    
    // Construct the string q with exactly w characters, each appearing n/w times
    for (int j = 0; j < w; j++) {
      // If current character's frequency exceeds required, we only use required count
      if (t[p[j]] > n / w)
        t[p[j]] = n / w;
      else
        // Fill the rest of the positions for this character
        for (int i = t[p[j]]; i < n / w; i++)
          q[++len] = p[j] + 'a';
    }
    
    // Reset the frequencies for unused characters
    for (int j = w; j < 26; j++)
      t[p[j]] = 0;
    
    // Go through original string s and construct the result
    for (int i = 0; i < n; i++) {
      int x = s[i] - 'a';
      if (t[x]) {
        // If we still have this character to use
        t[x]--;
      } else {
        // Replace this position with a character from q (used up)
        s[i] = q[len--];
      }
    }
    
    // Print the minimum number of changes and the resulting string
    printf("%d\n%s\n", ans, s), len = 0;
  }
}


// https://github.com/VaHiX/CodeForces/