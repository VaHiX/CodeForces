// Problem: CF 1921 D - Very Different Array
// https://codeforces.com/contest/1921/problem/D

using System;
using System.Linq;
class Program {
  static void Main() {
    try {
      Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput(),
                                               Console.InputEncoding, false,
                                               bufferSize: 1024));
      Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput(),
                                                Console.OutputEncoding,
                                                bufferSize: 1024));
      int t = int.Parse(Console.ReadLine());
      for (int testCase = 0; testCase < t; testCase++) {
        YourFunction();
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
  static void YourFunction() {
    var input1 = Console.ReadLine().Split().Select(long.Parse).ToArray();
    long n = input1[0], m = input1[1];
    var a = Console.ReadLine().Split().Select(long.Parse).ToArray();
    var b = Console.ReadLine().Split().Select(long.Parse).ToArray();
    Array.Sort(a);
    Array.Sort(b);
    long[] prefixSumA = new long[n];
    long[] prefixSumB = new long[m];
    for (int i = 0; i < n; i++) {
      prefixSumA[i] = (i == 0) ? a[i] : a[i] + prefixSumA[i - 1];
    }
    for (int i = 0; i < m; i++) {
      prefixSumB[i] = (i == 0) ? b[i] : b[i] + prefixSumB[i - 1];
    }
    long[] suffixSumA = new long[n];
    long[] suffixSumB = new long[m];
    for (int i = (int)(n - 1); i >= 0; i--) {
      suffixSumA[i] = (i == n - 1) ? a[i] : suffixSumA[i + 1] + a[i];
    }
    for (int i = (int)(m - 1); i >= 0; i--) {
      suffixSumB[i] = (i == m - 1) ? b[i] : suffixSumB[i + 1] + b[i];
    }
    long maxDifference = -1;
    for (long i = 0; i <= n; i++) {
      long npa = i, nna = n - i, npb = n - i, nnb = i;
      long sum;
      if (i == 0) {
        sum = suffixSumB[checked((int)(m - npb))] -
              prefixSumA[checked((int)(n - 1))];
      } else if (i == n) {
        sum = suffixSumA[0] - prefixSumB[checked((int)(n - 1))];
      } else {
        int indexNpa = checked((int)(n - npa));
        int indexNpb = checked((int)(m - npb));
        int indexNna = checked((int)(nna - 1));
        int indexNnb = checked((int)(nnb - 1));
        sum = suffixSumA[indexNpa] + suffixSumB[indexNpb] -
              prefixSumA[indexNna] - prefixSumB[indexNnb];
      }
      maxDifference = Math.Max(sum, maxDifference);
    }
    Console.WriteLine(maxDifference);
  }
}


// https://github.com/VaHiX/CodeForces/