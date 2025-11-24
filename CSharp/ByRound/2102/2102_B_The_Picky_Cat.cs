// Problem: CF 2102 B - The Picky Cat
// https://codeforces.com/contest/2102/problem/B

/*
B. The Picky Cat

Algorithm/Technique: Sorting, Greedy, Median Calculation

Time Complexity: O(n log n) per test case due to sorting (implicit in median calculation)
Space Complexity: O(n) for storing the array elements

The problem asks if we can make the first element of the array become the median
by flipping signs of any elements. The key idea is:
1. We compare absolute values of all elements except the first one.
2. Count how many of those have absolute value less than that of the first element.
3. If this count is at most half of the array size (rounded down), then we can flip signs
   to make the first element the median.

*/
using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    int testCases = int.Parse(Console.ReadLine());
    while (testCases-- > 0) {
      int arraySize = int.Parse(Console.ReadLine());
      int[] numbers = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
      int referenceValue = Math.Abs(numbers[0]); // Absolute value of first element
      int countLessThanReference = 0; // Count of elements whose absolute value is less than reference
      
      // Loop through all elements except the first one
      for (int index = 1; index < arraySize; index++) {
        if (Math.Abs(numbers[index]) < referenceValue)
          countLessThanReference++;
      }
      
      // If count of smaller elements is <= half the array size, we can make first element median
      if (countLessThanReference <= arraySize / 2)
        Console.WriteLine("YES");
      else
        Console.WriteLine("NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/