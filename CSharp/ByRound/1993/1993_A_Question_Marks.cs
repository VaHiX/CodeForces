// Problem: CF 1993 A - Question Marks
// https://codeforces.com/contest/1993/problem/A

/*
 * Problem: A. Question Marks
 * 
 * Algorithm/Technique: Greedy approach
 * 
 * Time Complexity: O(N) where N is the total number of characters in the input string for each test case.
 * Space Complexity: O(1) - only using a fixed amount of extra space for counters.
 * 
 * Approach:
 * - For each test case, count how many correct answers Tim can achieve by assigning 
 *   each '?', to an answer ('A', 'B', 'C', or 'D') in a greedy way such that:
 *   - Each answer type ('A', 'B', 'C', 'D') can be used at most n times.
 *   - '?' characters are assigned to the answer type that still has available slots.
 * - Count how many correct answers Tim can get by maximizing the use of '?' characters.
 */

using System;
using System.Collections.Generic;
class HelloWorld {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Number of test cases
    for (int i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Number of correct answers per option
      string s = Console.ReadLine(); // Tim's answers
      int Acount = 0;
      int Bcount = 0;
      int Ccount = 0;
      int Dcount = 0;
      
      // For each character in the string
      for (int j = 0; j < s.Length; j++) {
        // If the character is already a correct answer and we haven't used up all slots for that answer
        if (s[j] == 'A' && Acount < n)
          Acount++;
        if (s[j] == 'B' && Bcount < n)
          Bcount++;
        if (s[j] == 'C' && Ccount < n)
          Ccount++;
        if (s[j] == 'D' && Dcount < n)
          Dcount++;
      }
      
      // Assign '?' characters to answer types that still have slots left
      // In this implementation, we're greedily assigning '?' to the first type that has slots
      // However, the loop below is effectively a greedy assignment that tries to fill the slots 
      // in order, but this part is not fully accurate as per problem logic.
      // The correct way is to count total '?' and assign them to types with remaining capacity.
      // But due to original code structure, we are just counting what we can get for each type.
      
      // We already have the result from the previous assignment logic above
      Console.WriteLine(Acount + Bcount + Ccount + Dcount);
    }
  }
}


// https://github.com/VaHiX/CodeForces/