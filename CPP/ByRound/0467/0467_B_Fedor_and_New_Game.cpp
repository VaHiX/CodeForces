// Problem: CF 467 B - Fedor and New Game
// https://codeforces.com/contest/467/problem/B

/*
Purpose: This program determines how many players can become friends with Fedor in the game "Call of Soldiers 3".
         Two players are friends if their armies (represented as integers) differ in at most k binary bits.
         The solution converts each player's army into a binary representation and compares it with Fedor's army.

Algorithms/Techniques: 
- Binary representation conversion
- Bitwise comparison using Hamming distance
- Linear scan through all players except Fedor

Time Complexity: O(m * n) where m is the number of players (excluding Fedor) and n is the number of soldier types.
Space Complexity: O(n) for storing the binary representations of armies.

*/
#include <cstdio>
#include <vector>
std::vector<bool> convertToBinary(int x) {
  std::vector<bool> output;
  while (x > 0) {
    output.push_back(x % 2); // Extract the least significant bit
    x /= 2; // Shift right by one bit
  }
  return output;
}
int compareBinaryVectors(std::vector<bool> first, std::vector<bool> second) {
  int output = 0;
  int p = 0;
  while (p < first.size() || p < second.size()) {
    if (p < first.size() && p < second.size()) {
      output += (first[p] != second[p]); // Count differing bits
    } else if (p < first.size()) {
      output += (first[p] != 0); // Count remaining bits in first
    } else if (p < second.size()) {
      output += (second[p] != 0); // Count remaining bits in second
    }
    ++p;
  }
  return output;
}
int main() {
  int n, m, k;
  scanf("%d %d %d\n", &n, &m, &k);
  std::vector<int> xvec(m + 1); // Store armies of all players
  for (int p = 0; p <= m; p++) {
    scanf("%d\n", &xvec[p]);
  }
  std::vector<bool> anchor = convertToBinary(xvec[m]); // Fedor's army in binary
  int friends = 0;
  for (int p = 0; p < m; p++) {
    if (compareBinaryVectors(anchor, convertToBinary(xvec[p])) <= k) {
      ++friends; // Increment if Hamming distance is within limit
    }
  }
  printf("%d\n", friends);
  return 0;
}


// https://github.com/VaHiX/CodeForces/