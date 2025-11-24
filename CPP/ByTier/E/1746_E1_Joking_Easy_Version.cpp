// Problem: CF 1746 E1 - Joking (Easy Version)
// https://codeforces.com/contest/1746/problem/E1

/*
Algorithm: This interactive problem uses a ternary search approach to identify a hidden integer x in the range [1, n].
The key idea is to divide the search space into three parts and use the constraint that at least one of two consecutive answers is correct.
We perform up to 82 queries to narrow down the possible values, and then make up to 2 guesses.
Time Complexity: O(log_3(n)) for queries, and O(1) for the final guesses.
Space Complexity: O(n) for storing the array of possible candidates.
*/
#include <iostream>

using namespace std;
int a[100010], b[100010];
char c[500010];
int main() {
  int n, i;
  cin >> n;
  // Initialize array with all possible values from 1 to n
  for (i = 1; i <= n; i++)
    a[i] = i;
  
  // While more than 2 elements remain, perform ternary search
  while (n > 2) {
    int tp = n / 3, l = tp, r = l + (n - tp) / 2;
    // First query: asking about the first l elements
    cout << "? " << l << ' ';
    for (i = 1; i <= l; i++) {
      cout << a[i] << ' ';
    }
    cout << endl;
    cin >> c;
    // If first answer is YES (or 'O' in the string)
    if (c[1] == 'O') {
      // Second query: ask again about the same set
      cout << "? " << l << ' ';
      for (i = 1; i <= l; i++) {
        cout << a[i] << ' ';
      }
      cout << endl;
      cin >> c;
      // If second answer is also YES, then the first is definitely correct
      if (c[1] == 'O') {
        // Move remaining elements to the front and reduce size
        for (i = 1; i <= n - l; i++)
          a[i] = a[i + l];
        n -= l;
        continue;
      }
    }
    // Otherwise, query a second set of elements
    cout << "? " << r - l << ' ';
    for (i = l + 1; i <= r; i++) {
      cout << a[i] << ' ';
    }
    cout << endl;
    cin >> c;
    // If this answer is YES, keep elements in the middle and adjust search space
    if (c[1] == 'O') {
      for (i = l + 1; i <= n - r + l; i++)
        a[i] = a[i + r - l];
      n -= r - l;
    } else {
      // If NO, then x must be in the right part
      n = r;
    }
  }
  // Final guess: output the first remaining element
  cout << "! " << a[1] << endl;
  cin >> c;
  // If first guess is wrong, try the second one
  if (c[1] == '(')
    cout << "! " << a[2] << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/