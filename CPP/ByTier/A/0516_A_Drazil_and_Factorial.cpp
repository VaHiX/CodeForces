// Problem: CF 516 A - Drazil and Factorial
// https://codeforces.com/contest/516/problem/A

/*
 * Problem: Drazil and Factorial
 * 
 * Algorithm/Technique: 
 * - Precomputed mapping of digits to their factorial decompositions
 * - Greedily replace each digit with its factorial decomposition
 * - Sort the resulting digits in descending order to get the maximum number
 * 
 * Time Complexity: O(n * log(n)) where n is the number of digits in input
 *   - O(n) to process all digits and build the string
 *   - O(k * log(k)) to sort the resulting digits, where k is the total number of digits after decomposition
 *   - Since k <= 4 * n (as max decomposition is 4 digits), the overall complexity is O(n * log(n))
 * 
 * Space Complexity: O(n) for storing the decomposed digits string
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
string s, M[] = {"", "", "2", "3", "322", "5", "53", "7", "7222", "7332"};
long long a;
int main() {
  cin >> a >> a; // Read the number (unused in logic, but consumes input)
  while (a) {
    s += M[a % 10]; // Append factorial decomposition of last digit
    a /= 10;        // Move to next digit
  }
  sort(s.rbegin(), s.rend()); // Sort digits in descending order for maximum result
  cout << s; // Output the result
}


// https://github.com/VaHiX/CodeForces/