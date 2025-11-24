// Problem: CF 1609 C - Complex Market Analysis
// https://codeforces.com/contest/1609/problem/C

/*
 * Problem: Complex Market Analysis
 * 
 * Algorithm: 
 * - For each element in the array, if it is a prime number, we consider it as a potential starting point (i).
 * - From that point, we extend the sequence in both directions (forward and backward) as long as the elements are 1.
 * - For each valid sequence of 1s extending from a prime number, we count the number of valid subarrays that can be formed.
 * - We use a mathematical formula to calculate the combinations efficiently:
 *   Let 'l' be the number of 1s to the left of the prime, and 'r' be the number of 1s to the right.
 *   Total valid pairs = l + r + l * r
 * 
 * Time Complexity: O(n * sqrt(max_a)) where max_a is the maximum value in the array.
 * Space Complexity: O(n) for the input array.
 */
#include <iostream>

#define ll long long
using namespace std;

// Function to check if a number is prime
bool prost(int n) {
  if (n == 1)
    return false;
  for (int i = 2; i * i <= n; i++)
    if (n % i == 0)
      return false;
  return true;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    int a[n];
    long long s = 0;
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++) {
      // Check if current element is prime
      if (prost(a[i])) {
        long long r = 1, l = 1;
        // Count consecutive 1s to the right of current prime
        while (r * k + i < n && a[r * k + i] == 1)
          r++;
        // Count consecutive 1s to the left of current prime
        while (i - l * k >= 0 && a[i - l * k] == 1)
          l++;
        l--;
        r--;
        // Add the number of combinations to the total count
        s += l + r + l * r;
      }
    }
    cout << s << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/