// Problem: CF 1735 C - Phase Shift
// https://codeforces.com/contest/1735/problem/C

/*
Purpose: 
This code solves the problem of finding the lexicographically smallest string 's' that could have resulted in the given string 't' after a phase shift transformation. 
Each character in 's' is replaced by the next character in a circular arrangement of 26 lowercase letters. 
The algorithm tries to assign each character in 't' to a predecessor in 's' such that the resulting string 's' is lexicographically minimal.

Approach:
- For each character in the input string 't', we determine the smallest valid predecessor in the circular arrangement.
- We maintain two arrays: 'to' and 'from' to track the mapping from character to next character and vice versa.
- A greedy approach ensures minimal lexicographical order by choosing the smallest available character as the predecessor.

Time Complexity: O(n * 26) = O(n), where n is the total length of all strings in the input (since sum of n over all test cases is bounded by 2*10^5).
Space Complexity: O(1) - only fixed size arrays of size 26 are used.
*/

#include <iostream>
#include <string>

using namespace std;
int to[26], from[26]; // to[i] stores the next character after i; from[i] stores the previous character before i
int main() {
  int T;
  cin >> T;
  for (; T--;) {
    int N;
    string S;
    cin >> N >> S;
    // Initialize the mapping arrays
    for (int i = 0; i < 26; i++)
      to[i] = from[i] = -1;
    // Process each character in the string
    for (char &c : S) {
      int u = c - 'a'; // Convert character to index (0-25)
      // If this character hasn't been assigned a predecessor yet
      if (to[u] == -1) {
        int v = 0;
        // Find the smallest valid predecessor
        for (;; v++) {
          // Skip if the candidate character is the same or already used as a predecessor
          if (u == v || from[v] != -1)
            continue;
          // Check if this assignment maintains a valid cyclic structure
          int w = v;
          int cnt = 0;
          // Traverse the chain to detect cycles
          while (to[w] != -1)
            w = to[w], cnt++;
          // If we complete a cycle (with less than 25 steps), skip this assignment
          if (w == u && cnt < 25)
            continue;
          // Assign the mapping
          to[u] = v;
          from[v] = u;
          break;
        }
      }
      // Update the current character in string S to the mapped predecessor
      c = to[u] + 'a';
    }
    cout << S << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/