// Problem: CF 1867 C - Salyg1n and the MEX Game
// https://codeforces.com/contest/1867/problem/C

/*
Code Purpose:
This code implements a strategy for Alice in an interactive game against Bob, where Alice aims to maximize the MEX of a set S, and Bob aims to minimize it. 
Alice alternately adds numbers and Bob removes numbers, with specific rules. The algorithm identifies the optimal number Alice should add based on the current state of the set S to ensure the MEX is maximized.

Algorithms/Techniques:
- MEX calculation: Find the smallest non-negative integer not present in the set.
- Optimal strategy: Determine the best number for Alice to add, based on the current state and the position of gaps in the sequence.
- Interactive problem handling: Read and respond to moves from the jury (Bob).

Time Complexity:
- O(n log n) per test case due to sorting the initial set S.
- The main logic runs in O(n) as it processes the sorted list once.

Space Complexity:
- O(n) for storing the set S.

*/
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
#define debug(x) cout << #x << "=" << x << "\n";
#define debugg(x, y) cout << #x << "=" << x << " " << #y << "=" << y << "\n";
typedef long long ll;
typedef pair<int, int> PII;
const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;
int n, m, k;
int a[N], b[N];
int solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  sort(a + 1, a + 1 + n); // Sort the set S to analyze gaps in consecutive numbers
  bool flag = false;
  int pos = -1, mex = -1, cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (!flag && a[i] != cnt) // Check if the current expected number 'cnt' is missing
      pos = cnt, flag = true, cnt++; // Record this missing number as a potential candidate
    else if (a[i] != cnt) { // If a gap larger than 1 is found
      mex = cnt; // Set MEX to the smallest missing non-negative integer found
      break;
    }
    cnt++; // Increment expected number
  }
  int f = -1;
  if (pos == -1) // All numbers from 0 to n-1 are present
    mex = n + 1, f = 1; // MEX is n, since 0 to n-1 are all present
  else if (mex == -1) // No gap found in the sequence
    mex = n, f = 2; // MEX is n, as the sequence continues from 0...n-1
  if (f == 1) {
    cout << n << endl; // Alice adds n to make MEX = n+1, optimal choice
  } else if (f == 2) {
    cout << pos << endl; // Alice adds pos (which is the smallest missing number), optimal choice
  } else {
    cout << pos << endl; // Same as f == 2 case
  }
  while (1) { // Interactive loop
    int x;
    cin >> x;
    if (x == -1)
      return 0; // Game is over
    if (x == -2)
      return 1; // Invalid move
    cout << x << endl; // Bob removes a number
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    if (solve() == 0)
      continue;
    else
      break;
  }
}


// https://github.com/VaHiX/CodeForces/