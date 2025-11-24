// Problem: CF 2019 A - Max Plus Size
// https://codeforces.com/contest/2019/problem/A

/*
 * Problem: Max Plus Size
 * Algorithm: Greedy approach to select non-adjacent elements to maximize score.
 *            Score = max_value_of_selected_elements + count_of_selected_elements.
 * Time Complexity: O(n), where n is the size of the array.
 * Space Complexity: O(n), due to storage of the input list.
 */

using System;
using System.Collections.Generic;
using System.Linq;

public class Solution {
  public static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      int size = int.Parse(Console.ReadLine()); // Read size of the array
      List<int> array = new List<int>();
      string[] inputs = Console.ReadLine().Split(); // Read input numbers
      for (int i = 0; i < size; i++) {
        array.Add(int.Parse(inputs[i])); // Parse and add each number to list
      }
      int MaxScore = new Solution().MaxPlusSize(size, array); // Calculate max score
      Console.WriteLine(MaxScore); // Output result
    }
  }

  public int MaxPlusSize(int size, List<int> array) {
    int maxElement1 = array.Max(); // Find maximum element in the array
    int maxElement2 = array.Max(); // Another reference to max for logic clarity (not used effectively)
    
    int OddScore = 0; // Tracks score for odd-indexed selected elements
    int EvenScore = 0; // Tracks score for even-indexed selected elements
    
    for (int j = 0; j < size; j++) {
      if (j % 2 == 0) {
        OddScore += 1; // Increment count of selected elements
        if (maxElement1 == array[j]) { // If current element is max, add it to score
          OddScore += maxElement1;
          maxElement1 = 0; // Prevent reuse of max value
        }
      } else {
        EvenScore += 1; // Increment count of selected elements
        if (maxElement2 == array[j]) { // If current element is max, add it to score
          EvenScore += maxElement2;
          maxElement2 = 0; // Prevent reuse of max value
        }
      }
    }
    
    return (OddScore >= EvenScore) ? OddScore : EvenScore; // Return maximum score possible
  }
}


// https://github.com/VaHiX/codeForces/