// Problem: CF 2148 C - Pacer
// https://codeforces.com/contest/2148/problem/C

/*
C. Pacer
Algorithms/Techniques: Greedy approach with difference tracking
Time Complexity: O(n) per test case, where n is the number of requirements
Space Complexity: O(n) for storing the requirements

The problem involves maximizing points Farmer John can earn by moving between two sides of a gym,
while satisfying specific timing constraints. Each requirement specifies a time and required side.
John gains a point whenever he moves from one side to another during a minute.

The algorithm works as follows:
1. For each consecutive pair of requirements, calculate the expected movement:
   - If the time difference between requirements is odd, then John must move
     (because moving takes exactly one minute).
   - This is checked using the parity of (a[i] - a[i-1]) - (b[i] - b[i-1]).
2. Each such necessary move reduces the available points (M--).
3. The maximum points = M minus the number of required moves.

*/
#include <stdio.h>

int a[200005], b[200005];
int main() {
  int N, M, i, j, k, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &N, &M);  // Read number of requirements and total minutes
    for (i = 1; i <= N; i++)
      scanf("%d %d", &a[i], &b[i]);  // Read each requirement: time and required side
    a[0] = 0;  // Initialize start time to 0
    b[0] = 0;  // Initialize start side to 0
    for (i = 1; i <= N; i++)
      if (((a[i] - a[i - 1]) - (b[i] - b[i - 1])) % 2)  // Check if movement is necessary
        M--;  // Decrease available points if movement needed
    printf("%d\n", M);  // Output maximum points possible
  }
}


// https://github.com/VaHiX/codeForces/