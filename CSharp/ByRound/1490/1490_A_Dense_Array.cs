// Problem: CF 1490 A - Dense Array
// https://codeforces.com/contest/1490/problem/A

/*
 * Problem: Dense Array
 * 
 * Purpose: Determine the minimum number of elements to insert into an array to make it "dense".
 * A dense array is one where for any two adjacent elements, the larger is at most twice the smaller.
 * 
 * Algorithm:
 * - For each pair of adjacent elements, check if the ratio condition is satisfied.
 * - If not, calculate how many elements need to be inserted between them to make the array dense.
 * - The number of elements to insert is determined by how many times we need to double the smaller element
 *   to reach or exceed the larger element.
 * 
 * Time Complexity: O(n) for each test case, where n is the length of the array.
 * Space Complexity: O(1) excluding input/output storage.
 */

using System;
public class DenseArray {
  public static int Main() {
    string[] parts = ReadSplitLine(1);
    if (parts == null)
      return -1;
    ushort t;
    if (!UInt16.TryParse(parts[0], out t))
      return -1;
    if (t < 1 || t > 1000)
      return -1;
    for (ushort i = 0; i < t; i++) {
      parts = ReadSplitLine(1);
      if (parts == null)
        return -1;
      byte n;
      if (!Byte.TryParse(parts[0], out n))
        return -1;
      if (n < 2 || n > 50)
        return -1;
      parts = ReadSplitLine(n);
      if (parts == null)
        return -1;
      byte ans = 0;
      byte aPrev = 0;
      for (byte j = 0; j < n; j++) {
        byte aj;
        if (!Byte.TryParse(parts[j], out aj))
          return -1;
        if (aj < 1 || aj > 50)
          return -1;
        if (j > 0) {
          // Calculate the minimum and maximum of previous and current element
          byte aMin = Math.Min(aPrev, aj);
          byte aMax = Math.Max(aPrev, aj);
          // Start with double the minimum value
          byte aAdd = Convert.ToByte(2 * aMin);
          // While the doubled value is less than the maximum, keep doubling and count additions
          while (aAdd < aMax) {
            aAdd *= 2;
            ans++;
          }
        }
        aPrev = aj;
      }
      Console.WriteLine(ans);
    }
    return 0;
  }
  public static string[] ReadSplitLine(uint numPartReq) {
    string line = Console.ReadLine();
    if (line == null)
      return null;
    char[] delims = new char[] { ' ', '\t' };
    string[] parts = line.Split(delims, StringSplitOptions.RemoveEmptyEntries);
    return (parts.Length == numPartReq ? parts : null);
  }
}


// https://github.com/VaHiX/CodeForces/