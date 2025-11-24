// Problem: CF 2131 E - Adjacent XOR
// https://codeforces.com/contest/2131/problem/E

/*
E. Adjacent XOR
time limit per test2 seconds
memory limit per test256 megabytes

Approach:
The key idea is to work backwards from the end of the arrays. Since we can only modify elements by XORing with their right neighbor, we compare values in reverse order and check if transformation is possible by considering valid operations.

Complexity:
- Time: O(n) per test case
- Space: O(1) additional space (excluding input)

Algorithms/Techniques:
- Reverse iteration through arrays
- Bitwise XOR operations
- Conditional checks for valid transitions
*/

using System;
namespace CodeForces.Problems.Round2131.E {
public class AdjacentXorChecker {
  public bool CanTransform(int[] a, int[] b, int n) {
    // If last elements don't match, transformation is impossible
    if (a[n - 1] != b[n - 1]) {
      return false;
    }
    
    // Traverse from second-to-last element to the first
    for (int i = n - 2; i >= 0; i--) {
      // If current elements are already equal, skip to next
      if (a[i] == b[i]) {
        continue;
      }
      
      // Check if we can transform a[i] into b[i] using one of two allowed operations:
      // 1. XOR with right neighbor: a[i] = a[i] ^ a[i + 1]
      // 2. XOR with current value in target array: a[i] = a[i] ^ b[i + 1]
      if (b[i] != (a[i] ^ a[i + 1]) && b[i] != (a[i] ^ b[i + 1])) {
        return false;
      }
    }
    return true;
  }
  
  private static int[] ReadIntArray(int length) {
    string[] input =
        Console.ReadLine()!.Split(' ', StringSplitOptions.RemoveEmptyEntries);
    int[] array = new int[length];
    for (int i = 0; i < length; i++) {
      array[i] = int.Parse(input[i]);
    }
    return array;
  }
  
  private static int ReadInt() { return int.Parse(Console.ReadLine()!); }
  
  public static void Main() {
    var checker = new AdjacentXorChecker();
    int testCases = ReadInt();
    while (testCases-- > 0) {
      int n = ReadInt();
      int[] a = ReadIntArray(n);
      int[] b = ReadIntArray(n);
      if (checker.CanTransform(a, b, n)) {
        Console.WriteLine("Yes");
      } else {
        Console.WriteLine("No");
      }
    }
  }
}
}


// https://github.com/VaHiX/codeForces/