// Problem: CF 2168 A2 - Encode and Decode (Hard Version)
// https://codeforces.com/contest/2168/problem/A2

/*
Purpose: 
  This code implements a run-twice encoding/decoding strategy for an array of integers.
  In the first run (encoding), it converts an array of integers into a string of lowercase letters.
  In the second run (decoding), it reconstructs the original array from that string.
  
Algorithm:
  Encoding:
    - Each integer is encoded using a base-25 representation (where 'a' = 0, ..., 'y' = 24).
    - A 'z' is appended after each encoded number to mark the end of that number.
  Decoding:
    - The string is parsed to find 'z' markers.
    - For each segment between 'z's, the base-25 number is reconstructed and output.
    
Time Complexity: O(n * log(max(a_i))) for encoding and O(|s|) for decoding.
Space Complexity: O(|s|) for storing the encoded string and temporary variables.
*/

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define ll long long
#define all(v) (v).begin(), (v).end()
const ll mod = 1e9 + 7;
const ll INF = LLONG_MAX >> 1;

void solve(ll tt = 0) {
  string s;
  cin >> s;
  
  // First run: encoding
  if (s.front() == 'f') {
    ll n;
    cin >> n;
    vector<ll> arr(n);
    for (auto &i : arr)
      cin >> i;
    
    // Encode each number in the array
    for (ll i = 0; i < n; i++) {
      ll curr = arr[i];
      // Convert number to base-25 using letters 'a' to 'y'
      while (curr) {
        cout << (char)('a' + (curr % 25));
        curr /= 25;
      }
      // Mark end of current number with 'z'
      cout << 'z';
    }
    cout << endl;
  } else {
    // Second run: decoding
    cin >> s;
    ll n = s.size();
    ll count = 0;
    // Count number of 'z's to find how many numbers were encoded
    for (char c : s)
      count += (c == 'z');
    
    cout << count << '\n';
    
    string t = "";
    // Process the string to extract each encoded number
    for (ll i = 0; i < n; i++) {
      ll curr = 0;
      if (s[i] == 'z') {
        // Convert the accumulated letters back to base-25 integer
        ll mult = 1;
        ll ans = 0;
        for (ll i = 0; i < t.size(); i++) {
          ans += mult * (t[i] - 'a');
          mult *= 25;
        }
        cout << ans << " ";
        t = "";
      } else {
        // Accumulate characters until we hit a 'z'
        t += s[i];
      }
    }
    cout << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t = 1;
  for (ll i = 1; i <= t; i++)
    solve(i);
}


// https://github.com/VaHiX/CodeForces/