// Problem: CF 1784 B - Letter Exchange
// https://codeforces.com/contest/1784/problem/B

/*
B. Letter Exchange
time limit per test4 seconds
memory limit per test512 megabytes

Algorithm/Techniques: 
Graph matching and greedy exchange optimization.
The approach identifies which people have excess of one letter and deficit of another,
and creates a matching to resolve this imbalance with minimal exchanges.

Time Complexity: O(m) for each test case, where m is the number of players.
Space Complexity: O(m) for storing edges and results per test case.

A cooperative game is played by
m
people. In the game, there are
3m
sheets of paper:
m
sheets with letter 'w',
m
sheets with letter 'i', and
m
sheets with letter 'n'.
Initially, each person is given three sheets (possibly with equal letters).
The goal of the game is to allow each of the
m
people to spell the word "win" using their sheets of paper. In other words, everyone should have one sheet with letter 'w', one sheet with letter 'i', and one sheet with letter 'n'.
To achieve the goal, people can make exchanges. Two people participate in each exchange. Both of them choose exactly one sheet of paper from the three sheets they own and exchange it with each other.
Find the shortest sequence of exchanges after which everyone has one 'w', one 'i', and one 'n'.
*/

#include <stdio.h>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;
const int mod = 998244353;
int cnt[3]; // Count of each letter (w, i, n) for current string
vector<int> edge[3][3]; // Edge list representation for letter exchanges, edge[j][k] stores indices where person has j excess and k deficit
int check(char ch) {
  if (ch == 'w')
    return 0;
  if (ch == 'i')
    return 1;
  if (ch == 'n')
    return 2;
}
char solve(int ch) {
  if (ch == 0)
    return 'w';
  if (ch == 1)
    return 'i';
  if (ch == 2)
    return 'n';
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        edge[i][j].clear(); // Clear edge structure for each test case
    
    for (int i = 1; i <= m; i++) {
      char str[5];
      scanf("%s", str);
      cnt[0] = cnt[1] = cnt[2] = 0;
      cnt[check(str[0])]++; // Count letters in current string
      cnt[check(str[1])]++;
      cnt[check(str[2])]++;
      
      for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++) {
          if (cnt[j] > 1 && cnt[k] < 1) {
            // If person has more than one j and less than one k, record this as a potential exchange
            edge[j][k].push_back(i);
          }
        }
    }
    
    vector<array<int, (int)4>> ans; // Stores the sequence of exchanges
    
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        // Match up pairs of people who can directly exchange to resolve imbalance
        while (edge[i][j].size() && edge[j][i].size()) {
          int p = edge[i][j].back();   // Get last person with excess i and deficit j
          edge[i][j].pop_back();
          int q = edge[j][i].back();   // Get last person with excess j and deficit i
          edge[j][i].pop_back();
          ans.push_back({p, i, q, j}); // Add exchange: p gives i to q, q gives j to p
        }
      }
    
    // Handle remaining unmatched cases forming cycles of length 3 (for triangular exchanges)
    for (int i = 0; i < edge[0][1].size(); i++) {
      int p1 = edge[0][1][i];
      int p2 = edge[1][2][i];
      int p3 = edge[2][0][i];
      ans.push_back({p1, 0, p2, 1}); // Exchange: person p1 gives w to p2, p2 gives i to p1
      ans.push_back({p2, 0, p3, 2}); // Exchange: person p2 gives w to p3, p3 gives n to p2
    }
    
    // Handle remaining cycle in reverse order
    for (int i = 0; i < edge[1][0].size(); i++) {
      int p1 = edge[1][0][i];
      int p2 = edge[0][2][i];
      int p3 = edge[2][1][i];
      ans.push_back({p1, 1, p2, 0}); // Exchange: person p1 gives i to p2, p2 gives w to p1
      ans.push_back({p2, 1, p3, 2}); // Exchange: person p2 gives i to p3, p3 gives n to p2
    }
    
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
      array<int, (int)4> cur = ans[i];
      printf("%d %c ", cur[0], solve((int)cur[1])); // Print first person and letter they exchange
      printf("%d %c\n", cur[2], solve((int)cur[3])); // Print second person and letter they exchange
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/