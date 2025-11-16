// Problem: CF 827 A - String Reconstruction
// https://codeforces.com/contest/827/problem/A

/*
Algorithm/Technique:
- This problem uses a greedy approach to reconstruct the lexicographically minimal string.
- For each position in the final string, we determine what character should be placed there.
- We track the "farthest" position that any given string can cover starting from a certain index.
- By scanning from left to right and choosing the character that satisfies all constraints with minimal lexicographical value, we build the solution.
- Time Complexity: O(sum of all k_i + max_position), where sum of k_i is bounded by 10^6
- Space Complexity: O(max_position), as we store information up to the maximum position needed

*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <utility>

using namespace std;
const int MAXN = 2e6 + 10;
char s[MAXN]; // Stores all strings concatenated together
int len[MAXN], ss[MAXN]; // len[i] = length of string i, ss[i] = start index of string i in s
char an[MAXN]; // Resultant minimal string
int max_n; // Maximum position needed in final string
int st = 0; // Current start index in s
pair<int, int> d[MAXN]; // d[i] stores {length of string, index of string} that covers position i

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", s + st); // Read string t_i
    ss[i] = st; // Store start position of string i in s
    len[i] = strlen(s + st); // Store length of string i
    st += len[i]; // Update start for next string
    int m;
    scanf("%d", &m); // Read number of occurrences of string i
    for (int j = 0; j < m; j++) {
      int x;
      scanf("%d", &x); // Read occurrence position
      max_n = max(max_n, x + len[i] - 1); // Update max_n to reflect the furthest reach of this occurrence
      d[x] = max(d[x], make_pair(len[i], i)); // Store the longest string that starts at position x
    }
  }
  int far = 0, from = -1, id = -1; // far = furthest covered position, from = start of current segment, id = index of active string
  for (int i = 1; i < max_n + 1; i++) { // Scan each position from 1 to max_n
    if (d[i].first + i - 1 > far) { // If a new more far-reaching string starts at position i
      from = i; // Update the start of this segment
      far = d[i].first + i - 1; // Update farthest reach
      id = d[i].second; // Update the string index
    }
    if (far < i) // If no string covers this position
      an[i] = 'a'; // Place the smallest character 'a'
    else {
      an[i] = s[ss[id] + i - from]; // Select character from the longest covering string
    }
  }
  puts(an + 1); // Output result, skipping index 0
  return 0;
}


// https://github.com/VaHiX/CodeForces/