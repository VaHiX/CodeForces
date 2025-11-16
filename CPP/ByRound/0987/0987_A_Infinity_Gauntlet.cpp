// Problem: CF 987 A - Infinity Gauntlet
// https://codeforces.com/contest/987/problem/A

/**
 * Problem: Infinity Gauntlet
 * 
 * Purpose: Given the colors of gems currently in the Infinity Gauntlet,
 * determine which of the six gems are missing. Each color maps to a specific
 * gem name. We use a map to store the mapping and then iterate through the
 * input to mark which gems are present. Finally, we output the names of
 * the gems that are not marked as present.
 * 
 * Algorithm:
 * 1. Create a mapping from gem colors to gem names.
 * 2. Read the number of gems present (n).
 * 3. For each of the n gems, mark its corresponding gem name as "khan" in the map.
 * 4. Iterate through the map and print all gem names that are not marked as "khan".
 * 
 * Time Complexity: O(n), where n is the number of gems present (at most 6).
 * Space Complexity: O(1), since the map size is fixed (6 entries) and no extra space grows with input.
 */

#include <iostream>
#include <map>
#include <string>
#include <utility>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 50700
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s", s)
#define pb push_back
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  string s;
  // Map color to gem name
  map<string, string> mp;
  mp["purple"] = "Power";
  mp["green"] = "Time";
  mp["blue"] = "Space";
  mp["orange"] = "Soul";
  mp["red"] = "Reality";
  mp["yellow"] = "Mind";
  
  cin >> n;
  m = 6 - n; // Number of missing gems
  cout << m << endl;
  
  // Mark the gems that are present
  for (i = 0; i < n; i++) {
    cin >> s;
    mp[s] = "khan"; // Mark as present
  }
  
  // Print the gems that are not marked as present
  auto itr = mp.begin();
  while (itr != mp.end()) {
    if (itr->second != "khan")
      cout << itr->second << endl;
    itr++;
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/