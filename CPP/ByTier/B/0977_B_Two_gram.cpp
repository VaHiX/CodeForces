// Problem: CF 977 B - Two-gram
// https://codeforces.com/contest/977/problem/B

/*
 * Problem: Two-gram
 * Description: Find the most frequent two-gram (consecutive pair of characters) in a given string.
 * 
 * Algorithm:
 * 1. Iterate through the string and count occurrences of each two-gram.
 * 2. Keep track of the maximum count and the corresponding two-gram.
 * 
 * Time Complexity: O(n), where n is the length of the string.
 * Space Complexity: O(n), due to the map storing up to n-1 two-grams.
 * 
 * Techniques:
 * - Map for counting frequencies
 * - Linear scan of the string
 */

#include <iostream>
#include <map>
#include <string>
#include <utility>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 400
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d\n", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s\n", s)
#define pb push_back
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  string s, t = "##"; // t will hold the current two-gram being processed
  map<string, int> mp; // map to store frequency of each two-gram
  cin >> n >> s;
  
  // Loop through string to form all two-grams and count them
  for (i = 0; i < n - 1; i++) {
    t[0] = s[i];      // First character of two-gram
    t[1] = s[i + 1];  // Second character of two-gram
    mp[t]++;          // Increment frequency count
  }
  
  int mx = 0; // max frequency found so far
  map<string, int>::iterator itr = mp.begin();
  
  // Find the two-gram with maximum frequency
  while (itr != mp.end()) {
    if (itr->second >= mx) {
      mx = itr->second;
      t = itr->first; // update the result two-gram
    }
    itr++;
  }
  
  cout << t; // print the most frequent two-gram
  return 0;
}


// https://github.com/VaHiX/CodeForces/