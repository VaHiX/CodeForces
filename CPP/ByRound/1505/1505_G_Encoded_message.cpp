// Problem: CF 1505 G - Encoded message
// https://codeforces.com/contest/1505/problem/G

/*
G. Encoded message
Algorithm: Map-based decoding of 5-digit sequences.
Each input line represents a 5-digit number formed by concatenating 5 integers (each between 0-2 or 0-3).
These numbers are mapped to unique lowercase letters from 'a' to 'z'.
The mapping is built by processing the first 26 unique numbers in order and assigning them letters 'a' through 'z'.
Time Complexity: O(N + M), where N is the number of inputs (26) and M is the number of queries.
Space Complexity: O(1), since the map size is bounded by a constant (26).
*/

#include <cstdio>
#include <map>
int main() {
  long num[] = {10010, 11020, 20011, 21012, 11011, 21021, 22022, 12021, 11011,
                12012, 10120, 11130, 20121, 21122, 11121, 21131, 22132, 12131,
                11121, 12122, 10221, 11231, 12113, 20222, 21223, 11222};
  std::map<long, char> m; // Map to store unique numbers and their corresponding letters
  for (long p = 0; p < 26; p++) {
    if (m[num[p]]) { // If the number is already mapped, skip it
      continue;
    }
    m[num[p]] = 'a' + p; // Assign letter 'a' to 'z' based on position
  }
  long t;
  scanf("%ld", &t); // Read number of test cases
  while (t--) {
    long cur(0);
    for (long p = 0; p < 5; p++) {
      long s;
      scanf("%ld", &s), cur = cur * 10 + s; // Build the 5-digit number from input
    }
    printf("%c", m[cur]); // Print the corresponding letter
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/