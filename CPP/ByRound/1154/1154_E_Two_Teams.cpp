// Problem: CF 1154 E - Two Teams
// https://codeforces.com/contest/1154/problem/E

/*
E. Two Teams
Algorithms/Techniques: Greedy, Deque-like Simulation, Two Pointers

Time Complexity: O(n)
Space Complexity: O(n)

The code simulates a game where two coaches alternately select students to form teams.
Each coach selects the student with the highest remaining skill and takes k closest
students to the left and right of that student. The process continues until all students
are assigned to a team. A linked-list like structure (using pre[] and nxt[]) is used to
efficiently manage the deletion of selected students from the row.
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
int n, m, b[200005], a[200005], pre[200005], nxt[200005], ans[200005];
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    pre[i] = i - 1;           // previous node in the linked list
    nxt[i] = i + 1;           // next node in the linked list
    scanf("%d", &a[i]);
    b[a[i]] = i;              // map skill value to position
  }
  int id = 2;                 // toggle between 1 and 2 for team assignment
  for (int i = n; i >= 1; i--) { // process from highest skill to lowest
    if (ans[b[i]])           // skip if already assigned
      continue;
    id = 3 - id;             // alternate team: 1 -> 2 -> 1 -> ...
    int k = m, l = pre[b[i]], r = nxt[b[i]]; // start from left and right of current student
    ans[b[i]] = id;          // assign current student to team
    while (l != 0 && k > 0) { // move left and assign k students
      k--;
      ans[l] = id;
      l = pre[l];
    }
    k = m;
    while (r <= n && k > 0) { // move right and assign k students
      k--;
      ans[r] = id;
      r = nxt[r];
    }
    nxt[l] = r;              // remove selected range from the list by linking gaps
    pre[r] = l;
  }
  for (int i = 1; i <= n; i++)
    printf("%d", ans[i]);   // print final team assignments
  return 0;
}


// https://github.com/VaHiX/codeForces/