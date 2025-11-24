// Problem: CF 1861 C - Queries for the Array
// https://codeforces.com/contest/1861/problem/C

/* 
 * Problem: Check if a sequence of operations (+, -, 1, 0) on an array is valid.
 * 
 * Description:
 * - '+' adds an element to the array
 * - '-' removes the last element from the array
 * - '1' checks if the current array is sorted (non-descending)
 * - '0' checks if the current array is NOT sorted
 * 
 * Algorithm:
 * - Maintain the current length of the array
 * - Track the latest position where the array was sorted (latestsorted)
 * - Track the earliest position where the array was not sorted (earliestnonsorted)
 * - Validate operations against these constraints
 * 
 * Time Complexity: O(n) where n is the length of string s
 * Space Complexity: O(1) - only using a few variables
 */
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define pb push_back
#define mp make_pair
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    int currlen = 0; // Current length of the array
    int latestsorted = 1; // Position of latest sorted state (initially 1 to avoid edge case)
    int earliestnonsorted = 1e8; // Position of earliest non-sorted state (initially large)
    bool ok = true; // Flag to track if sequence is valid
    for (char c : s) {
      if (c == '+') {
        currlen++; // Increment length when adding element
      } else if (c == '-') {
        currlen--; // Decrement length when removing element
        if (currlen < 0)
          ok = false; // Can't remove from empty array
        latestsorted = min(latestsorted, currlen); // Update latest sorted position
        latestsorted = max(1, latestsorted); // Ensure it's at least 1
        if (currlen < earliestnonsorted) {
          earliestnonsorted = 1e8; // Reset non-sorted position if current is smaller
        }
      } else if (c == '1') {
        if (currlen >= earliestnonsorted) {
          ok = false; // If current length >= earliest non-sorted, it's not sorted
        }
        latestsorted = max(1, currlen); // Update latest sorted position
      } else if (c == '0') {
        if (currlen <= latestsorted) {
          ok = false; // If current length <= latest sorted, it's sorted
        }
        earliestnonsorted = min(earliestnonsorted, currlen); // Update earliest non-sorted position
      }
      if (!ok)
        break; // Early exit if invalid
    }
    if (ok)
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}


// https://github.com/VaHiX/CodeForces/