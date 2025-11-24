// Problem: CF 690 F1 - Tree of Life (easy)
// https://codeforces.com/contest/690/problem/F1

/*
F1. Tree of Life (easy)
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
Heidi has finally found the mythical Tree of Life – a legendary combinatorial structure which is said to contain a prophecy crucially needed to defeat the undead armies.
On the surface, the Tree of Life is just a regular undirected tree well-known from computer science. This means that it is a collection of 
n
 points (called vertices), some of which are connected using 
n
 - 1
 line segments (edges) so that each pair of vertices is connected by a 
path
 (a sequence of one or more edges).
To decipher the prophecy, Heidi needs to perform a number of steps. The first is counting the number of 
lifelines
 in the tree – these are paths of length 
2
, i.e., consisting of two edges. Help her!
Input
The first line of the input contains a single integer 
n
 – the number of vertices in the tree (
1 ≤ 
n
 ≤ 10000
). The vertices are labeled with the numbers from 1 to 
n
. Then 
n
 - 1
 lines follow, each describing one edge using two space-separated numbers 
a
 
b
 – the labels of the vertices connected by the edge (
1 ≤ 
a
 < 
b
 ≤ 
n
). It is guaranteed that the input represents a tree.
Output
Print one integer – the number of lifelines in the tree.
Examples
Input
4
1 2
1 3
1 4
Output
3
Input
5
1 2
2 3
3 4
3 5
Output
4
Note
In the second sample, there are four lifelines: paths between vertices 
1
 and 
3
, 
2
 and 
4
, 
2
 and 
5
, and 
4
 and 
5
.

Algorithms/Techniques:
- Count degree of each node in a tree.
- For each node with degree d, the number of paths of length 2 passing through it is C(d, 2) = d*(d-1)/2.
- Sum all such values to get total number of lifelines.
Time Complexity: O(n)
Space Complexity: O(n)

*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> d(n + 1, 0); // d[i] stores degree of vertex i
  for (long p = 1; p < n; p++) { // process n-1 edges
    long x, y;
    scanf("%ld %ld", &x, &y);
    ++d[x]; // increment degree of x
    ++d[y]; // increment degree of y
  }
  long total(0);
  for (long p = 1; p <= n; p++) {
    total += d[p] * (d[p] - 1) / 2; // add C(d[p], 2) to total
  }
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/