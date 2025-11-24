// Problem: CF 785 A - Anton and Polyhedrons
// https://codeforces.com/contest/785/problem/A

/*
 * Problem: Anton and Polyhedrons
 * Purpose: Calculate the total number of faces from a collection of regular polyhedrons.
 * Algorithm: Use a map to store the number of faces for each polyhedron type.
 *            Read input polyhedron names and accumulate their face counts.
 * Time Complexity: O(n), where n is the number of polyhedrons.
 * Space Complexity: O(1), since the map size is fixed (5 entries).
 */

#include <iostream>
#include <map>
#include <string>

int main() {
  // Map to store the number of faces for each polyhedron
  std::map<std::string, long> m;
  m["Tetrahedron"] = 4;     // Tetrahedron has 4 triangular faces
  m["Cube"] = 6;            // Cube has 6 square faces
  m["Octahedron"] = 8;      // Octahedron has 8 triangular faces
  m["Dodecahedron"] = 12;   // Dodecahedron has 12 pentagonal faces
  m["Icosahedron"] = 20;    // Icosahedron has 20 triangular faces

  // Disable synchronization between C and C++ standard streams for faster I/O
  std::ios_base::sync_with_stdio(false);

  long n;
  std::cin >> n;  // Read number of polyhedrons
  long total(0);  // Initialize total face count

  // Process each polyhedron
  while (n--) {
    std::string s;
    std::cin >> s;           // Read the name of the polyhedron
    total += m[s];           // Add the number of faces for this polyhedron to the total
  }

  std::cout << total << std::endl;  // Output the total number of faces
  return 0;
}


// https://github.com/VaHiX/CodeForces/