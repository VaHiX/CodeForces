// Problem: CF 762 B - USB vs. PS/2
// https://codeforces.com/contest/762/problem/B

/*
Purpose: This program solves the problem of buying mice to equip computers in a lab,
         where computers have different port types (USB, PS/2, or both). The goal is to
         maximize the number of equipped computers, and in case of ties, minimize the total cost.

Algorithm:
- Sort all mice by price (ascending) to use a greedy approach.
- For each mouse, try to assign it to a computer:
  - If the mouse is USB type, try to assign it to a USB-only or a dual-port computer.
  - If the mouse is PS/2 type, try to assign it to a PS/2-only or a dual-port computer.
- Use a greedy strategy: always assign the cheapest available mouse to the first available computer.

Time Complexity: O(m log m) due to sorting, where m is the number of mice.
Space Complexity: O(m) for storing the list of mice.

*/
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t a, b, c;
  std::cin >> a >> b >> c;
  int64_t m;
  std::cin >> m;
  std::vector<std::pair<int64_t, std::string>> mv(m);
  for (int64_t p = 0; p < m; p++) {
    int64_t price;
    std::string port;
    std::cin >> price >> port;
    mv[p] = std::make_pair(price, port);
  }
  sort(mv.begin(), mv.end()); // Sort mice by price to apply greedy algorithm
  int64_t equipped(0), total(0);
  for (int64_t p = 0; p < mv.size(); p++) {
    if (mv[p].second == "USB") {
      if (a > 0 || c > 0) { // If there's a computer that can use this mouse
        ++equipped;
        total += mv[p].first;
        if (a > 0) {
          --a; // Assign to a USB-only computer
        } else if (c > 0) {
          --c; // Assign to a dual-port computer
        }
      }
    } else {
      if (b > 0 || c > 0) { // If there's a computer that can use this mouse
        ++equipped;
        total += mv[p].first;
        if (b > 0) {
          --b; // Assign to a PS/2-only computer
        } else if (c > 0) {
          --c; // Assign to a dual-port computer
        }
      }
    }
  }
  std::cout << equipped << " " << total << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/