// Problem: CF 1739 F - Keyboard Design
// https://codeforces.com/contest/1739/problem/F

/*
 * Problem: Keyboard Design
 * 
 * Purpose: Given a dictionary of words formed from the first 12 letters of the Latin alphabet,
 *          find an arrangement of these 12 letters that maximizes the total usage count
 *          of words that can be typed with the keyboard, where consecutive letters in a word
 *          must be adjacent on the keyboard.
 * 
 * Approach:
 * 1. For each word, check if it can be typed using a keyboard layout. A word is valid if every
 *    vertex (letter) has degree ≤ 2 in the graph formed by adjacent letter pairs.
 * 2. Build a trie of possible valid starting paths for valid words.
 * 3. Use dynamic programming with bitmasks to find the optimal permutation of letters.
 *    State: f[mask][node] = max value achievable by placing letters in mask with current trie node.
 * 4. Reconstruct the optimal sequence by tracking transitions.
 *  
 * Time Complexity: O(2^12 * N) where N is the number of words, due to DP over all subsets
 * Space Complexity: O(2^12 * T) where T is the number of nodes in the trie, due to DP table and trie storage
 *
 * Algorithms/Techniques:
 * - Trie construction
 * - Dynamic Programming with bitmasks
 * - BFS for fail links (Aho-Corasick style)
 * - Subset DP
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;
const int o = 1 << 12, inf = 1e9;
int n, c, w[o], ch[o][12], fail[o], cnt, d[12], e[12][12], f[o][o], lstp[o][o],
    lstu[o][o], ans;
char s[o];
queue<int> q;

// DFS to build prefix paths in trie for valid words (those with all degrees <= 2)
void dfs(int nw, int fa, int u) {
  if (!ch[u][nw])
    ch[u][nw] = ++cnt;
  for (int i = 0; i < 13; ++i)
    if (i == 12)
      w[ch[u][nw]] += c;
    else if (e[nw][i] && i - fa) {
      dfs(i, nw, ch[u][nw]);
      break;
    }
}

int main() {
  scanf("%d", &n);
  for (int i = 1, len, flg; i <= n; ++i) {
    scanf("%d%s", &c, s + 1);
    len = strlen(s + 1);
    flg = 1;
    for (int j = 0; j < 12; ++j)
      d[j] = 0;
    for (int j = 0; j < 12; ++j)
      for (int k = 0; k < 12; ++k)
        e[j][k] = 0;
    for (int j = 1; j <= len; ++j)
      s[j] -= 'a';
    for (int j = 1; j < len; ++j)
      e[s[j]][s[j + 1]] = e[s[j + 1]][s[j]] = 1;
    for (int j = 0; j < 12; ++j)
      for (int k = 0; k < 12; ++k)
        d[j] += e[j][k];
    for (int j = 0; j < 12; ++j)
      if (d[j] > 2) {
        flg = 0;
        break;
      }
    if (flg)
      for (int j = 0; j < 12; ++j)
        if (d[j] == 1)
          dfs(j, -1, 0);
  }
  for (int i = 0; i < 12; ++i)
    if (ch[0][i])
      q.push(ch[0][i]);
  // BFS to assign fail links (standard Aho-Corasick)
  for (; !q.empty(); q.pop())
    for (int i = 0, u = q.front(); i < 12; ++i)
      if (ch[u][i])
        w[ch[u][i]] += w[fail[ch[u][i]] = ch[fail[u]][i]], q.push(ch[u][i]);
      else
        ch[u][i] = ch[fail[u]][i];
  // Initialize DP table
  for (int i = 0; i < (1 << 12); ++i)
    for (int j = 0; j <= cnt; ++j)
      f[i][j] = -inf;
  f[0][0] = 0;
  // DP over subsets of letters
  for (int i = 0; i < (1 << 12); ++i)
    for (int j = 0; j <= cnt; ++j)
      if (f[i][j] >= 0)
        for (int k = 0; k < 12; ++k)
          if (!((i >> k) & 1) &&
              f[i][j] + w[ch[j][k]] > f[i | (1 << k)][ch[j][k]])
            f[i | (1 << k)][ch[j][k]] = f[i][j] + w[ch[j][k]],
                        lstp[i | (1 << k)][ch[j][k]] = k,
                        lstu[i | (1 << k)][ch[j][k]] = j;
  // Find maximum optimal value
  for (int i = 0; i <= cnt; ++i)
    if (f[(1 << 12) - 1][i] > ans)
      ans = f[(1 << 12) - 1][i];
  // Reconstruct solution from DP table
  for (int i = 0; i <= cnt; ++i)
    if (f[(1 << 12) - 1][i] == ans) {
      for (int j = (1 << 12) - 1, u = i, p; j;)
        putchar(97 + (p = lstp[j][u])), u = lstu[j][u], j ^= (1 << p);
      break;
    }
  return 0;
}


// https://github.com/VaHiX/CodeForces/