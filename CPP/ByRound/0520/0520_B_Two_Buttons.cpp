// Problem: CF 520 B - Two Buttons
// https://codeforces.com/contest/520/problem/B

/*
Algorithm: Greedy approach with backward thinking
Techniques: Reverse engineering, greedy strategy

Time Complexity: O(log m) - In the worst case, we halve m until it becomes less than or equal to n
Space Complexity: O(1) - Only using a constant amount of extra space

The algorithm works by reversing the process: instead of going from n to m, we go from m to n.
- If m is odd, we increment it (reverse of subtracting 1)
- If m is even, we halve it (reverse of multiplying by 2)
We count the operations needed to reach a value <= n, then add the difference between n and that value
*/

#include <iostream>
int n, m, a;
int main() {
  std::cin >> n >> m;
  while (n < m)
    m % 2 ? m++ : m /= 2, a++;  // If m is odd, increment it; if even, divide by 2. Count each operation
  std::cout << a + n - m;  // Add remaining operations to get from current m to n
}


// https://github.com/VaHiX/CodeForces/