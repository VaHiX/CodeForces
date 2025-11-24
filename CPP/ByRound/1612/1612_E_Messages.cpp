// Problem: CF 1612 E - Messages
// https://codeforces.com/contest/1612/problem/E

/*
Purpose: 
This code solves the problem of determining which messages to pin in a conference 
to maximize the expected number of students who read their assigned messages. 
Each student has a limit on how many messages they will read, and if more 
messages are pinned than the limit, they randomly choose a subset of size k.

Algorithm/Techniques:
- For each possible number of pinned messages (from 1 to 20), we calculate 
  the expected number of students reading their assigned messages.
- We use a greedy approach to decide which messages to pin in each scenario.
- The key insight is to prioritize which messages are most beneficial for 
  maximizing the expected score based on student reading limits.

Time Complexity: O(n * 20 * log(n)) where n is the number of students.
Space Complexity: O(n * 20) for storing the v array and auxiliary structures.

*/
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
const int N = 2e5 + 1;
int n, a[N], b[N], s, A, I = 99, v[21][N]; // v[i][j] indicates if message j is pinned when i messages are pinned
pair<int, int> p[N]; // p[i].first = total potential reads for message i, p[i].second = message index
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i] >> b[i]; // a[i] = target message index, b[i] = max messages student i will read
  for (int i = 1; i <= 20; i++) { // try pinning 1 to 20 messages
    for (int j = 1; j < N; j++)
      p[j] = make_pair(0, j); // initialize p with 0 potential reads, store message index
    for (int j = 1; j <= n; j++)
      p[a[j]].first += min(b[j], i); // accumulate potential reads for each message
    sort(p + 1, p + N), s = 0; // sort by potential reads
    for (int j = N - 1; j >= N - i; j--)
      s += p[j].first, v[i][p[j].second] = 1; // select top i messages to pin, update v
    if (s * I > A * i) // greedy selection: maximize s/i (expected value per pinned message)
      A = s, I = i; // update best number of messages to pin
  }
  cout << I << '\n';
  for (int i = 1; i < N; i++)
    if (v[I][i]) // print indices of pinned messages
      cout << i << ' ';
  return 0;
}


// https://github.com/VaHiX/CodeForces/