// Problem: CF 736 A - Tennis Championship
// https://codeforces.com/contest/736/problem/A

/*
 * Problem: Tennis Championship
 * 
 * Purpose: Given n players in a knockout tournament, determine the maximum number of games
 *          the winner can play, under the constraint that two players can only play if 
 *          their number of games played differs by at most 1.
 * 
 * Algorithm: This problem is solved using a greedy approach based on Fibonacci-like sequence.
 *            We build a sequence where each term represents the minimum number of players 
 *            needed to achieve a certain number of rounds. The recurrence is:
 *            dp[i] = dp[i-1] + dp[i-2], starting with dp[0] = 1, dp[1] = 2.
 *            This represents the minimum number of participants required to have exactly i 
 *            rounds in the tournament (in the best possible arrangement).
 *            
 * Time Complexity: O(log n) - since we're generating a Fibonacci-like sequence up to n,
 *                     and the growth is exponential.
 * Space Complexity: O(log n) - for storing the sequence up to the maximum needed value.
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
  long long x;
  cin >> x;
  // Initialize the sequence to simulate the minimum number of players needed
  // for each round of the tournament to be possible under the given constraints.
  vector<long long> dp = {1, 2};
  
  // Continue building the sequence while the sum of the last two elements
  // is less than or equal to x (number of players).
  while (dp[dp.size() - 1] + dp[dp.size() - 2] <= x) {
    dp.push_back(dp[dp.size() - 1] + dp[dp.size() - 2]);
  }
  
  // The size of the sequence minus 1 gives the maximum number of rounds
  // the winner can play (since we are looking for the largest k such that 
  // the k-th Fibonacci-like number <= n).
  cout << dp.size() - 1 << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/