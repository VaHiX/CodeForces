// Problem: CF 2061 G - Kevin and Teams
// https://codeforces.com/contest/2061/problem/G

/*
G. Kevin and Teams
Algorithms/Techniques: Greedy approach with interactive queries.
Time Complexity: O(n) per test case (amortized), as we perform at most n queries.
Space Complexity: O(n), for storing arrays s, a, u, v, w.

This code attempts to determine the maximum number of teams (k) that can be formed 
from n classmates such that all teams either consist of friends or non-friends.
The solution uses an interactive approach with at most n queries to determine
friendship relationships and then constructs valid k teams.
*/

#include <cstdio>
#include <iostream>

using namespace std;
const int N = 100000;
int s[N], a[N], u[N], v[N], w[N]; // s: stack of candidates, a: answers from queries, u,v,w: team members

// Function to query friendship status between two classmates
int ask(int u, int v) {
  int x;
  printf("? %d %d\n", u, v);
  fflush(stdout);
  scanf("%d", &x);
  return x;
}

int main() {
  int T, n, k, b, m, i, x;
  for (scanf("%d", &T); T; T--) {
    scanf("%d", &n);
    k = (n + 1) / 3; // Maximum possible teams
    printf("%d\n", k);
    fflush(stdout);
    b = m = 0; // b: stack pointer, m: team counter
    
    for (i = 1; i <= n; i++)
      if (!b)
        s[b++] = i; // Initialize stack with first person
      else if (b == 1) {
        x = ask(s[0], i); // Query the first person with new person
        s[b++] = i;
      } else if (ask(s[b - 1], i) == x) // If same friendship status as previous
        s[b++] = i;
      else { // Friendship status differs from previous
        a[m] = x; // Store previous friendship result
        u[m] = s[b - 2]; // First team member
        v[m] = s[b - 1]; // Second team member
        w[m++] = i; // Third person (to be paired later)
        b -= 2; // Remove last two people from consideration
      }
    
    printf("!"); // Output start of answer
    
    // Output pairs from stack s (friends)
    for (i = 0; i < b - 1; i += 2) {
      if (!k) break;
      k--;
      printf(" %d %d", s[i], s[i ^ 1]); // Pair adjacent elements in stack
    }
    
    // Output pairs from u,v,w arrays (either friends or non-friends)
    for (i = 0; i < m; i++) {
      if (!k) break;
      k--;
      if (a[i] == x)
        printf(" %d %d", u[i], v[i]); // If friend, use original pair
      else
        printf(" %d %d", v[i], w[i]); // Otherwise, use swapped pair
    }
    
    printf("\n");
    fflush(stdout);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/