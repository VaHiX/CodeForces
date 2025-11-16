// Problem: CF 2055 B - Crafting
// https://codeforces.com/contest/2055/problem/B

/*
B. Crafting
Algorithms/Techniques: Greedy, Array manipulation, Simulation
Time Complexity: O(n) per test case
Space Complexity: O(n) due to input arrays

Problem:
We are given two arrays a and b representing current materials and needed materials.
We can perform an operation: select material i, spend 1 unit of all other materials,
and gain 1 unit of material i. Determine if it's possible to make a >= b for all elements.

Approach:
- For each material, we compare b[i] with a[i]:
  - If b[i] > a[i], we must perform operations to increase a[i]
  - If b[i] < a[i], we might have surplus that can be used to help others
- Only one material can be increased at a time (by performing operations on it).
- So, exactly one element needs to be increased (call it the "base" material).
    - This base material must have exactly 1 element with b[i] > a[i].
    - The difference d1 = b[i] - a[i] is how much we need to increase.
    - For all other elements where b[i] < a[i], we note the surplus d2 = a[i] - b[i].
- The key condition: if we increase some material by d1 units via operations, 
  then we must be able to "pay" for that by consuming surplus from the other materials.
  Since we lose 1 unit of every other material, we must have at least d1 units of surplus 
  in total among remaining materials.
- In this case, we want the minimum surplus d2 among all elements where b[i] < a[i].
  If d2 >= d1, then it's possible to do so.

We iterate once through the array to:
  - Check how many times b[i] > a[i]
  - Calculate d1 (if exactly one)
  - Track minimum surplus d2
*/

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of arrays
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse); // Read current amounts
      line = Console.ReadLine().Trim().Split(' ');
      var b = Array.ConvertAll(line, int.Parse); // Read required amounts
      getAns(n, a, b); // Process the case
    }
  }
  
  static void getAns(int n, int[] a, int[] b) {
    var c = 0;           // Count of elements where b[i] > a[i]
    var d1 = 0;          // Required increase for one material (if exactly one)
    var eq = 0;          // Unused variable
    var d2 = int.MaxValue; // Minimum surplus among elements where b[i] < a[i]
    
    for (int i = 0; i < n; i++) {
      if (b[i] > a[i]) { // If we need more of this material
        c++;             // Increment count
        if (c > 1) {     // If more than one material needs increase
          Console.WriteLine("NO");
          return;
        }
        d1 = b[i] - a[i]; // Store the deficit for this material
      } else {
        d2 = Min(d2, a[i] - b[i]); // Track minimum surplus (a[i] - b[i])
      }
    }
    
    if (c == 0)            // If no increases needed
      Console.WriteLine("YES");
    else
      Console.WriteLine(d2 >= d1 ? "YES" : "NO"); // Check if surplus is enough to cover deficit
  }
}


// https://github.com/VaHiX/codeForces/