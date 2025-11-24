// Problem: CF 1296 C - Yet Another Walking Robot
// https://codeforces.com/contest/1296/problem/C

/*
C. Yet Another Walking Robot
Algorithm: Using prefix sum technique with a map to track positions.
Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for storing positions in the map.

The problem asks us to find the shortest non-empty substring that can be removed 
such that the robot's final position remains unchanged. 

We use prefix sums to track the robot's location as we move through the string, 
and a map to store the first occurrence of each coordinate. If we revisit a coordinate, 
it means there's a cycle in the path — i.e., removing the substring between those two 
positions will not change the ending position.

We iterate through the string, updating coordinates and checking if the current 
position was seen before. If yes, we compute the length of the subarray between
the previous occurrence and the current one. We keep track of the smallest such
length.
*/

#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::map<std::pair<long, long>, long> m; // Map to store first occurrence of each position
    long x(0), y(0); // Current coordinates
    m[std::make_pair(0, 0)] = 0; // Initialize with starting point (0,0)
    long start(0), stop(0), len(1e9); // To store result indices and minimum length
    
    for (long p = 0; p < s.size(); p++) {
      // Update coordinates according to the move
      x += ((s[p] == 'R') - (s[p] == 'L'));
      y += ((s[p] == 'U') - (s[p] == 'D'));
      
      std::pair<long, long> pos = std::make_pair(x, y);
      
      // If we have been at this position before
      if (m.count(pos)) {
        long dist = (p + 1) - m[pos]; // Length of the subarray to remove
        if (dist < len) {
          len = dist;
          start = m[pos] + 1; // 1-based index
          stop = p + 1;       // 1-based index
        }
      }
      
      // Store the first occurrence of this position
      m[pos] = p + 1;
    }
    
    if (start && stop) {
      std::cout << start << " " << stop << std::endl;
    } else {
      std::cout << "-1" << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/