// Problem: CF 1609 E - William The Oblivious 
// https://codeforces.com/contest/1609/problem/E

/*
Purpose: 
This code solves the problem of dynamically maintaining a string of characters 'a', 'b', and 'c' and answering queries about the minimum number of character replacements needed to ensure the string does not contain "abc" as a subsequence. It uses a segment tree with dynamic updates and maintains six values for each node to track the minimum cost of avoiding "abc" subsequences.

Algorithms/Techniques:
- Segment Tree with Lazy Propagation
- Dynamic Programming on Trees
- Subsequence Pattern Matching

Time Complexity: O((n + q) * log n)
Space Complexity: O(n)

The segment tree maintains for each node:
- t1: count of 'a' characters in subtree
- t2: count of 'b' characters in subtree  
- t3: count of 'c' characters in subtree
- t4: minimum cost to make a valid prefix ending with 'a' or 'b'
- t5: minimum cost to make a valid prefix ending with 'b' or 'c'
- t6: minimum cost to make a valid prefix (no "abc" subsequence)
*/
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
#define ll long long
const ll N = 1e5 + 10, M = N << 2;
ll n, q, x, t1[M], t2[M], t3[M], t4[M], t5[M], t6[M];
string s;
char ch;

// Push up function to update parent node values from children
void push_up(ll rt) {
  t1[rt] = t1[rt << 1] + t1[rt << 1 | 1];  // Sum of 'a' counts
  t2[rt] = t2[rt << 1] + t2[rt << 1 | 1];  // Sum of 'b' counts
  t3[rt] = t3[rt << 1] + t3[rt << 1 | 1];  // Sum of 'c' counts
  
  // t4: minimum cost to have a prefix that doesn't contain "abc" and ends with a or b
  t4[rt] = min(t1[rt << 1] + t4[rt << 1 | 1], t4[rt << 1] + t2[rt << 1 | 1]);
  
  // t5: minimum cost to have a prefix that doesn't contain "abc" and ends with b or c
  t5[rt] = min(t2[rt << 1] + t5[rt << 1 | 1], t5[rt << 1] + t3[rt << 1 | 1]);
  
  // t6: minimum cost to have a prefix that doesn't contain "abc" at all
  t6[rt] = min({t1[rt << 1] + t6[rt << 1 | 1], t6[rt << 1] + t3[rt << 1 | 1],
                t4[rt << 1] + t5[rt << 1 | 1]});
}

// Update function to modify a character in the string and propagate changes
void update(ll rt, ll l, ll r, ll x, char ch) {
  if (x < l || r < x)
    return;
  if (l == r) {
    // Reset node values
    t1[rt] = t2[rt] = t3[rt] = 0;
    // Set new character count
    if (ch == 'a')
      t1[rt] = 1;
    else if (ch == 'b')
      t2[rt] = 1;
    else
      t3[rt] = 1;
    return;
  }
  ll mid = l + r >> 1;
  update(rt << 1, l, mid, x, ch);       // Update left child
  update(rt << 1 | 1, mid + 1, r, x, ch); // Update right child
  push_up(rt);                          // Propagate updated values
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q >> s;
  s = " " + s;  // 1-indexed
  for (int i = 1; i <= n; i++)
    update(1, 1, n, i, s[i]);  // Initialize segment tree with original string
  while (q--)
    cin >> x >> ch, update(1, 1, n, x, ch), cout << t6[1] << "\n";  // Process queries
  return 0;
}


// https://github.com/VaHiX/CodeForces/