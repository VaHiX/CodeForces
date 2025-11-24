// Problem: CF 734 D - Anton and Chess
// https://codeforces.com/contest/734/problem/D

/*
 * Code purpose: Determine if a white king on an infinite chessboard is under attack (in check) 
 *               by any of the black pieces (rooks, bishops, or queens).
 * 
 * Algorithm:
 * - The board is infinite, but we only care about pieces that could potentially attack the king.
 * - We classify pieces into 8 diagonal/orthogonal directions relative to the king's position.
 * - For each of these 8 directions, we store the closest piece and whether it can attack (i.e. is a queen or the right type).
 * - Then we check if any of these closest pieces can attack the king.
 * 
 * Time Complexity: O(n log n) due to sorting the 8 directional lists.
 * Space Complexity: O(n) for storing the directional lists.
 */
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  long kx, ky;
  std::cin >> kx >> ky;
  // Calculate the diagonal constants for the king's position
  long dk(ky - kx), sk(kx + ky);
  // Create 8 directional lists to store pieces in each direction
  // Each list stores {distance, is-attackable}, where attackable means
  // the piece can attack the king in that diagonal/orthogonal path.
  std::vector<std::pair<long, bool>> nw, nn, ne, ee, se, ss, sw, ww;
  while (n--) {
    char t;
    long x, y;
    std::cin >> t >> x >> y;
    // Check if piece is on the NW diagonal (y - x = ky - kx)
    if (y - x == dk && x > kx) {
      nw.push_back(std::make_pair(x - kx, (t == 'B' || t == 'Q')));
    }
    // Check if piece is on the SE diagonal (y - x = ky - kx)
    if (y - x == dk && x < kx) {
      se.push_back(std::make_pair(kx - x, (t == 'B' || t == 'Q')));
    }
    // Check if piece is on the SW diagonal (y + x = kx + ky)
    if (y + x == sk && x > kx) {
      sw.push_back(std::make_pair(x - kx, (t == 'B' || t == 'Q')));
    }
    // Check if piece is on the NE diagonal (y + x = kx + ky)
    if (y + x == sk && x < kx) {
      ne.push_back(std::make_pair(kx - x, (t == 'B' || t == 'Q')));
    }
    // Check if piece is on the same row to the left of king
    if (y == ky && x > kx) {
      ww.push_back(std::make_pair(x - kx, (t == 'R' || t == 'Q')));
    }
    // Check if piece is on the same row to the right of king
    if (y == ky && x < kx) {
      ee.push_back(std::make_pair(kx - x, (t == 'R' || t == 'Q')));
    }
    // Check if piece is on the same column above king
    if (x == kx && y > ky) {
      nn.push_back(std::make_pair(y - ky, (t == 'R' || t == 'Q')));
    }
    // Check if piece is on the same column below king
    if (x == kx && y < ky) {
      ss.push_back(std::make_pair(ky - y, (t == 'R' || t == 'Q')));
    }
  }
  // Sort each directional list by distance (ascending)
  sort(nw.begin(), nw.end());
  sort(nn.begin(), nn.end());
  sort(ne.begin(), ne.end());
  sort(ee.begin(), ee.end());
  sort(se.begin(), se.end());
  sort(ss.begin(), ss.end());
  sort(sw.begin(), sw.end());
  sort(ww.begin(), ww.end());
  // Check if any of the closest pieces in the 8 directions is attacking
  bool check = (!nw.empty() && nw[0].second) || (!nn.empty() && nn[0].second) ||
               (!ne.empty() && ne[0].second) || (!ee.empty() && ee[0].second) ||
               (!se.empty() && se[0].second) || (!ss.empty() && ss[0].second) ||
               (!sw.empty() && sw[0].second) || (!ww.empty() && ww[0].second);
  puts(check ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/