// Problem: CF 876 D - Sorting the Coins
// https://codeforces.com/contest/876/problem/D

/*
Purpose: This code solves the problem of determining the "hardness of ordering" 
         after each replacement of a coin from out-of-circulation to in-circulation.

Algorithms/Techniques:
- Simulation of the sorting process using a greedy approach
- Efficient tracking of the rightmost out-of-circulation coin to avoid redundant checks

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm maintains a boolean vector to track which coins are in circulation.
It keeps track of the rightmost out-of-circulation coin and updates it as coins are replaced.
The hardness of ordering is calculated based on the number of steps needed to sort the coins,
which is related to how many times we need to scan from the beginning and perform exchanges.

The key insight is that the number of steps can be derived by counting how many valid 
exchanges are needed, which is efficiently tracked using the rightmost out-of-circulation coin.
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<bool> mark(n); // Track if coin is in circulation (1) or not (0)
  printf("1 "); // Initially all coins are out of circulation, so hardness is 1
  long right(n - 1), cnt(0); // 'right' tracks the rightmost out-of-circulation coin
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    --x; // Convert to 0-based indexing
    mark[x] = 1; // Mark the coin at position x as in circulation
    
    if (x == right) { // If the replaced coin was the rightmost out-of-circulation coin
      // Move 'right' pointer backwards as long as coins are in circulation
      while (right >= 0 && mark[right]) {
        cnt++;
        --right;
      }
    }
    // The hardness is computed as: 2 + p - cnt
    // where p is the current step, and cnt is how many exchanges we avoided
    printf("%ld ", 2 + p - cnt);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/