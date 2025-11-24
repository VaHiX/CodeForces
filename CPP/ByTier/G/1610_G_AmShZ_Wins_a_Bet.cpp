// Problem: CF 1610 G - AmShZ Wins a Bet
// https://codeforces.com/contest/1610/problem/G

/*
 * Problem: G. AmShZ Wins a Bet
 * 
 * Algorithm/Technique: 
 * - This solution uses a stack-based approach to reconstruct the lexicographically smallest 
 *   valid bracket sequence from a given string after a series of operations.
 * - The core idea is to process the string from right to left and maintain a "next" array 
 *   that helps in identifying the best candidate for placing the opening bracket.
 * - It utilizes a modified suffix comparison technique to efficiently determine the order.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * The problem involves undoing a sequence of operations where a string is cut into three parts,
 * and a '(' and ')' are inserted in between. We are to find the lexicographically smallest 
 * possible initial bracket sequence that could result in the given final string.
 */

#include <string.h>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;
#define N 300020
typedef long long ll;
int a[N], n, nxt[N];
char s[N];

// Compare two suffixes starting at i and j using the next array for optimization
bool cmp(int i, int j) {
  while (i <= n && j <= n && s[i] == s[j])
    i = nxt[i + 1], j = nxt[j + 1];  // Skip to next positions using the next array
  if (i <= n && j <= n)
    return s[i] <= s[j];  // If characters differ, compare them
  return i > n && j <= n;   // If i is exhausted, then s[i] < s[j] lexicographically
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> (s + 1);  // Read string starting from index 1
  n = strlen(s + 1);
  stack<int> st;  // Stack to hold indices of ')' characters
  st.push(n + 1);
  nxt[n + 1] = n + 1;  // Initialize next array

  // Process string from right to left
  for (int i = n; i >= 1; --i) {
    nxt[i] = i;  // Default next is current index
    if (s[i] == ')') {
      st.push(i);  // Push index of ')' to stack
    } else {
      st.pop();  // Pop from stack (we match a '(' with a ')' from stack)
      if (st.empty()) {
        st.push(i);  // If stack is empty, put current index (this '(' will not be matched)
      } else if (cmp(i, st.top())) {
        // If current '(' is lexicographically smaller than top of stack, replace top with current index
        st.top() = i;
      } else {
        // If current '(' is lex greater or equal to top, link this '(' to the top in the next array
        nxt[i] = st.top();
      }
    }
  }

  // Build the result by traversing the 'next' array
  for (int i = 1; i <= n; i = nxt[i + 1]) {
    cout << s[i];
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/