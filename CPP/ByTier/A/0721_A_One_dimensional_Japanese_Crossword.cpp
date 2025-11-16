// Problem: CF 721 A - One-dimensional Japanese Crossword
// https://codeforces.com/contest/721/problem/A

/*
 * Problem: One-dimensional Japanese Crossword
 * Algorithm: Linear scan to count consecutive black ('B') segments
 * Time Complexity: O(n), where n is the length of the string
 * Space Complexity: O(1) excluding the input and output storage
 *
 * The solution processes the input string from left to right,
 * counting consecutive 'B' characters and storing the count when
 * a 'W' is encountered or at the end of the string.
 */

#include <stdio.h>
#include <iostream>

using namespace std;
int main() {
  int i, j, k, n;
  char s[200];
  int count = 0, segment = 0;
  int a[100];
  cin >> n;
  scanf("%s", &s);
  k = 0;
  for (i = 0; i < n; i++) {
    if (s[i] == 'B') {
      count++;  // Increment count for each consecutive 'B'
    } else if (s[i] == 'W' && count != 0) {
      // When we encounter a 'W' after some 'B's, record the segment
      segment++;
      a[k] = count;
      k++;
      count = 0;  // Reset count for next segment
    }
    if (i == n - 1 && s[i] == 'B') {
      // Handle case where the last character is 'B'
      segment++;
      a[k] = count;
      break;
    }
  }
  cout << segment << endl;
  for (i = 0; i < segment; i++) {
    cout << a[i] << " ";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/