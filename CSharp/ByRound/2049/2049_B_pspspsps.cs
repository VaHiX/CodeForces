// Problem: CF 2049 B - pspspsps
// https://codeforces.com/contest/2049/problem/B

// Flowerbox:
// Problem: Determine if a permutation of integers 1 to n exists satisfying given constraints.
//          Each position in input string s specifies constraint type:
//          'p': prefix up to this position must form a permutation
//          's': suffix from this position must form a permutation  
//          '.': no constraint
// Algorithm: 
//   - Preprocess arrays to track:
//     * nextP[j]: next occurrence of 'p' from position j (or n+1 if none)
//     * lastS[j]: last occurrence of 's' up to position j (or 0 if none)
//   - For each position j, compute minimum required length for valid permutation
//   - Sort these values and check if they satisfy the threshold condition
// Time Complexity: O(n^2) per test case due to nested loops for preprocessing
// Space Complexity: O(n) for storing auxiliary arrays

using System;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      string input = Console.ReadLine();
      input = " " + input; // Shift indices to 1-based
      int[] nextP = Enumerable.Repeat(n + 1, n + 2).ToArray(); // Next 'p' position from index j
      for (int j = n; j >= 1; j--) {
        if (input[j] == 'p')
          nextP[j] = j; // If current char is 'p', nextP is itself
        else
          nextP[j] = nextP[j + 1]; // Otherwise, inherit from next position
      }
      int[] lastS = new int[n + 1]; // Last occurrence of 's' up to index j
      for (int j = 1; j <= n; j++) {
        if (input[j] == 's')
          lastS[j] = j; // If current char is 's', store its position
        else
          lastS[j] = lastS[j - 1]; // Otherwise, inherit from previous position
      }
      int[] Uj = new int[n];
      for (int j = 1; j <= n; j++) {
        int uP = int.MaxValue;
        if (nextP[j] <= n) {
          uP = nextP[j]; // Next 'p' position is valid
        }
        int uS = int.MaxValue;
        if (lastS[j] >= 1) {
          uS = n - lastS[j] + 1; // Distance from last 's' to end
        }
        if (uP != int.MaxValue && uS != int.MaxValue) {
          Uj[j - 1] = Math.Min(uP, uS); // Minimum required length
        } else if (uP != int.MaxValue) {
          Uj[j - 1] = uP;
        } else if (uS != int.MaxValue) {
          Uj[j - 1] = uS;
        } else {
          Uj[j - 1] = n; // No constraints, need full length
        }
      }
      Array.Sort(Uj); // Sort required lengths
      bool isValid = true;
      for (int i = 1; i <= n; i++) {
        if (Uj[i - 1] < i) { // Check if required length exceeds position index
          isValid = false;
          break;
        }
      }
      Console.WriteLine(isValid ? "YES" : "NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/