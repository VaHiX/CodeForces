// Problem: CF 912 A - Tricky Alchemy
// https://codeforces.com/contest/912/problem/A

/*
Algorithm/Techniques: Greedy approach
Time Complexity: O(1) - Constant time operations
Space Complexity: O(1) - Only a constant amount of extra space is used

The problem involves determining the minimum number of additional crystals needed 
to produce a given number of yellow, green, and blue balls. Each ball type requires 
a specific combination of yellow and blue crystals. The solution computes the 
required total crystals for each color and compares it with the available ones, 
adding any deficit as additional crystals needed.
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
  int i, j, k;
  int n, m;
  ll A, B, t = 0; // A and B are the available yellow and blue crystals, t is the count of additional crystals needed
  ll x, y, z; // x, y, z are the required numbers of yellow, green, and blue balls respectively
  cin >> A >> B; // Read available crystals
  cin >> x >> y >> z; // Read required balls
  
  // Calculate additional yellow crystals needed
  // For x yellow balls, we need 2*x yellow crystals
  // For y green balls, we need 1*y yellow crystals
  // Total yellow crystals needed = 2*x + y
  // If we have less than that, we need to acquire the difference
  if (A < (2 * x + y))
    t += ((2 * x + y) - A);
  
  // Calculate additional blue crystals needed
  // For y green balls, we need 1*y blue crystals  
  // For z blue balls, we need 3*z blue crystals
  // Total blue crystals needed = y + 3*z
  // If we have less than that, we need to acquire the difference
  if (B < (y + 3 * z))
    t += ((3 * z + y) - B);
    
  cout << t; // Output the minimum number of additional crystals required
  return 0;
}


// https://github.com/VaHiX/CodeForces/