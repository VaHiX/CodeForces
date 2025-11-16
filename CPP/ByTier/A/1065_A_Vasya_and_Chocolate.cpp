// Problem: CF 1065 A - Vasya and Chocolate
// https://codeforces.com/contest/1065/problem/A

/*
 * Problem: Vasya and Chocolate
 * 
 * Purpose: To calculate the maximum number of chocolate bars Vasya can obtain
 *          given a special offer where buying 'a' bars gives him 'b' bars for free,
 *          and he has 's' roubles, with each bar costing 'c' roubles.
 * 
 * Algorithm:
 *   - First, determine how many bars can be bought with the available money: s / c
 *   - Then, for every 'a' bars purchased, he gets 'b' bars free
 *   - So, the number of free bars = (number of bars bought / a) * b
 *   - Total bars = bars bought + free bars
 * 
 * Time Complexity: O(t) where t is the number of test cases
 * Space Complexity: O(1) - only using fixed amount of extra variables
 */

#include <iostream>
long long a, b, c, s;
int main() {
  std::cin >> a;  // read number of test cases
  while (std::cin >> s >> a >> b >> c)  // for each test case, read s, a, b, c
    std::cout << s / c + s / c / a * b << "\n";  // compute and print result
}


// https://github.com/VaHiX/CodeForces/