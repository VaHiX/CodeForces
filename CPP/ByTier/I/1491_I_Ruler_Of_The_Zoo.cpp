// Problem: CF 1491 I - Ruler Of The Zoo
// https://codeforces.com/contest/1491/problem/I

/*
I. Ruler Of The Zoo
time limit per test
3 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

The problem simulates a tournament where animals fight to become the ruler of the zoo. Initially, animal 0 is the king, others form a queue. Each animal has different strengths A_i, B_i, C_i depending on consecutive wins (0, 1, or 2). Winner becomes the new king and loser goes back to the queue. If an animal wins 3 consecutive fights, it becomes the ruler.

Approach:
- Use simulation with a queue to manage the animals in line.
- Track the strength of each animal depending on their number of consecutive wins.
- The key challenge is efficiently managing the queue rotation to simulate fights until a winner achieves 3 consecutive victories.
- A special optimization handles cases where an individual animal wins multiple times in sequence and the tournament can be fast-forwarded due to the rotation pattern.

Time Complexity: O(n^2) average case, but can degrade to O(n^3) in worst-case scenarios involving many rotations.
Space Complexity: O(n) for storing arrays related to queue and fight states.
*/
#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>

#define For(i, l, r) for (register int i = (l); i <= (r); ++i)
#define For_down(i, r, l) for (register int i = (r); i >= (l); --i)
using namespace std;
constexpr int n_MAX = 6000 + 5;
int n, a[n_MAX], b[n_MAX], c[n_MAX], u[n_MAX];
bool w[n_MAX];
int p[n_MAX], q[n_MAX], x[n_MAX << 1], k, y[n_MAX << 1], l, r, skip, beat;

// Insert an animal index into the working structures for efficient simulation
void insert(const int z) {
  x[++k] = z;
  while ((l <= r) && (b[x[y[r]]] > b[z]))
    --r;
  y[++r] = k;
  if (c[x[k - 1]] > a[z])
    beat = (k - 1);
}

// Rotate the array elements in q starting from index 1 by 'm' positions
void rotate(const int m) {
  rotate(q + 1, q + ((n - m) - skip) + 1, q + (n - m) + 1);
}

// Simulate the tournament until a winner is crowned or it's determined that no one wins
pair<int, long long> simulate(long long sum, const bool prev) {
  if (prev) { // Handle the case when previous animal was king and won
    if (c[u[1]] > a[u[2]])
      return {u[1], sum + 1};
    rotate(u + 1, u + 2, u + n + 1), ++sum; // Update queue after fight
  }
  For(i, 1, n - 1) { // Process current round of fights
    if (w[i - 1]) { // Check if last animal won consecutive battles
      if (c[u[i - 1]] > a[u[i + 1]])
        return {u[i - 1], sum + i};
      w[i] = false;
    } else
      w[i] = (b[u[i]] > a[u[i + 1]]); // Determine who wins next based on strength
  }
  if (w[n - 1] && (c[u[n - 1]] > a[u[w[1] + 1]]))
    return {u[n - 1], sum + n};
  int m = 0, cur = 0;
  For(i, 1, n) {
    if (w[i - 1]) // If animal had prior consecutive win
      p[++m] = i;
    else
      q[++cur] = u[i]; // Add to queue
  }
  skip = (n - m), beat = k = 0, l = 1, r = 0; // Reset tracking variables
  For(i, 1, n - m) insert(q[i]); // Insert initial queue animals
  For(i, 1, m) {
    For(j, p[i - 1] + 1, p[i] - 1) insert(u[j]);
    while ((l <= r) && (b[x[y[l]]] < a[u[p[i]]]))
      skip = min(skip, k - y[l]), ++l; // Adjust skips if needed to optimize rounds
    if (beat)
      skip = min(skip, k - beat);
  }
  if (skip == (n - m)) // If no progress possible, tournament is infinite
    return {-1, -1};
  rotate(m), cur = 0;
  For(i, 1, n) if (!w[i - 1]) u[i] = q[++cur]; // Update queue
  return simulate(sum + ((n - 1) * skip), w[n - 1]); // Continue simulation with updated sum and state
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n;
  For(i, 0, n - 1) cin >> a[i] >> b[i] >> c[i];
  iota(u + 1, u + n, 1); // Initialize queue with animal indices
  if (a[0] > a[1])
    swap(u[1], u[n]); // Adjust initial order if needed
  const pair<int, long long> ans = simulate(1, false);
  cout << ans.first << ' ' << ans.second << '\n';
  return 0;
}


// https://github.com/VaHiX/codeForces/