// Problem: CF 835 B - The number on the board
// https://codeforces.com/contest/835/problem/B

/*
 * Problem: Finding the minimum number of digit changes to make the sum of digits >= k
 * Algorithm: Greedy approach
 * Time Complexity: O(len(s) * log(len(s))) due to sorting
 * Space Complexity: O(1) excluding input storage
 *
 * Strategy:
 * 1. Calculate the current sum of digits in the number
 * 2. Sort digits in descending order to prioritize changing smaller digits to 9
 * 3. Greedily increase the sum by converting the smallest digits to 9 until sum >= k
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define inf 1000000000
#define pp pair<int, int>
using namespace std;

int main() {
  ll i, j, k;
  ll n, sum, count;
  string s;
  cin >> n >> s;  // Read target sum k and the string representation of number
  
  sum = 0;
  for (i = 0; i < s.length(); i++)
    sum += (s[i] - 48);  // Calculate initial sum of digits
  
  sort(s.begin(), s.end(), greater<char>());  // Sort digits in descending order to maximize gain per change
  
  count = 0;
  i = s.length() - 1;  // Start from the smallest digit (after sorting)
  while (n > sum) {    // While we haven't reached the required sum
    if (s[i] == '9')   // If it's already 9, skip it
      i--;
    else {
      k = 9 - s[i] + 48;  // Compute how much we need to increase to make it 9
      sum += k;           // Update the sum
      count++;            // Increment the count of changes
      i--;                // Move to next smaller digit
    }
  }
  cout << count;  // Output the minimum number of changes needed
  return 0;
}


// https://github.com/VaHiX/CodeForces/