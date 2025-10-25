// Problem: CF 1904 A - Forked!
// https://codeforces.com/contest/1904/problem/A

/*
 * Code Purpose:
 *   This code solves the problem of finding how many positions a modified knight
 *   (with move pattern (a,b) instead of standard (2,1)) can attack both the king and queen.
 *
 * Algorithms/Techniques:
 *   - Generate all possible knight moves from the king's position using the given (a,b) pattern.
 *   - Generate all possible knight moves from the queen's position using the same pattern.
 *   - Count the intersection of these two sets of positions.
 *
 * Time Complexity:
 *   O(1) per test case, as we generate exactly 8 moves for each piece regardless of input size.
 *
 * Space Complexity:
 *   O(1), since we store only a fixed number of positions (at most 16).
 */

#include <cstdio>
#include <set>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long xk, yk;
    scanf("%ld %ld", &xk, &yk);      // Read king's position
    long xq, yq;
    scanf("%ld %ld", &xq, &yq);      // Read queen's position
    
    std::set<std::pair<long, long>> s, t;  // Sets to store possible knight moves from king and queen
    
    // Generate all 8 possible knight moves from king's position (a,b pattern)
    s.insert(std::make_pair(xk + a, yk + b));
    s.insert(std::make_pair(xk - a, yk + b));
    s.insert(std::make_pair(xk + a, yk - b));
    s.insert(std::make_pair(xk - a, yk - b));
    s.insert(std::make_pair(xk + b, yk + a));
    s.insert(std::make_pair(xk - b, yk + a));
    s.insert(std::make_pair(xk + b, yk - a));
    s.insert(std::make_pair(xk - b, yk - a));
    
    // Generate all 8 possible knight moves from queen's position (a,b pattern)
    t.insert(std::make_pair(xq + a, yq + b));
    t.insert(std::make_pair(xq - a, yq + b));
    t.insert(std::make_pair(xq + a, yq - b));
    t.insert(std::make_pair(xq - a, yq - b));
    t.insert(std::make_pair(xq + b, yq + a));
    t.insert(std::make_pair(xq - b, yq + a));
    t.insert(std::make_pair(xq + b, yq - a));
    t.insert(std::make_pair(xq - b, yq - a));
    
    long cnt(0);
    // Count how many positions are common between the two sets (intersections)
    for (std::set<std::pair<long, long>>::iterator it = s.begin();
         it != s.end(); it++) {
      cnt += t.count(*it);  // Add 1 if the current position exists in both sets
    }
    
    printf("%ld\n", cnt);  // Output the count of forkable positions
  }
}


// https://github.com/VaHiX/codeForces/