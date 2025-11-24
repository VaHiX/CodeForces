// Problem: CF 525 A - Vitaliy and Pie
// https://codeforces.com/contest/525/problem/A

/*
Code Purpose:
This program determines the minimum number of keys Vitaly needs to buy to guarantee reaching the n-th room 
in a house where each room contains a key and each door between rooms requires a specific key to open.

Algorithm:
- Use a map to track available keys (lowercase letters).
- Traverse the string s which represents keys and doors in alternating positions.
- For each door (uppercase letter), check if a matching key (lowercase) is available:
  - If yes, decrement key count.
  - If no, increment the required key purchase count.
- For each key (lowercase letter), increment the key count in the map.

Time Complexity: O(n) where n is the length of the string s (2*n - 2).
Space Complexity: O(1) since the map stores at most 26 lowercase letters.
*/

#include <ctype.h>
#include <iostream>
#include <map>
#include <string>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("f");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n, count = 0; // count tracks how many additional keys are needed
  map<char, ll> lil; // map to store available keys
  string s;
  cin >> n >> s;
  char ch;
  for (i = 0; i < s.length(); i++) {
    if (isupper(s[i]) == 1) {
      // Process a door (uppercase letter)
      ch = tolower(s[i]); // Get matching key type
      if (lil[ch] > 0)
        lil[ch]--; // Use one key if available
      else
        count++; // Need to buy this key
    } else
      lil[s[i]]++; // Add the key we found to our collection
  }
  cout << count;
  return 0;
}


// https://github.com/VaHiX/CodeForces/