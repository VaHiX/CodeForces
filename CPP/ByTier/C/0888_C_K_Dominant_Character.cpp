// Problem: CF 888 C - K-Dominant Character
// https://codeforces.com/contest/888/problem/C

/*
 * Problem: C. K-Dominant Character
 * 
 * Purpose: Find the minimum k such that there exists at least one k-dominant character in the string.
 * A character c is k-dominant if every substring of length at least k contains c.
 * 
 * Approach:
 * 1. For each character, store all positions where it appears.
 * 2. For each character, calculate the maximum gap between consecutive occurrences,
 *    and also the distance from the start and end of the string.
 * 3. The minimum k is the smallest such maximum gap across all characters.
 * 
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(n) for storing positions of characters.
 * 
 * Algorithms/Techniques: 
 * - Greedy approach with prefix/postfix distances
 * - Character grouping and gap calculation
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 200000
#define inf 1000000
#define pp pair<int, int>
using namespace std;

vector<int> v[26]; // Store positions of each character (a-z)
int dist[26];      // Store the maximum gap for each character

int main() {
  int i, j, k;
  int n, m;
  string s;
  
  memset(dist, 0, sizeof(dist)); // Initialize distances to 0
  cin >> s;
  
  // Store positions of each character
  for (i = 0; i < s.length(); i++) {
    v[s[i] - 'a'].push_back(i + 1); // Store 1-based positions
  }
  
  n = s.length();
  
  // For each character, compute the maximum gap between its occurrences
  for (i = 0; i < 26; i++) {
    if (!v[i].size()) {
      dist[i] = inf; // Character not present
      continue;
    }
    
    m = v[i].size();
    
    // Compute max gap: between consecutive positions, and from start/end
    dist[i] = max(v[i][0], n - v[i][m - 1] + 1); // Gap from beginning or end
    
    for (j = 1; j < m; j++)
      dist[i] = max(dist[i], v[i][j] - v[i][j - 1]); // Gap between consecutive positions
  }
  
  // Find minimum among all character gaps
  m = dist[0];
  for (i = 1; i < 26; i++)
    m = min(m, dist[i]);
    
  printf("%d\n", m);
  return 0;
}


// https://github.com/VaHiX/CodeForces/