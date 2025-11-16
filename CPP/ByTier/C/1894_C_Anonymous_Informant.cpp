// Problem: CF 1894 C - Anonymous Informant
// https://codeforces.com/contest/1894/problem/C

/*
Algorithm: Simulation with cycle detection
Time Complexity: O(N * K) in worst case, but due to early termination and
constraints, it's effectively much faster in practice Space Complexity: O(N) for
the boolean array p and the input array A

The problem involves determining if a given array b can be obtained from some
initial array a after k operations. Each operation chooses a fixed point x
(where a[x] == x), then shifts the array left by x positions.

This implementation simulates the reverse process, starting from the final array
b and tracing back step by step, using cycle detection to avoid infinite loops.
*/

#include <stdio.h>
#include <utility>

#define fi first
#define se second
#define eb emplace_back
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;

int N, K;
int A[202020];  // Input array b
bool p[202020]; // Visited array to detect cycles

// Function to check if it's possible to reach the initial array after K
// operations st: current position in simulation k: remaining number of
// operations
int chk(int st, int k) {
  // If already visited or no more operations, return true
  if (p[st] || k == 0)
    return 1;
  // Calculate the index of the element that would have been at position st in
  // the previous step
  int idx = (st - 1 + N) % N;
  // If the element at idx is larger than N, it's invalid
  if (A[idx] > N)
    return 0;
  // Mark this position as visited
  p[st] = 1;
  // Recursively check next step with updated position and decremented operation
  // count
  return chk((st - A[idx] + N) % N, k - 1);
}

void solve() {
  scanf("%d%d", &N, &K);
  // Reset visited array for current test case
  for (int i = 0; i < N; i++)
    p[i] = 0;
  // Read the input array
  for (int i = 0; i < N; i++)
    scanf("%d", &A[i]);
  // Start simulation from index 0
  if (chk(0, K))
    printf("Yes\n");
  else
    printf("No\n");
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
}

// https://github.com/VaHiX/CodeForces/