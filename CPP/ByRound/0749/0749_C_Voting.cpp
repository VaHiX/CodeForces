// Problem: CF 749 C - Voting
// https://codeforces.com/contest/749/problem/C

/*
 * Problem: C. Voting
 * 
 * Purpose: Simulate a voting process where two factions (D = depublicans, R = remocrats) 
 *          compete. Each voter can eliminate another voter, and the process continues 
 *          in rounds until only one voter remains, who decides the outcome in favor of 
 *          their faction.
 * 
 * Algorithm:
 *   - Use two queues to represent the order of voters from each faction.
 *   - In each round, the voter with the smaller index (earlier in the sequence) takes action.
 *   - That voter eliminates the other faction's voter with the smaller index.
 *   - The eliminated voter is removed from the queue, and the acting voter is moved to the end of their queue.
 *   - Repeat until one queue is empty, then the remaining faction wins.
 * 
 * Time Complexity: O(n), where n is the number of employees. Each employee is enqueued and dequeued at most once.
 * Space Complexity: O(n), for the two queues storing up to n elements.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 2000
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  sf(n);
  string s;
  cin >> s;
  queue<int> D, R; // Queues to hold indices of depublicans and remocrats
  
  // Populate queues with indices of employees based on their faction
  for (i = 0; i < n; i++) {
    if (s[i] == 'D')
      D.push(i + 1); // Store 1-based index
    else
      R.push(i + 1);
  }
  
  // Simulate the voting process
  while (true) {
    // If one faction is out of voters, the other wins
    if (D.empty()) {
      pfs("R");
      break;
    } else if (R.empty()) {
      pfs("D");
      break;
    }
    
    // Determine who acts next (the one with smaller index)
    if (D.front() < R.front()) {
      k = D.front() + n; // Calculate new index after rotation
      D.pop(); // Remove acting voter
      D.push(k); // Add acting voter to end of queue with updated index
      R.pop(); // Remove the eliminated voter
    } else {
      k = R.front() + n; // Calculate new index after rotation
      D.pop(); // Remove acting voter
      R.push(k); // Add acting voter to end of queue with updated index
      R.pop(); // Remove the eliminated voter
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/