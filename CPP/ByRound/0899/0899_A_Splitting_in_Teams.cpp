// Problem: CF 899 A - Splitting in Teams
// https://codeforces.com/contest/899/problem/A

/*
Code Purpose:
This program determines the maximum number of teams of exactly three people that can be formed from given groups of students.
Each group contains either one person or two people. 
For groups of two people, both must either participate in the same team or none at all.
The approach involves counting the number of single-person groups (x) and two-person groups (y),
and then computing two strategies:
1. Using one single-person group with each two-person group to form a team (this is represented by j).
2. Combining three single-person groups to form a team (this is represented by k).
The maximum of these two strategies is the answer.

Algorithms/Techniques:
Greedy approach with case analysis based on counts of single and double groups.

Time Complexity: O(n) - single pass through the input array.
Space Complexity: O(1) - only a few variables used for counting.
*/

#include <algorithm>
#include <cstdio>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 200
#define inf 1000000000
#define pp pair<string, int>
using namespace std;

int main() {
  int i, j = 0, k = 0;
  int n, m, t;
  int x = 0, y = 0; // x counts single-person groups, y counts two-person groups
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &t);
    if (t == 1)
      x++; // increment single-person group count
    else
      y++; // increment two-person group count
  }
  // Strategy 1: Use single-person groups as fillers for two-person groups
  if (y > x)
    j = x; // can only pair x single groups with y two groups
  else {
    j += y; // pairs all y two groups
    j += (x - y) / 3; // remaining single groups can form (x-y)/3 teams of 3
  }
  // Strategy 2: Use three single-person groups to form teams
  k = (x / 3); // teams formed from triplets of single groups
  x -= (x / 3 * 3); // remaining single groups after forming triplets
  if (y > x)
    k += x; // pair each of the remaining single groups with a two-group
  else {
    k += y; // pairs all two groups with single groups
    k += (x - y) / 3; // leftover single groups form more triplets
  }
  printf("%d", max(j, k)); // output the better strategy
  return 0;
}


// https://github.com/VaHiX/CodeForces/