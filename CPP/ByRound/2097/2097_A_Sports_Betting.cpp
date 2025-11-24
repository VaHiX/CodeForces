// Problem: CF 2097 A - Sports Betting
// https://codeforces.com/contest/2097/problem/A

/*
Code Purpose:
This code determines whether Vadim can guarantee winning at least one bet among n students,
based on the days they placed their bets. The key idea is to check if there exists at least one 
sequence of three consecutive days where all days are equal, meaning Vadim can predict that 
boardings will be the same for those three days, ensuring at least one correct prediction.

Algorithms/Techniques:
- Sorting the array of bet days.
- Iterating through sorted array to find if there exists a subsequence of 3 equal elements or
  patterns where predictions align with required constraints (i.e., 2 or more consecutive days match,
  and next is at least 2 larger to allow valid strategy).

Time Complexity: O(n log n) due to sorting, where n is the number of students.
Space Complexity: O(n) for storing the array of bet days.

*/

#include <iostream>
#include <algorithm>

#define ll long long
#define ull unsigned long long
using namespace std;

ll arr[1000007]; // Array to store the days on which students placed their bets
ll t, n, ans;    // Variables for number of test cases, number of students, and answer counter

int main() {
  ios_base::sync_with_stdio(false); // Optimize I/O speed
  cin.tie(nullptr);                 // Untie cin from cout for faster input

  cin >> t; // Read number of test cases
  while (t--) { // Process each test case
    cin >> n; // Read number of students for current test case
    
    for (int i = 1; i <= n; i++) {
      cin >> arr[i]; // Read the days on which bets were placed
    }
    
    sort(arr + 1, arr + n + 1); // Sort the array to facilitate checking consecutive elements
    
    ans = 0; // Reset counter for checking valid prediction sequence
    
    for (int i = 2; i <= n; i++) {
      if (arr[i] == arr[i - 1]) { // If current day equals previous day
        ans++; // Increment count of matching days
        
        if (ans == 2) // If we found two matches, then we have a sequence of 3 equal elements
          break;    // Valid strategy possible
        
        if (arr[i + 1] >= arr[i] + 2) // If next day is more than 2 ahead
          ans = 0; // Reset counter as it breaks the sequence of valid matches
          
        i++; // Skip one index since we checked two elements already
        continue;
      }
      
      if (arr[i] >= arr[i - 1] + 2) // If current day is more than 2 ahead of previous day
        ans = 0; // Reset match count as the sequence breaks
    }
    
    if (ans == 2) // If we found at least one pair of matches that form a valid triplet
      cout << "YES" << endl; // Guaranteed to win at least one bet
    else
      cout << "NO" << endl; // Cannot guarantee winning any bet
  }

  return 0;
}


// https://github.com/VaHiX/codeForces/