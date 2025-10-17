// Problem: CF 1833 A - Musical Puzzle
// https://codeforces.com/contest/1833/problem/A

/*
Problem: A. Musical Puzzle
Purpose: Determine the minimum number of 2-note melodies needed to construct a given melody string.
Algorithms/Techniques: 
    - Sliding window technique to extract all consecutive pairs of characters.
    - Set data structure to count unique pairs (as duplicates are merged).
Time Complexity: O(n) per test case, where n is the length of the string s.
Space Complexity: O(n) for storing the set of pairs in worst case.

Input: 
    - t: number of test cases
    - For each test case:
        - n: length of string s
        - s: melody string of length n consisting of 'a'-'g'

Output:
    - Minimum number of 2-note melodies required to construct the input melody.
*/

#include <iostream>
#include <set>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::set<std::string> v; // Set to store unique consecutive pairs of notes
    for (long p = 1; p < s.size(); p++) { // Iterate through string starting from index 1
      v.insert(s.substr(p - 1, 2)); // Extract 2-character substring and insert into set
    }
    std::cout << v.size() << std::endl; // Output number of unique pairs (required melodies)
  }
}


// https://github.com/VaHiX/codeForces/