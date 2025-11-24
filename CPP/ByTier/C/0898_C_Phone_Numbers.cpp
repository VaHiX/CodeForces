// Problem: CF 898 C - Phone Numbers
// https://codeforces.com/contest/898/problem/C

/*
Purpose: This program organizes phone numbers recorded by Vasya, removing redundant entries 
         where one number is a suffix of another for the same person. It processes multiple 
         entries, each containing a name and a list of phone numbers. Numbers are reversed 
         to facilitate suffix checking, then processed to eliminate redundant suffixes.

Algorithms/Techniques:
- Use of std::map and std::set for storing and managing unique phone numbers per person.
- Reversing phone numbers to efficiently check suffix relationships.
- Iterative removal of suffixes from the set until no more can be removed.

Time Complexity: O(N * M * log(M)) where N is number of entries and M is average number of phone numbers per entry.
Space Complexity: O(N * M) for storing phone numbers and names in maps and sets.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

int main() {
  std::map<std::string, std::set<std::string>> m; // Map to store name -> set of reversed phone numbers
  long n;
  std::cin >> n;
  while (n--) {
    std::string name;
    std::cin >> name;
    long u;
    std::cin >> u;
    while (u--) {
      std::string num;
      std::cin >> num;
      std::reverse(num.begin(), num.end()); // Reverse the phone number to check suffixes
      m[name].insert(num);
    }
  }
  std::cout << m.size() << std::endl; // Print number of unique friends
  std::map<std::string, std::set<std::string>>::iterator it;
  for (it = m.begin(); it != m.end(); it++) {
    std::string name = it->first;
    std::set<std::string> ss = it->second;
    std::set<std::string>::iterator st, sa, sb;
    bool done(false);
    while (!done) {
      done = true;
      for (sa = ss.begin(); sa != ss.end(); sa++) {
        if (!done) {
          break;
        }
        sb = sa;
        ++sb;
        while (sb != ss.end()) {
          std::string aa = *sa;
          std::string bb = *sb;
          if (bb.find(aa) == 0) { // Check if aa is a prefix of bb (since strings are reversed)
            ss.erase(sa);
            done = false;
            break;
          } else {
            ++sb;
          }
        }
      }
    }
    std::cout << name << " " << ss.size() << " ";
    for (st = ss.begin(); st != ss.end(); st++) {
      std::string str = *st;
      std::reverse(str.begin(), str.end()); // Reverse back to original form for output
      std::cout << str << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/