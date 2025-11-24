// Problem: CF 1978 C - Manhattan Permutations
// https://codeforces.com/contest/1978/problem/C

/*
 * Problem: Manhattan Permutations
 * 
 * Purpose: Given n and k, find a permutation of length n such that its Manhattan value equals k.
 *          The Manhattan value is defined as sum of absolute differences between each element and its index.
 * 
 * Algorithm:
 * - Start with the identity permutation [1, 2, ..., n]
 * - Calculate the maximum possible Manhattan value for n elements
 * - If k is odd or greater than the maximum, it's impossible
 * - Otherwise, we can construct the permutation by swapping elements from the outside in
 * 
 * Key Concepts:
 * - The maximum Manhattan value occurs when elements are swapped from both ends:
 *   for each pair (i, n-i+1), we can increase the Manhattan value by 2*(n-i+1-i) = 2*(n-2*i+1)
 * - We greedily swap elements from left to right until we reduce k to 0
 * 
 * Time Complexity: O(n) per test case - we iterate through elements once and perform swaps
 * Space Complexity: O(n) - we store the permutation list
 */

using System;
using System.Collections.Generic;
class Program {
  static void Main(string[] args) {
    int test = FastIO.ReadInt();
    while (test-- > 0) {
      sol();
    }
  }
  static void sol() {
    long n = FastIO.ReadLong();
    long k = FastIO.ReadLong();
    List<long> ans = new List<long>();
    long sum = 0;
    // Initialize the identity permutation and calculate the max possible Manhattan value
    for (long i = 1; i <= n; i++) {
      sum += Math.Abs(i - (n - i + 1)); // This calculates the maximum Manhattan value
      ans.Add(i);
    }
    // If k is odd or exceeds the maximum possible Manhattan value, impossible
    if (k % 2 == 1 || sum < k) {
      Console.WriteLine("NO");
    } else {
      Console.WriteLine("YES");
      long ind = 0;
      long N = n;
      // While we still have k to reduce, swap pairs from the outside in
      while (k > (N - 1) * 2) {
        long temp = ans[(int)ind];
        ans[(int)ind] = ans[(int)(n - ind - 1)];
        ans[(int)(n - ind - 1)] = temp;
        k -= (N - 1) * 2; // Reduce k by the contribution of this swap
        N -= 2; // Decrease the window size for remaining swaps
        ind++; // Move to the next pair
      }
      k /= 2; // k is now the number of swaps needed to reduce to half
      // Perform the final partial swap
      long temp2 = ans[(int)ind];
      ans[(int)ind] = ans[(int)(ind + k)];
      ans[(int)(ind + k)] = temp2;
      FastIO.WriteLine(string.Join(" ", ans));
    }
  }
}
static class FastIO {
  private static readonly Queue<string> inputBuffer = new Queue<string>();
  private static string[] tokens;
  private static int pos;
  public static string ReadLine() {
    if (inputBuffer.Count == 0) {
      inputBuffer.Enqueue(Console.ReadLine());
    }
    return inputBuffer.Dequeue();
  }
  public static string[] ReadLineTokens() {
    while (tokens == null || pos >= tokens.Length) {
      tokens = ReadLine().Split(new[] { ' ', '\t' },
                                StringSplitOptions.RemoveEmptyEntries);
      pos = 0;
    }
    return tokens;
  }
  public static int ReadInt() { return int.Parse(ReadLineTokens()[pos++]); }
  public static long ReadLong() { return long.Parse(ReadLineTokens()[pos++]); }
  public static void WriteLine(string output) { Console.WriteLine(output); }
}


// https://github.com/VaHiX/CodeForces/