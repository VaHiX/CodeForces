// Problem: CF 479 B - Towers
// https://codeforces.com/contest/479/problem/B

/*
Code Purpose:
This program minimizes the instability of a set of towers by redistributing cubes among them.
The instability is defined as the difference between the tallest and shortest tower.
We use a greedy approach: in each step, we move a cube from the tallest tower to the shortest,
until we either run out of moves or the instability becomes 0.

Algorithms/Techniques:
- Greedy algorithm
- Sorting to quickly identify the tallest and shortest towers
- Vector of pairs to keep track of tower heights and their original indices

Time Complexity: O(n * log(n) + k * n * log(n))
- Sorting the towers takes O(n * log(n)) per iteration, and we do this up to k times.
- The total number of operations is bounded by k, so the dominant factor is O(k * n * log(n)).

Space Complexity: O(n)
- We store the tower heights and their original indices in a vector of pairs.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n, k;
  scanf("%ld %ld\n", &n, &k);
  std::vector<std::pair<long, long>> heightVec(n);
  for (int p = 0; p < n; p++) {
    long temp;
    scanf("%ld", &temp);
    heightVec[p].first = temp;
    heightVec[p].second = p + 1;  // Store original index
  }
  std::vector<std::pair<long, long>> moves;
  long instability(0);
  for (int q = 0; q < k; q++) {
    sort(heightVec.begin(), heightVec.end());  // Sort by height to find min/max easily
    if (heightVec[n - 1].first <= heightVec[0].first + 1) {
      break;  // If the difference is already at most 1, no more moves needed
    }
    --heightVec[n - 1].first;  // Decrease the tallest tower
    ++heightVec[0].first;      // Increase the shortest tower
    moves.push_back(
        std::pair<long, long>(heightVec[n - 1].second, heightVec[0].second));  // Record the move
  }
  sort(heightVec.begin(), heightVec.end());  // Final sort to determine the result
  printf("%ld %ld\n", heightVec[n - 1].first - heightVec[0].first,
         moves.size());
  for (int p = 0; p < moves.size(); p++) {
    printf("%ld %ld\n", moves[p].first, moves[p].second);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/