// Problem: CF 2172 E - Number Maze
// https://codeforces.com/contest/2172/problem/E

/*
Purpose: This code solves the "Number Maze" problem where two permutations of a given number's digits are compared to compute the number of matches in value and position (A) and matches in value only (B). It generates all permutations of the digits, sorts them, and then compares two specific ones.

Algorithms/Techniques:
- Generation of permutations using std::next_permutation
- String comparison to count matches in position (A) and value only (B)
- Sorting permutations via next_permutation (which naturally sorts in lexicographical order)

Time Complexity: O(P * L) per test case where P is the number of permutations (at most 4! = 24) and L is the length of the string representation of n.
Space Complexity: O(P * L) to store all permutations, where P is the number of permutations and L is the length of the string.

Input Format:
- First line: number of test cases t
- For each test case: n (base number), j (index of first permutation), k (index of second permutation)

Output Format:
- For each test case: result in "xAyB" format
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, j, k;
    cin >> n >> j >> k;
    vector<string> v;
    string s = to_string(n);  // Convert number to string to work with digits
    v.push_back(s);  // Add the first permutation (original order)
    while (next_permutation(s.begin(), s.end()))  // Generate all permutations in lexicographical order
      v.push_back(s);
    int cnt = 0;  // Counter for matches in both value and position
    int l = s.length();  // Length of the permutation string
    for (int i = 0; i < l; ++i) {  // Compare each digit position
      if (v[j - 1][i] == v[k - 1][i])  // Check if digits at position i match exactly
        cnt++;
    }
    cout << cnt << "A" << l - cnt << "B" << "\n";  // Output in required format
  }
}


// https://github.com/VaHiX/CodeForces/