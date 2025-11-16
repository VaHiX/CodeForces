// Problem: CF 949 A - Zebras
// https://codeforces.com/contest/949/problem/A

/*
Code Purpose:
This program determines whether a given binary string (representing days as 0 = bad, 1 = good) can be split into subsequences, each forming a "zebra" pattern.
A zebra is a subsequence that starts and ends with '0' and alternates between '0' and '1'.
The algorithm processes the string from left to right:
- For each '0', it either assigns it to an existing zebra (if possible) or starts a new one.
- For each '1', it must be assigned to an existing zebra that has a '0' as the last element.

Algorithms/Techniques:
- Greedy assignment of characters to subsequences.
- Maintains a list of active zebras, each represented as a vector of indices.
- Uses index tracking to determine when a zebra can be extended or closed.

Time Complexity: O(n), where n is the length of the input string.
Space Complexity: O(n), for storing the subsequences and indices.

*/
#include <cstdio>
#include <vector>
using namespace std;
int i, j, b, m, w;
char s[200200];
vector<int> v[200001]; // Vector of vectors to hold indices of each zebra
int main() {
  // Read input string into s starting from index 1
  for (scanf("%s", s + 1), m = b = 0, w = i = 1; w && s[i]; ++i)
    // If current character is '0', either start a new zebra or append to an existing one
    s[i] == '0' ? (v[b++].push_back(i), 1)
                : (--b < 0 ? w-- : (v[b].push_back(i), 1)),
        m < b && (m = b); // Keep track of maximum active zebras

  // Check if valid partitioning was achieved
  if (w && m == b)
    // If so, output the number of zebras and each zebra's indices
    for (printf("%d\n", m), i = 0; v[i].size(); puts(""), ++i)
      for (printf("%d", v[i].size()), j = 0; j != v[i].size(); ++j)
        printf(" %d", v[i][j]);
  else
    puts("-1"); // No valid partitioning found
}


// https://github.com/VaHiX/CodeForces/