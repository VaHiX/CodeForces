// Problem: CF 714 C - Sonya and Queries
// https://codeforces.com/contest/714/problem/C

/*
Purpose: This code handles a multiset of integers with operations to add, remove, and query integers based on a parity pattern.
         The pattern matching is done by converting integers to a binary string where 0 represents even digits and 1 represents odd digits.
         The implementation uses a map to store the count of integers matching each pattern.

Algorithms/Techniques:
- Use of map to store pattern strings and their counts
- Pattern generation by checking digit parity (even = 0, odd = 1)
- Padding strings to 18 digits for consistent pattern matching

Time Complexity: O(t * log t) where t is the number of queries. 
                 Each map operation (insert, delete, lookup) takes O(log t) time.

Space Complexity: O(t * 18) = O(t), since each pattern is of length 18 and we store at most t patterns.
*/
#include <iostream>
#include <map>
#include <string>

typedef long long int ll;
#define pp pair<string, ll>
#define dbg printf("f");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;
int main() {
  ll i, j, k;
  ll n;
  char ch;
  string a;
  map<string, ll> mp; // Map to store pattern -> count of integers matching that pattern
  cin >> n;
  ll lagbe;
  for (j = 0; j < n; j++) {
    string s;
    cin >> ch >> a;
    lagbe = 18 - a.length(); // Calculate padding needed to make string 18 digits long
    for (i = 0; i < lagbe; i++)
      s.push_back('0'); // Pad with leading zeros
    k = 0;
    for (i = lagbe; i <= 18; i++) {
      if ((a[k] - 48) % 2 == 0) // Check if digit is even
        s.push_back('0');
      else
        s.push_back('1'); // Check if digit is odd
      k++;
    }
    if (ch == '+')
      mp[s]++; // Increment count for matching pattern
    else if (ch == '-')
      mp[s]--; // Decrement count for matching pattern
    else
      cout << mp[s] << endl; // Print count of integers matching the pattern
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/