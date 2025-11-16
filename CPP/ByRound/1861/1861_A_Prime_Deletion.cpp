// Problem: CF 1861 A - Prime Deletion
// https://codeforces.com/contest/1861/problem/A

/*
Purpose: This code determines if a given sequence of digits (1-9, each appearing once) can be reduced to a prime number 
         by deleting digits. It does so by checking if the sequence contains '1' or '7' and directly outputs 
         a prime number composed of these digits (17 or 71), or reports impossibility for other cases.
         
         The solution leverages that:
         - If a sequence contains a '1', removing all other digits except '1' and '7' and arranging them as "17" gives a prime.
         - If a sequence contains a '7', removing all other digits except '7' and '1' and arranging them as "71" gives a prime.
         - The problem constraints allow this greedy approach, as we only need one valid prime number to output.
         
         Algorithms/Techniques: Greedy Search
         Time Complexity: O(n) per test case where n is the length of input string (9 digits).
         Space Complexity: O(1) as we only use a fixed amount of extra space.
*/
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '1') {
        std::cout << 17 << std::endl;
        break;
      }
      if (s[p] == '7') {
        std::cout << 71 << std::endl;
        break;
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/