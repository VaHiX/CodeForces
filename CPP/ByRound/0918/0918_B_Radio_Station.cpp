// Problem: CF 918 B - Radio Station
// https://codeforces.com/contest/918/problem/B

/*
 * Code Purpose:
 * This program reads server names and their IP addresses, then processes
 * nginx configuration commands to append the corresponding server name as a comment.
 *
 * Algorithm:
 * 1. Store IP-to-name mapping in a std::map for O(log n) lookups.
 * 2. For each configuration command, extract the IP, look up the name, and print
 *    the command with the appended comment.
 *
 * Time Complexity: O(n * log n + m * log n)
 *   - Building the map takes O(n * log n) due to map insertions.
 *   - Processing m commands takes O(m * log n) for lookups.
 *
 * Space Complexity: O(n)
 *   - The map stores n key-value pairs.
 */

#include <iostream>
#include <map>
#include <string>

int main() {
  long n, m;
  std::cin >> n >> m;
  std::map<std::string, std::string> sl;  // Map to store IP -> server name
  while (n--) {
    std::string name, ip;
    std::cin >> name >> ip;
    sl[ip] = name;  // Store IP to name mapping
  }
  while (m--) {
    std::string command, ip;
    std::cin >> command >> ip;
    ip.erase(ip.size() - 1, 1);  // Remove semicolon from IP
    std::cout << command << " " << ip << "; #" << sl[ip] << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/