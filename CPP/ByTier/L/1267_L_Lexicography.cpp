// Problem: CF 1267 L - Lexicography
// https://codeforces.com/contest/1267/problem/L

/*
Purpose: 
This code solves the problem of generating n words of length l each from a given string of n*l letters,
such that the k-th word in lexicographical order is minimized. The algorithm uses sorting and greedy assignment.

Approach:
1. Sort all input characters to get the smallest possible characters available.
2. Construct the first k-1 words by assigning the smallest available characters in order.
3. For the k-th word, we assign characters to minimize it lexicographically while considering that the previous k-1 words are already set.
4. Assign remaining characters to the rest of the words.

Time Complexity: O((n*l)*log(n*l)) due to sorting.
Space Complexity: O(n*l) for storing the words and auxiliary arrays.

Algorithms/Techniques:
- Sorting
- Greedy assignment
- String manipulation
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
#define ll long long
char a[1005][1005];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m, k, tot = 0;
  string s;
  cin >> n >> m >> k >> s;
  sort(s.begin(), s.end()); // Sort all characters to get the lexicographically smallest order
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j < k; j++) {
      // If the current character in previous row matches the k-th word's character,
      // assign the next available character to current position
      if (a[j][i - 1] == a[k - 1][i - 1])
        a[j][i] = s[tot++];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      // Fill in any remaining positions with the next available characters
      if (a[i][j] == 0)
        a[i][j] = s[tot++];
    }
  }
  for (int i = 0; i < n; i++)
    cout << a[i] + 1 << '\n'; // Print each row (word) starting from index 1
}


// https://github.com/VaHiX/CodeForces/