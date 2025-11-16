// Problem: CF 1738 H - Palindrome Addicts
// https://codeforces.com/contest/1738/problem/H

/*
 * Problem: H. Palindrome Addicts
 * Algorithm: Palindromic Substrings Counting using Palindromic Tree (Eertree)
 * Time Complexity: O(n) amortized for all operations where n is the total number of characters pushed
 * Space Complexity: O(n) where n is the length of the sequence of pushed characters
 *
 * The solution uses a Palindromic Tree (also known as Eertree) to efficiently maintain
 * the count of distinct palindromic substrings while inserting and deleting characters.
 * The tree supports:
 *  - Adding a character to the end (push)
 *  - Removing a character from the front (pop)
 * For each operation, the number of distinct palindromic substrings is output.
 */

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
typedef pair<int, int> pii;
int cnt, q, lst, cur; // cnt: node count, q: operations, lst: previous operation result, cur: current node in tree
int s[1000004];       // s: input string with indices
int it, n, ans;       // it: deletion offset, n: string length, ans: current answer
int ch[1000004][26], num[1000004]; // ch: children, num: count of palindromes ending at node
int nx[1000004], le[1000004];      // nx: fail links (suffix links), le: length of palindrome
int fa[1000004], tg[1000004];      // fa: parent, tg: tail index of palindrome
vector<int> vec[1000004];          // vec: list of palindromes ending at position

// Function to get the appropriate node in the palindrome tree for insertion
int get(int x, int p) {
  // While the prefix of current node doesn't match, move to its suffix link
  while (p - le[x] - 1 < 0 || s[p - le[x] - 1] != s[p])
    x = nx[x];
  return x;
}

// Add character c to the end of the string
void push(char c) {
  ++n, s[n] = c, cur = get(cur, n); // Increment length and find correct node
  bool now = 0; // Flag to check if new node was added

  // If there's no node for this character from current node, create one
  if (!ch[cur][c]) {
    int p = ++cnt; // New node index
    int q = nx[p] = ch[get(nx[cur], n)][c]; // Create suffix link for new node
    ch[cur][c] = p, fa[p] = cur; // Link child to parent
    num[q]++, le[p] = le[cur] + 2; // Set length and increment count
    now = 1;
    ++ans; // Increment palindrome count
  }
  cur = ch[cur][c], tg[cur] = n; // Move to new node
  if (!num[cur])
    vec[n - le[cur] + 1].push_back(cur); // Store palindrome in vec
}

// Remove character from front of the string
void pop() {
  ++it, s[it] = -1; // Mark deleted position
  int p = -1; // Node to be removed

  // Find node that can be deleted (tail matches position and count is 0)
  for (auto x : vec[it])
    if (!num[x] && it == tg[x] - le[x] + 1)
      p = x;

  if (~p) { // If found removable node
    for (int c = 0; c < 26; c++)
      if (ch[fa[p]][c] == p)
        ch[fa[p]][c] = 0; // Remove reference from parent
    --ans; // Decrement palindrome count

    int q = nx[p]; // Get suffix link of node
    num[q]--, tg[q] = max(tg[q], tg[p]); // Decrement count and update tail

    if (!num[q] && q > 1)
      vec[tg[q] - le[q] + 1].push_back(q); // Add suffix link back to vector

    if (cur == p)
      cur = q; // Update current node if needed
  }
}

int main() {
  scanf("%d", &q);
  cnt = 1, nx[0] = 1, le[1] = -1, s[0] = -1; // Initialize palindrome tree with base nodes

  while (q--) {
    char buf[10], ch[10];
    scanf("%s", buf); // Read command

    if (buf[1] == 'u') { // Push operation
      scanf("%s", ch), push(ch[0] - 'a');
    } else { // Pop operation
      pop();
    }

    printf("%d\n", ans); // Output current count of distinct palindromic substrings
  }

  return 0;
}


// https://github.com/VaHiX/CodeForces/