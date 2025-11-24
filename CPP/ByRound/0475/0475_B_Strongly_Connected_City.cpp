// Problem: CF 475 B - Strongly Connected City
// https://codeforces.com/contest/475/problem/B

/*
 * Code Purpose: Determine if all junctions in a city grid are reachable from each other
 *               based on given directions for horizontal and vertical streets.
 *
 * Algorithm/Techniques: 
 *   - The problem reduces to checking if there exists a cycle in the directed graph
 *     formed by the street directions such that all nodes (junctions) are connected.
 *   - A key observation is that for full connectivity, it's sufficient to check
 *     if the corner directions form a valid cycle pattern. Specifically, checking
 *     the pattern formed by the first horizontal, first vertical, last horizontal,
 *     and last vertical street directions.
 *
 * Time Complexity: O(n + m), where n is the number of horizontal streets and m is vertical.
 * Space Complexity: O(1), constant extra space used.
 */

#include <cstdio>
#include <iostream>
#include <string>
int main() {
  int n, m;
  scanf("%d %d\n", &n, &m);
  std::string horizontal;
  getline(std::cin, horizontal);
  std::string vertical;
  getline(std::cin, vertical);
  // Construct a cycle string from the directions of the first and last streets
  std::string cycle = std::string("") + horizontal[0] + vertical[0] +
                      horizontal[n - 1] + vertical[m - 1];
  // Check for valid connectivity patterns
  if (cycle == "<v>^" || cycle == ">^<v") {
    puts("YES");
  } else {
    puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/