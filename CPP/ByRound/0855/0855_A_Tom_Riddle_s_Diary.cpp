// Problem: CF 855 A - Tom Riddle's Diary
// https://codeforces.com/contest/855/problem/A

/*
Purpose: This code determines whether each person in a list has previously possessed a diary.
         For each name in the input, it checks if that name has appeared earlier in the list.
         If so, it outputs "YES", otherwise "NO".

Algorithms/Techniques: 
    - Use of a hash map (std::map) to store previously seen names.
    - For each new name, check if it exists in the map.
    - If not present, print "NO" and insert the name into the map.
    - If present, print "YES" and increment the count in the map.

Time Complexity: O(n * log n), where n is the number of names. 
                   Each map operation (insert, find) takes O(log n) time.

Space Complexity: O(n), as we store at most n names in the map.
*/

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
#define mod 1000000007
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  string s;
  scanf("%d%d", &n); // Read number of names
  map<string, int> mp; // Map to track seen names
  while (n--) {
    cin >> s; // Read current name
    if (!mp[s]) // If name hasn't been seen before
      cout << "NO" << endl;
    else
      cout << "YES" << endl;
    mp[s]++; // Increment count of the name in map
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/