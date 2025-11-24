// Problem: CF 777 B - Game of Credit Cards
// https://codeforces.com/contest/777/problem/B

/*
 * Problem: Game of Credit Cards
 * 
 * Purpose: 
 *   Given two n-digit credit card numbers, Sherlock and Moriarty play a game where they 
 *   compare digits one by one. If a digit from Sherlock's card is smaller than Moriarty's,
 *   Sherlock gets a flick. Moriarty can reorder his digits to minimize his own flicks or
 *   maximize Sherlock's flicks.
 * 
 * Algorithm:
 *   - To find the minimum number of flicks Moriarty gets:
 *     Sort both strings. Use two pointers. For each digit in Sherlock's sorted string,
 *     try to match it with a digit from Moriarty's sorted string that is >= it.
 *     If such a digit exists, use it; otherwise, it results in a flick for Moriarty.
 *   - To find the maximum flicks Sherlock can get:
 *     Again, sort both strings. Use two pointers. For each digit in Sherlock's sorted string,
 *     try to match it with digits from Moriarty's sorted string that are > it to maximize flicks.
 * 
 * Time Complexity: O(n log n) - due to sorting, where n is the number of digits
 * Space Complexity: O(1) - only using fixed extra space (sorting in place)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int n, x;
  cin >> n;
  string s, ss;
  cin >> s >> ss;
  
  // Sort both strings to allow greedy matching
  sort(s.begin(), s.end());
  sort(ss.begin(), ss.end());
  
  // Find minimum flicks Moriarty gets
  int j = n - 1;  // Pointer for Moriarty's largest unused digit
  for (int i = n - 1; i >= 0; --i) {
    // If Moriarty's current largest digit is >= Sherlock's digit, use it
    if (ss[j] >= s[i])
      --j;
  }
  // j + 1 represents how many digits from Sherlock's string were not matched (i.e., flicks for Moriarty)
  cout << j + 1 << endl;
  
  // Reset j for next calculation (maximum flicks Sherlock can get)
  j = 0;
  for (int i = 0; i < n; i++) {
    // If Moriarty's digit is greater than Sherlock's current digit, increment Sherlock's flicks
    if (ss[i] > s[j])
      j++;
  }
  // j is the number of times Sherlock gets a flick
  cout << j << endl;
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/