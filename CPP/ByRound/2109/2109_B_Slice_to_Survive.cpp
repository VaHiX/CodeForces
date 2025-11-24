// Problem: CF 2109 B - Slice to Survive
// https://codeforces.com/contest/2109/problem/B

/*
B. Slice to Survive

Purpose:
This code computes the minimum number of turns required for Mouf to isolate Fouad's monster in an n×m grid, assuming both players play optimally. Mouf tries to minimize the number of cuts (turns), while Fouad tries to maximize it.

Algorithms/Techniques:
- The problem is modeled as a game tree where each turn involves either cutting a row or column and then Fouad moves his monster.
- The key idea is that in each turn, Mouf makes a cut to reduce the grid size, and Fouad chooses a move to prolong the game.
- The optimal strategy for both players is to choose the most effective cuts to either minimize or maximize the number of turns.
- The minimum number of turns depends on the distance from the starting position (a,b) to the edges of the grid and how efficiently these can be reduced.

Time Complexity: O(1) per test case
Space Complexity: O(1)

*/
#include <algorithm>
#include <cmath>
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, a, b;
    scanf("%ld %ld %ld %ld", &n, &m, &a, &b); // Read grid dimensions and initial monster position
    // Calculate minimum turns needed if Mouf optimally cuts along rows first
    long resA = ceil(log2(std::min(a, n - a + 1))) + ceil(log2(m)) + 1;
    // Calculate minimum turns needed if Mouf optimally cuts along columns first
    long resB = ceil(log2(n)) + ceil(log2(std::min(b, m - b + 1))) + 1;
    // Output the smaller of the two possible turn counts
    printf("%ld\n", std::min(resA, resB));
  }
}


// https://github.com/VaHiX/codeForces/