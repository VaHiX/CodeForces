// Problem: CF 910 B - Door Frames
// https://codeforces.com/contest/910/problem/B

/*
Algorithm: Brute force with bitmasks
This solution uses a bitmask approach to try all possible combinations of how to assign the 6 sides 
(4 vertical and 2 horizontal) to the wooden bars. For each valid assignment (where exactly 4 sides are 
vertical and 2 are horizontal), it simulates cutting the bars and determines the minimum number of 
bars needed.

Time Complexity: O(2^C * C) where C = 6 (number of sides) -> O(64 * 6) = O(1)
Space Complexity: O(C) for the vector storage -> O(1)

The problem involves making two identical door frames, each with 2 vertical sides of length `a` and 1 
horizontal side of length `b`. We are to determine the minimal number of wooden bars of length `n` needed 
to construct these frames, where each side must be a solid piece (entire bar or a segment).

Techniques:
- Bitmask enumeration to generate all valid configurations of 6 sides (4 vertical, 2 horizontal)
- Greedy simulation of bar usage to calculate minimum required bars for each configuration
*/

#include <cstdio>
#include <vector>
std::vector<int> getVector(int x, int length) {
  std::vector<int> res;
  for (int p = 0; p < length; p++) {
    res.push_back(x % 2);  // Extract least significant bit
    x /= 2;               // Shift bits to the right
  }
  return res;
}
int countOnes(std::vector<int> x) {
  int cnt(0);
  for (int p = 0; p < x.size(); p++) {
    cnt += (x[p] == 1);  // Count number of 1s in the vector
  }
  return cnt;
}
int main() {
  const int A = 4;  // Number of vertical sides per door (2 per door * 2 doors = 4)
  const int B = 2;  // Number of horizontal sides per door (1 per door * 2 doors = 2)
  const int C = A + B; // Total number of sides (6)
  int n, a, b;
  scanf("%d %d %d", &n, &a, &b);
  int s(1);
  for (int p = 0; p < C; p++) {
    s *= 2;  // s = 2^C, i.e., all possible combinations
  }
  int minCnt(C + 1);  // Initialize to maximum possible value
  for (int p = 1; p < s; p++) {
    std::vector<int> vs = getVector(p, C);  // Get binary representation of p
    if (countOnes(vs) != A) {
      continue;  // Only consider configurations where exactly A (4) sides are vertical
    }
    int cnt(0), rem(0);
    for (int p = 0; p < vs.size(); p++) {
      int u = vs[p] ? a : b;  // If bit is 1, side is vertical (length a), else horizontal (length b)
      if (u > rem) {
        ++cnt;  // Need a new bar
        rem = n; // Reset remaining bar length to full
      }
      rem -= u; // Consume length u from current bar
    }
    minCnt = (minCnt < cnt) ? minCnt : cnt;  // Update minimum bars needed
  }
  printf("%d\n", minCnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/