// Problem: CF 1896 B - AB Flipping
// https://codeforces.com/contest/1896/problem/B

/*
 * Problem: B. AB Flipping
 * 
 * Algorithm/Technique: Two-pointer approach
 * 
 * Time Complexity: O(n) where n is the length of the string. Each character is visited at most twice.
 * Space Complexity: O(1) as we only use a constant amount of extra space.
 * 
 * The solution works by identifying segments of the string composed of consecutive 'A's and 'B's,
 * and counting the number of operations possible in each segment.
 * 
 * Key idea:
 * - We process the string from left to right using two pointers.
 * - For each group of 'B's that follows a group of 'A's, we count how many operations can be performed.
 * - The number of operations is equal to the number of characters between the two groups minus 1.
 */

using System;
class Programm {
  static int Main() {
    int queries = Int32.Parse(Console.ReadLine()); // Read number of test cases
    while (queries-- > 0) {
      int stringLength = Int32.Parse(Console.ReadLine()); // Read length of the string
      string inputString = Console.ReadLine(); // Read the string
      int answer = 0, ptr1 = 0, ptr2 = 0; // Initialize counters and pointers
      
      // Skip initial 'B's as they cannot be used to perform operations
      while (ptr1 < stringLength && inputString[ptr1] == 'B') {
        ptr1++;
        ptr2++;
      }
      
      // Process the remaining string using two pointers
      while (ptr1 < stringLength) {
        int cntB = 0; // Count of 'B's in current segment
        
        // Move ptr2 to the end of current 'A' segment
        while ((ptr2 < stringLength) && (inputString[ptr2] == 'A')) {
          ptr2++;
        }
        
        // Move ptr2 to the end of current 'B' segment and count 'B's
        while ((ptr2 < stringLength) && (inputString[ptr2] == 'B')) {
          ptr2++;
          cntB++;
        }
        
        // If last character in current segment is 'B', add operations count
        if (inputString[ptr2 - 1] == 'B') {
          answer += ptr2 - ptr1 - 1; // Number of operations = distance between segments minus 1
        }
        
        // Update ptr1 based on whether we have encountered any 'B'
        if (cntB != 0) {
          ptr1 = ptr2 - 1; // Move ptr1 to the last 'B' in segment
        } else {
          break; // No more 'B's to process, exit loop
        }
      }
      Console.WriteLine(answer); // Output the maximum number of operations
    }
    return 0;
  }
}


// https://github.com/VaHiX/CodeForces/