// Problem: CF 1758 A - SSeeeeiinngg DDoouubbllee
// https://codeforces.com/contest/1758/problem/A

/*
Purpose: This code takes a string and outputs a palindrome formed by rearranging the double of the string.
         The approach is to simply concatenate the original string with its reverse.
         This works because the double of any string can always be rearranged into a palindrome
         by placing the first half of the characters in order, followed by the reverse of the first half.

Algorithms/Techniques: String manipulation, palindrome construction via reverse concatenation.

Time Complexity: O(n), where n is the length of the string s. The reverse operation takes O(n) time,
                   and printing the concatenated string also takes O(n) time.

Space Complexity: O(n), as we store the input string and its reverse, requiring space proportional to the input size.

*/
#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::cout << s;                        // Print the original string
    reverse(s.begin(), s.end());           // Reverse the string in-place
    std::cout << s << std::endl;           // Print the reversed string
  }
}


// https://github.com/VaHiX/CodeForces/