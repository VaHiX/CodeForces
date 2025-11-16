// Problem: CF 681 B - Economy Game
// https://codeforces.com/contest/681/problem/B

/*
 * Purpose: Determine if a given number n can be expressed as a sum of multiples
 *          of three specific values: 1234567 (houses), 123456 (cars), and 1234 (computers).
 *          This is essentially a 3-variable Diophantine equation problem:
 *          a * 1234567 + b * 123456 + c * 1234 = n
 *
 * Algorithm:
 * - Iterate through all possible numbers of houses (a) from 0 to n/1234567
 * - For each number of houses, iterate through all possible numbers of cars (b) from 0 to (n - a*1234567)/123456
 * - Compute remaining coins (z = n - a*1234567 - b*123456)
 * - Check if the remaining coins is divisible by 1234 (i.e., z % 1234 == 0)
 * - If such a combination exists, output "YES"
 * - If no such combination is found, output "NO"
 *
 * Time Complexity: O(n / 1234567 * n / 123456) which is approximately O(10^3 * 10^3) = O(10^6)
 * Space Complexity: O(1) - only using a constant amount of extra space
 */

#include <iostream>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define inf 1000000000
#define pp pair<char, char>
using namespace std;

int main() {
  ll i, j, k;
  ll n;
  ll x, y, z;
  cin >> n;
  x = n / 1234567;  // Maximum possible houses
  x++;              // Add 1 to include 0
  y = n / 123456;   // Maximum possible cars
  y++;              // Add 1 to include 0
  for (i = 0; i <= x; i++) {  // Loop through all possible numbers of houses
    for (j = 0; j <= y; j++) {  // Loop through all possible numbers of cars
      z = n - (i * 1234567) - (j * 123456);  // Calculate remaining coins
      if (z >= 0 && z % 1234 == 0) {         // Check if remaining coins can be bought with computers
        cout << "YES" << endl;
        return 0;
      }
    }
  }
  cout << "NO" << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/