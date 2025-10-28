// Problem: CF 1065 A - Vasya and Chocolate
// https://codeforces.com/contest/1065/problem/A

#include <iostream>
long long a, b, c, s;
int main() {
  std::cin >> a;
  while (std::cin >> s >> a >> b >> c)
    std::cout << s / c + s / c / a * b << "\n";
}


// https://github.com/VaHiX/codeForces/