// Problem: CF 527 C - Glass Carving
// https://codeforces.com/contest/527/problem/C

/*
C. Glass Carving
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
Leonid wants to become a glass carver (the person who creates beautiful artworks by cutting the glass). He already has a rectangular 
w
 mm 
 × 
 
h
 mm sheet of glass, a diamond glass cutter and lots of enthusiasm. What he lacks is understanding of what to carve and how.
In order not to waste time, he decided to practice the technique of carving. To do this, he makes vertical and horizontal cuts through the entire sheet. This process results in making smaller rectangular fragments of glass. Leonid does not move the newly made glass fragments. In particular, a cut divides each fragment of glass that it goes through into smaller fragments.
After each cut Leonid tries to determine what area the largest of the currently available glass fragments has. Since there appear more and more fragments, this question takes him more and more time and distracts him from the fascinating process.
Leonid offers to divide the labor — he will cut glass, and you will calculate the area of the maximum fragment after each cut. Do you agree?
Input
The first line contains three integers 
w
, 
h
, 
n
 (
2 ≤ 
w
, 
h
 ≤ 200 000
, 
1 ≤ 
n
 ≤ 200 000
).
Next 
n
 lines contain the descriptions of the cuts. Each description has the form 
H
 
y
 or 
V
 
x
. In the first case Leonid makes the horizontal cut at the distance 
y
 millimeters (
1 ≤ 
y
 ≤ 
h
 - 1
) from the lower edge of the original sheet of glass. In the second case Leonid makes a vertical cut at distance 
x
 (
1 ≤ 
x
 ≤ 
w
 - 1
) millimeters from the left edge of the original sheet of glass. It is guaranteed that Leonid won't make two identical cuts.
Output
After each cut print on a single line the area of the maximum available glass fragment in mm
2
.
Examples
Input
4 3 4
H 2
V 2
V 3
V 1
Output
8
4
4
2
Input
7 6 5
H 4
V 3
V 5
H 2
V 1
Output
28
16
12
6
4

Algorithm: 
Use two maps to store the frequencies of widths/heights (key: length, value: count), and maintain sets of cut positions.
When a cut is made:
 - Insert the position into appropriate set (pr for horizontal cuts, pc for vertical)
 - Find previous and next cut positions in the set
 - Remove old segment lengths from maps
 - Add new segment lengths to maps
 - Output max width * max height

Time Complexity: O(n log n) where n is number of operations due to set and map insert/remove.
Space Complexity: O(n) for storing segments in maps and sets.
*/

#include <stdint.h>
#include <cstdio>
#include <map>
#include <set>
#include <functional>
#include <utility>

int main() {
  long w, h, n;
  scanf("%ld %ld %ld\n", &w, &h, &n);
  std::map<int64_t, int64_t, std::greater<int64_t>> col, row; // Maps to store frequency of column and row lengths
  col[w] = 1;  // Initially the full width is one segment
  row[h] = 1;  // Initially the full height is one segment
  std::set<int64_t> pc, pr; // Sets to track cut positions: pc for vertical cuts, pr for horizontal cuts
  pc.insert(0);
  pc.insert(w);   // Insert initial boundaries
  pr.insert(0);
  pr.insert(h);   // Insert initial boundaries

  for (long p = 0; p < n; p++) {
    char orientation;
    long cut;
    scanf("%c %ld\n", &orientation, &cut);

    if (orientation == 'V') {  // Vertical cut
      pc.insert(cut);
      std::set<int64_t>::iterator setIter = pc.find(cut);
      int64_t t2 = *(++setIter);   // Next position after cut
      int64_t t1 = *(--(--setIter)); // Previous position before cut
      int64_t length = t2 - t1;    // Length of original segment

      --col[length];               // Remove the old segment from map
      if (col[length] <= 0) {
        col.erase(length);         // Clean up if count reaches zero
      }
      
      ++col[t2 - cut];             // Add new segments to map
      ++col[cut - t1];
    } else {
      pr.insert(cut);
      std::set<int64_t>::iterator setIter = pr.find(cut);
      int64_t t2 = *(++setIter);   // Next position after cut
      int64_t t1 = *(--(--setIter)); // Previous position before cut
      int64_t length = t2 - t1;    // Length of original segment

      --row[length];               // Remove the old segment from map
      if (row[length] <= 0) {
        row.erase(length);         // Clean up if count reaches zero
      }
      
      ++row[t2 - cut];             // Add new segments to map
      ++row[cut - t1];
    }

    // Print max area after each operation: maximum width * maximum height
    printf("%lld\n", (row.begin()->first) * (col.begin()->first));
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/