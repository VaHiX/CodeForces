// Problem: CF 1838 D - Bracket Walk
// https://codeforces.com/contest/1838/problem/D

/*
 * Problem: D. Bracket Walk
 * 
 * Purpose:
 *   Determine if a bracket string is "walkable" after a series of flips.
 *   A walkable string means there exists a path from the first to last character
 *   such that the sequence of characters visited forms a valid bracket sequence.
 * 
 * Approach:
 *   - A valid bracket sequence has an equal number of '(' and ')' and at no point
 *     while reading left to right do we have more ')' than '('.
 *   - The idea is to maintain a "balance" (difference between '(' and ')') as we move.
 *   - Key insight: if we flip a character at position i (1-based), we check if:
 *     - It's a position where the parity (even/odd) matters in a valid sequence.
 *   - Maintain a set of "bad" positions (positions where the brackets don't follow
 *     the rules of a valid order).
 *   - If the set is empty, the string is walkable.
 * 
 * Time Complexity: O(n + q * log(n))
 *   - Preprocessing: O(n)
 *   - Each query: O(log(n)) for set operations
 * 
 * Space Complexity: O(n)
 *   - For storing the string and the set of indices
 * 
 * Algorithms/Techniques:
 *   - Set data structure for maintaining "bad" indices.
 *   - Parity-based logic for tracking valid bracket positions.
 *   - Balance tracking via index parity.
 */

#include <iostream>
#include <set>
#include <string>

#define LL long long
#define forn(i, aa, bb) for (int i = aa; i <= bb; ++i)
using namespace std;
const int N = 2e5 + 5;
string s;
int n;
set<int> q;  // set of "bad" indices (positions where bracket structure is invalid)
string ans[2];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  T = 1;
  ans[0] = "YES\n";
  ans[1] = "NO\n";
  while (T--) {
    int qq;
    cin >> n >> qq >> s;
    // If n is odd, it's impossible to form a valid bracket sequence
    if (n & 1) {
      forn(i, 1, qq) {
        int id;
        cin >> id;
        cout << "NO\n";
      }
      continue;
    }
    
    // Initialize set with "bad" positions based on initial string
    forn(i, 1, n) {
      if (i & 1) {  // odd position (1-based)
        if (s[i - 1] == ')')  // ')' at odd index is bad
          q.insert(i);
      } else {  // even position (1-based)
        if (s[i - 1] == '(')  // '(' at even index is bad
          q.insert(i);
      }
    }
    
    // Process queries
    forn(i, 1, qq) {
      int id;
      cin >> id;
      
      // Remove old bad state if necessary
      if (s[id - 1] == '(' && !(id & 1))  // '(' at even index was bad
        q.erase(id);
      if (s[id - 1] == ')' && (id & 1))  // ')' at odd index was bad
        q.erase(id);
      
      // Flip the character
      if (s[id - 1] == '(')
        s[id - 1] = ')';
      else
        s[id - 1] = '(';
      
      // Add new bad state if necessary
      if ((id & 1) && s[id - 1] == ')')  // ')' at odd index is now bad
        q.insert(id);
      else if (s[id - 1] == '(' && !(id & 1))  // '(' at even index is now bad
        q.insert(id);
      
      // Check if the string is walkable
      if (q.empty())
        cout << "YES\n";
      else if (*(q.begin()) & 1) {
        // Smallest bad index is odd -> impossible
        cout << "NO\n";
      } else {
        // Smallest bad index is even
        auto it = q.end();
        it--;  // Get last element
        if (!((*it) & 1)) {
          // Last bad index is even -> impossible
          cout << "NO\n";
        } else {
          // Valid case
          cout << "YES\n";
        }
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/