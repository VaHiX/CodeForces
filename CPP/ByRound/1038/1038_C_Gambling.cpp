// Problem: CF 1038 C - Gambling
// https://codeforces.com/contest/1038/problem/C

/*
C. Gambling
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Two players A and B have a list of n integers each. They both want to maximize the subtraction between their score and their opponent's score. 
In one turn, a player can either add to his score any element from his list (assuming his list is not empty), the element is removed from the list afterward. Or remove an element from his opponent's list (assuming his opponent's list is not empty).
Note, that in case there are equal elements in the list only one of them will be affected in the operations above. For example, if there are elements {1, 2, 2, 3} in a list and you decided to choose 2 for the next turn, only a single instance of 2 will be deleted (and added to the score, if necessary). 
The player A starts the game and the game stops when both lists are empty. Find the difference between A's score and B's score at the end of the game, if both of the players are playing optimally.
Optimal play between two players means that both players choose the best possible strategy to achieve the best possible outcome for themselves. In this problem, it means that each player, each time makes a move, which maximizes the final difference between his score and his opponent's score, knowing that the opponent is doing the same.

Algorithm:
- Greedy approach with sorting
- Both players sort their lists in descending order
- Simulate the game by always choosing the best available option to maximize score difference
- At each turn, a player decides whether to take an element from their own list or remove an element from opponent's list
- Time Complexity: O(n log n) due to sorting; Space Complexity: O(n)

*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> va(n), vb(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &va[p]); // Read elements of player A's list
  }
  for (long p = 0; p < n; p++) {
    scanf("%ld", &vb[p]); // Read elements of player B's list
  }
  sort(va.rbegin(), va.rend()); // Sort A's list in descending order
  sort(vb.rbegin(), vb.rend()); // Sort B's list in descending order
  long xa(0), xb(0); // xa and xb are indices tracking current position in va and vb
  long long sa(0), sb(0); // sa and sb are scores of A and B
  for (long p = 0; p < n; p++) {
    // Player A's turn: decide whether to take from own list or remove from opponent's
    if ((xb >= n) || (xa < n && xb < n && va[xa] > vb[xb])) {
      sa += va[xa]; // Take element from A's list
      ++xa; // Move to next element in A's list
    } else {
      ++xb; // Remove element from B's list (effectively skip the element)
    }
    // Player B's turn: decide whether to take from own list or remove from opponent's
    if ((xa >= n) || (xa < n && xb < n && vb[xb] > va[xa])) {
      sb += vb[xb]; // Take element from B's list
      ++xb; // Move to next element in B's list
    } else {
      ++xa; // Remove element from A's list (effectively skip the element)
    }
  }
  printf("%lld\n", sa - sb); // Output difference between scores
  return 0;
}


// https://github.com/VaHiX/codeForces/