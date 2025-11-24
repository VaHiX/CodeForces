// Problem: CF 1692 H - Gambling
// https://codeforces.com/contest/1692/problem/H

/*
Algorithm/Techniques: Dynamic Programming with Map, Sliding Window Technique
Time Complexity: O(n log n) due to map operations (log n for each insert/update)
Space Complexity: O(n) for storing the array and map

This code solves the problem of finding the optimal strategy for Marian to maximize his money 
in a gambling game where he guesses a number for multiple rounds. The key idea is to track 
the best possible "score" for each number seen so far (based on winning/losing rounds), and 
then find the best interval to apply that guess to achieve maximum profit.
*/

#include <algorithm>
#include <iostream>
#include <map>

using namespace std;
int T, n, k, a[200005];
int main() {
  cin >> T;
  while (T--) {
    int res = -1, l, r, s = 0;
    map<int, int> last, f; // 'last' tracks last occurrence of a number, 'f' stores max score for each number
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      k = a[i];
      // Update the score for number k: 
      // subtract current index, add last occurrence index + 2, and take max with 1
      f[k] = max(f[k] - i + last[k] + 2, 1);
      last[k] = i;  // Update the last seen index of k
      if (f[k] > res) {  // If current score is better than best so far
        res = f[k];
        r = i;  // r is the end index of optimal interval
      }
    }
    // Backtrack from r to find left boundary of optimal interval
    for (l = r; s != res; l--) {
      if (a[l] == a[r])
        s++;   // Increment if it matches the chosen number
      else
        s--;   // Decrement otherwise
    }
    cout << a[r] << " " << l + 1 << " " << r << "\n";  // Output a, l, r
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/