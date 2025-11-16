// Problem: CF 1144 B - Parity Alternated Deletions
// https://codeforces.com/contest/1144/problem/B

/*
B. Parity Alternated Deletions
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
Polycarp has an array a consisting of n integers.
He wants to play a game with this array. The game consists of several moves. On the first move he chooses any element and deletes it (after the first move the array contains n-1 elements). For each of the next moves he chooses any element with the only restriction: its parity should differ from the parity of the element deleted on the previous move. In other words, he alternates parities (even-odd-even-odd-... or odd-even-odd-even-...) of the removed elements. Polycarp stops if he can't make a move.
Formally: 
 
 If it is the first move, he chooses any element and deletes it; 
 If it is the second or any next move: 
 
if the last deleted element was 
odd
, Polycarp chooses any 
even
 element and deletes it; 
if the last deleted element was 
even
, Polycarp chooses any 
odd
 element and deletes it. 
 
If after some move Polycarp cannot make a move, the game ends. 
Polycarp's goal is to 
minimize
 the sum of 
non-deleted
 elements of the array after end of the game. If Polycarp can delete the whole array, then the sum of 
non-deleted
 elements is zero.
Help Polycarp find this value.

Algorithms/Techniques: Greedy approach with sorting
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing odd and even numbers
*/

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 2500
#define inf 1e18
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<ll, ll>
using namespace std;

int main() {
  int i, j, k;
  int n, m, sum = 0, sum2;
  sf(n);
  vector<int> odd, even; // Separate odd and even numbers
  for (i = 0; i < n; i++) {
    sf(m);
    if (m % 2) // If number is odd
      odd.pb(m);
    else
      even.pb(m); // If number is even
    sum += m; // Keep track of total sum
  }
  sort(odd.begin(), odd.end(), greater<int>()); // Sort odds in descending order
  sort(even.begin(), even.end(), greater<int>()); // Sort evens in descending order
  int mn = sum; // Initialize minimum with total sum
  k = 1, i = 0, j = 0, sum2 = sum;
  // Try starting with odd number first
  while (true) {
    if (odd.size() && k && i < odd.size()) // If there are odds left and we want to pick an odd number
      sum2 -= odd[i], i++;
    else if (even.size() && !k && j < even.size()) // If there are evens left and we want to pick an even number
      sum2 -= even[j], j++;
    else
      break;
    k = 1 - k; // Alternate between picking odds and evens
  }
  mn = min(mn, sum2); // Update minimum sum
  k = 0, i = 0, j = 0, sum2 = sum;
  // Try starting with even number first
  while (true) {
    if (odd.size() && k && i < odd.size()) // If there are odds left and we want to pick an odd number
      sum2 -= odd[i], i++;
    else if (even.size() && !k && j < even.size()) // If there are evens left and we want to pick an even number
      sum2 -= even[j], j++;
    else
      break;
    k = 1 - k; // Alternate between picking odds and evens
  }
  mn = min(mn, sum2); // Update minimum sum
  pf(mn); // Print the result
  return 0;
}


// https://github.com/VaHiX/codeForces/