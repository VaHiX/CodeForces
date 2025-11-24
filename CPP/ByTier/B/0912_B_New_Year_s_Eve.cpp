// Problem: CF 912 B - New Year's Eve
// https://codeforces.com/contest/912/problem/B

/*
Purpose: To find the maximum possible XOR-sum of at most k candies chosen from n candies labeled from 1 to n.
Algorithm: The key insight is that to maximize XOR, we want to set as many bits as possible to 1 from the most significant bit downward.
           If we can select up to k candies, we aim to construct the largest number possible in terms of bit representation.
           The maximum XOR is achieved by selecting numbers such that the result is all 1s up to a certain bit.
           If k >= 2, we can always achieve the maximum possible XOR which is 2^b - 1 where b is the highest bit such that 2^b - 1 < n.
           Special case: if k == 1, return n directly.

Time Complexity: O(log n) due to the while loop that processes bits.
Space Complexity: O(1) as only a constant amount of extra space is used.
*/

#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 200
#define inf 10000000000
#define pp pair<char, int>
using namespace std;

int main() {
  ll i, j, k;
  ll n, m;
  cin >> n >> k;
  
  // If only one candy can be taken, the best choice is the candy with the highest label (n)
  if (k == 1) {
    cout << n;
    return 0;
  }
  
  // Find the smallest power of 2 minus 1 that is >= n
  // This gives us the maximum possible XOR value for any subset of size <= k
  m = 1;
  while (m < n) {
    m = 2 * m + 1;  // Keep doubling and adding 1 to get next number like 1, 3, 7, 15, ...
  }
  
  cout << m;
  return 0;
}


// https://github.com/VaHiX/CodeForces/