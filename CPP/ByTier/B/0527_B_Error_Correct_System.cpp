// Problem: CF 527 B - Error Correct System
// https://codeforces.com/contest/527/problem/B

/*
 * Problem: B. Error Correct System
 * 
 * Purpose:
 *   This code finds the minimum Hamming distance between two strings S and T
 *   by swapping at most one pair of characters in string S.
 * 
 * Approach:
 *   1. Identify all positions where characters in S and T differ.
 *   2. For each differing position, store the characters from S and T.
 *   3. Try to reduce Hamming distance by swapping two characters in S:
 *      - If there exists a pair of differing positions that form a swap
 *        (i.e., S[i] == T[j] and S[j] == T[i]), a single swap reduces Hamming
 *        distance by 2.
 *      - Otherwise, check if swapping one character in S with another
 *        (that appears in T at a different position) reduces distance by 1.
 *   4. If no beneficial swap is found, output the original Hamming distance
 *      and "-1 -1".
 * 
 * Time Complexity: O(n)
 *   - The algorithm iterates through the strings a few times, with each
 *     iteration taking linear time.
 * 
 * Space Complexity: O(n)
 *   - Storing character positions and difference vectors requires space
 *     proportional to the length of the strings.
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define inf 1000000000
#define pp pair<char, char>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  int idx = -1, jdx = -1;
  string s, t;
  cin >> n >> s >> t;
  vector<int> sv[26];      // Store positions of each character in S
  vector<int> tv[26];      // Store positions of each character in T
  vector<char> sc;         // Characters from S where S[i] != T[i]
  vector<char> tc;         // Characters from T where S[i] != T[i]
  vector<int> v;           // Positions where S[i] != T[i]
  map<pp, bool> mp;        // Map to store pairs of differing chars
  int cnt = 0;
  
  // Identify differing positions and store data
  for (i = 0; i < n; i++) {
    if (s[i] != t[i]) {
      cnt++;
      sc.push_back(s[i]);
      sv[s[i] - 'a'].push_back(i + 1);
      v.push_back(i + 1);
      tc.push_back(t[i]);
      tv[t[i] - 'a'].push_back(i + 1);
      mp[{s[i], t[i]}] = 1;
    }
  }
  
  char x, y;
  // Check for a pair that if swapped reduces distance by 2
  for (i = 0; i < sc.size(); i++) {
    x = sc[i];
    y = tc[i];
    pp p = {y, x};
    if (mp[p]) {
      cout << cnt - 2 << endl;
      cout << v[i] << " ";
      for (j = 0; j < n; j++) {
        if (s[j] == y && t[j] == x) {
          cout << j + 1 << endl;
          return 0;
        }
      }
    }
  }
  
  // Check for a pair that if swapped reduces distance by 1
  for (i = 0; i < sc.size(); i++) {
    x = sc[i];
    y = tc[i];
    if (sv[y - 'a'].size() > 0) {
      cout << cnt - 1 << endl;
      cout << sv[y - 'a'][0] << " " << v[i] << endl;
      return 0;
    }
  }
  
  // If no beneficial swap found, output original distance and -1 -1
  cout << cnt << endl;
  cout << "-1 -1" << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/