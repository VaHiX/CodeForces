// Problem: CF 2136 F2 - From the Unknown (Hard Version)
// https://codeforces.com/contest/2136/problem/F2

/*
F2. From the Unknown (Hard Version)
Algorithms/Techniques: Binary search with interactive queries, adaptive interactor
Time Complexity: O(log W) per test case, where W <= 10^5
Space Complexity: O(1) excluding input/output buffers

This problem involves determining an unknown integer W (width of a text editor) using at most two interactive queries.
The approach uses binary search on the value of W by constructing specific test cases that allow us to deduce the range in which W lies.
*/
using System.Text;
namespace FromTheUnknownHard;
class Program {
  static void Solve() {
    const int W = 113; // Initial guess for W, used in construction
    const int len = 11611; // Length of initial array
    int[] p = new int[len]; // Initialize array with all elements equal to W
    Array.Fill(p, W);
    int q = Ask(p); // First query to check if editor can handle this case
    if (q == 0) {
      // If editor cannot display it, then W < max element of p, so W < W => impossible or we need to adjust search space
      // This branch handles case where maximum element exceeds W
      p = new int[(W - 1) * (W - 2)]; // Create a specific array for next step based on mathematical bounds
      Array.Fill(p, 1);
      q = Ask(p); // Make second query with this setup
      Ans(((W - 1) * (W - 2) + q - 1) / q); // Final computation to find W
      return;
    }
    int lo = (len + q - 1) / q; // Lower bound for W from first query
    int hi = Math.Max(lo + 1, (len + q - 2) / (q - 1)); // Upper bound adjusted from first query result
    lo *= W; // Scale bounds to actual word lengths (W was used as unit)
    hi *= W; // Same scaling on upper limit
    hi = Math.Min(100001, hi); // Cap hi at reasonable limit
    List<int> ints = new() { lo }; // Initialize list of word lengths for second query
    int c = 1; // Counter for lines in constructed array (initially 1 line due to initial element)
    for (int i = lo + 1; i < hi; i++) {
      ints.Add(lo); // Add a specific length to maintain structure
      ints.Add(i - lo); // Add another term that helps narrow the range
      c++; // Increment counter for number of elements added
    }
    int q2 = Ask(ints.ToArray()); // Query with generated array
    Ans(lo + c - (q2 - c) - 1); // Compute final W from second query result using derived formula
  }

  static int Ask(int[] p) {
    writer.Write($"? {p.Length}"); // Print query format string "? n"
    foreach (var i in p) {
      writer.Write(' '); // Add space after number
      writer.Write(i);   // Output word length
    }
    writer.WriteLine(); // Print newline to terminate query
    writer.Flush(); // Ensure output is sent immediately
    return int.Parse(reader.ReadLine()); // Read return value from jury
  }

  static void Ans(int w) {
    writer.WriteLine($"! {w}"); // Print answer in format "! W"
    writer.Flush(); // Flush output buffer
  }
  
  static void Main(string[] args) {
    int t = int.Parse(reader.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      Solve(); // Process each test case
    }
    writer.Flush(); // Flush final buffer
  }

  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/