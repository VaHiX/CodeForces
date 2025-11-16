// Problem: CF 999 A - Mishka and Contest
// https://codeforces.com/contest/999/problem/A

/*
Code Purpose:
This program determines the maximum number of problems Mishka can solve in a programming contest,
given his problem-solving skill level k and a list of n problems with their difficulties.
Mishka can only solve problems from the ends of the list (leftmost or rightmost) and stops when
he can't solve any problem from either end. The algorithm uses a greedy approach by always choosing
the smallest available problem from the ends.

Algorithms/Techniques:
- Greedy Algorithm: At each step, choose the smallest difficulty problem from the ends.
- Data Structure: deque (double-ended queue) to efficiently remove elements from both ends.

Time Complexity: O(n) where n is the number of problems. Each element is pushed and popped once.
Space Complexity: O(n) for storing the deque of problems.

*/
#include <stdio.h>
#include <algorithm>
#include <deque>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 20100
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s", s)
#define pb push_back
using namespace std;
int main() {
  int i, j, k;
  int n, m;
  sff(n, k); // Read number of problems and Mishka's skill level
  deque<int> q; // Create a deque to store the problems
  for (i = 0; i < n; i++)
    sf(m), q.push_back(m); // Read and add each problem's difficulty to the deque
  int cnt = 0; // Counter for solved problems
  while (q.size() > 0) { // While there are problems left
    if (q.front() <= k) // If the leftmost problem can be solved
      q.pop_front(), cnt++; // Remove and solve it
    else if (q.back() <= k) // Else if the rightmost problem can be solved
      q.pop_back(), cnt++; // Remove and solve it
    else
      break; // If neither end can be solved, stop
  }
  pf(cnt); // Print the number of problems solved
  return 0;
}


// https://github.com/VaHiX/CodeForces/