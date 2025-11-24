// Problem: CF 1147 A - Hide and Seek
// https://codeforces.com/contest/1147/problem/A

/*
A. Hide and Seek
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Alice and Bob are playing a game on a line with n cells. There are n cells labeled from 1 through n.
For each i from 1 to n-1, cells i and i+1 are adjacent.
Alice initially has a token on some cell on the line, and Bob tries to guess where it is.
Bob guesses a sequence of line cell numbers x_1, x_2, ..., x_k in order.
In the i-th question, Bob asks Alice if her token is currently on cell x_i.
That is, Alice can answer either "YES" or "NO" to each Bob's question.
At most one time in this process, before or after answering a question, Alice is allowed to move her token from her current cell to some adjacent cell.
Alice acted in such a way that she was able to answer "NO" to all of Bob's questions.

Algorithms/Techniques:
- Preprocessing: for each cell, store first and last time it appears in queries
- For each possible starting position p, check if there exists an ending position q such that 
  Alice can avoid all guesses by possibly moving between the queries.
  
Time Complexity: O(n + k)
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> first(n + 2, 0), last(n + 2, 0); // Stores first and last occurrence of each cell in the query sequence
  for (long p = 1; p <= k; p++) {
    long x;
    scanf("%ld", &x);
    if (first[x] == 0) {
      first[x] = p;  // Record first time cell x appears
    }
    last[x] = p;   // Update last time cell x appears
  }
  long cnt(0);
  for (long p = 1; p <= n; p++) {
    if (last[p] == 0) {
      ++cnt;  // If cell p never appeared in input, Alice can start and end at this cell (1 possibility)
    }
    // Check if there is a valid way to put the token such that it does not appear in any adjacent position's query
    if (p > 1 && (first[p] == 0 || last[p - 1] < first[p])) {
      ++cnt;  // If previous cell has no occurrence or its last appearance is before this cell's first appearance, valid start/end combination.
    }
    if (p < n && (first[p] == 0 || last[p + 1] < first[p])) {
      ++cnt;  // Same logic for next cell
    }
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/