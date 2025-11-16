// Problem: CF 1986 E - Beautiful Array
// https://codeforces.com/contest/1986/problem/E

/*
 * Problem: Beautiful Array
 * 
 * Algorithm:
 * - The key insight is that for an array to be beautiful, it must be a palindrome.
 * - For a palindrome of length n, elements at symmetric positions must be equal.
 * - Since we can only increment elements by k, we analyze the problem modulo k.
 * - We group numbers by their remainder when divided by k. 
 * - For each group, we sort the numbers and pair them up.
 * - If a group has an odd number of elements, exactly one element remains unpaired.
 * - If more than one group has an odd count, it's impossible.
 * - For even groups, we compute the minimal cost to make pairs equal.
 * - For the odd group, we compute the minimum cost to make all elements equal by choosing an optimal middle element.
 * 
 * Time Complexity: O(n log n) due to sorting operations
 * Space Complexity: O(n) for storing values in frequency maps and arrays
 */

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void ProcessArray(int testCase) {
    string[] nk = Console.ReadLine().Trim().Split();
    int n = int.Parse(nk[0]);
    int k = int.Parse(nk[1]);
    int[] arr = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();
    Dictionary<int, SortedSet<int>> freqMap =
        new Dictionary<int, SortedSet<int>>();
    foreach (int x in arr) {
      int mod = x % k;
      if (freqMap.ContainsKey(mod)) {
        if (freqMap[mod].Contains(x)) {
          freqMap[mod].Remove(x);
        } else {
          freqMap[mod].Add(x);
        }
      } else {
        freqMap[mod] = new SortedSet<int>() { x };
      }
    }
    int count = 0, remainder = -1;
    foreach (var pair in freqMap) {
      int size = pair.Value.Count;
      if (size % 2 != 0) {
        count++;
        remainder = pair.Key;
      }
    }
    if (count > 1) {
      Console.WriteLine(-1);
      return;
    }
    int result = 0;
    foreach (var pair in freqMap) {
      int key = pair.Key;
      if (key == remainder)
        continue;
      List<int> values = pair.Value.ToList();
      for (int i = 0; i < values.Count; i += 2) {
        int b = values[i];
        if (i + 1 < values.Count) {
          int tp = values[i + 1];
          result += (tp - b) / k;
        }
      }
    }
    if (count > 0) {
      List<int> v = freqMap[remainder].ToList();
      int m = v.Count;
      if (m == 1) {
        Console.WriteLine(result);
        return;
      }
      int[] prefix = new int[m];
      int[] suffix = new int[m];
      for (int i = 1; i < m; i += 2) {
        prefix[i] = v[i] - v[i - 1];
        if (i > 1)
          prefix[i] += prefix[i - 2];
      }
      for (int i = m - 2; i >= 0; i -= 2) {
        suffix[i] = v[i + 1] - v[i];
        if (i < m - 2)
          suffix[i] += suffix[i + 2];
      }
      int temp = int.MaxValue;
      for (int i = 0; i < m; i += 2) {
        int x = 0;
        if (i > 0)
          x += prefix[i - 1];
        if (i + 1 < m)
          x += suffix[i + 1];
        temp = Math.Min(temp, x);
      }
      result += temp / k;
    }
    Console.WriteLine(result);
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine().Trim());
    for (int i = 0; i < t; i++) {
      ProcessArray(i);
    }
  }
}


// https://github.com/VaHiX/CodeForces/