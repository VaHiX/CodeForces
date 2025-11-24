// Problem: CF 2102 D - Quartet Swapping
// https://codeforces.com/contest/2102/problem/D

/*
 * Problem: D. Quartet Swapping
 * Algorithm: Inversion Parity + Binary Indexed Tree + Greedy Merge Strategy
 * Description:
 *   Given a permutation of integers [1..n], we can swap elements at positions (i, i+2) and (i+1, i+3) simultaneously for any valid i.
 *   This operation allows us to rearrange elements in even-indexed groups and odd-indexed groups independently.
 *   For each group, we calculate the inversion parity. Two groups with same parity can be merged in sorted order,
 *   while groups with different parity require trying swaps of last two elements in each group.
 *
 * Time Complexity: O(n log n) per test case due to sorting and BIT operations
 * Space Complexity: O(n) for storing arrays and BIT structure
 */

using System;
using System.Collections.Generic;
using System.Linq;

class Program {
  // Calculates the inversion parity of a list using Binary Indexed Tree (Fenwick Tree)
  static int CalculateInversionParity(List<int> elements) {
    int count = elements.Count;
    List<int> sortedElements = new List<int>(elements);
    Dictionary<int, int> valueToIndex = new Dictionary<int, int>();
    sortedElements.Sort();
    for (int i = 0; i < count; i++)
      valueToIndex[sortedElements[i]] = i;
    int[] binaryIndexedTree = new int[count + 1];
    int parity = 0;
    Action<int> UpdateTree = (index) => {
      for (++index; index <= count; index += index & -index)
        binaryIndexedTree[index]++;
    };
    Func<int, int> QueryTree = (index) => {
      int result = 0;
      for (++index; index > 0; index -= index & -index)
        result += binaryIndexedTree[index];
      return result;
    };
    for (int i = count - 1; i >= 0; i--) {
      int compressedIndex = valueToIndex[elements[i]];
      parity ^= QueryTree(compressedIndex - 1) % 2;
      UpdateTree(compressedIndex);
    }
    return parity;
  }

  // Merges even and odd indexed elements in alternating fashion to form a result list
  static List<int> MergeVectors(List<int> evenElements, List<int> oddElements) {
    int totalSize = evenElements.Count + oddElements.Count;
    List<int> merged = new List<int>(totalSize);
    int evenIndex = 0, oddIndex = 0;
    for (int i = 0; i < totalSize; i++) {
      merged.Add((i % 2 == 0) ? evenElements[evenIndex++]
                              : oddElements[oddIndex++]);
    }
    return merged;
  }

  // Processes each test case to compute result
  static void ProcessTestCases() {
    int testCases = int.Parse(Console.ReadLine());
    while (testCases-- > 0) {
      int elementCount = int.Parse(Console.ReadLine());
      List<int> elements =
          Console.ReadLine().Split().Select(int.Parse).ToList();

      // Split input into even and odd indexed elements
      List<int> evenPositionElements = new List<int>();
      List<int> oddPositionElements = new List<int>();
      for (int i = 0; i < elementCount; i++) {
        if (i % 2 == 0)
          evenPositionElements.Add(elements[i]);
        else
          oddPositionElements.Add(elements[i]);
      }

      // Sort for merging purposes
      List<int> sortedEven = new List<int>(evenPositionElements);
      List<int> sortedOdd = new List<int>(oddPositionElements);
      sortedEven.Sort();
      sortedOdd.Sort();

      // Compute inversion parities for both groups
      int evenParity = CalculateInversionParity(evenPositionElements);
      int oddParity = CalculateInversionParity(oddPositionElements);

      List<int> result;
      if (evenParity == oddParity) {
        // Same parity: direct merge in sorted order
        result = MergeVectors(sortedEven, sortedOdd);
      } else {
        // Different parity: try swapping last two elements of each group and compare results
        List<int> modifiedEven = new List<int>(sortedEven);
        List<int> modifiedOdd = new List<int>(sortedOdd);
        if (modifiedEven.Count >= 2) {
          int temp = modifiedEven[modifiedEven.Count - 1];
          modifiedEven[modifiedEven.Count - 1] =
              modifiedEven[modifiedEven.Count - 2];
          modifiedEven[modifiedEven.Count - 2] = temp;
        }
        if (modifiedOdd.Count >= 2) {
          int temp = modifiedOdd[modifiedOdd.Count - 1];
          modifiedOdd[modifiedOdd.Count - 1] =
              modifiedOdd[modifiedOdd.Count - 2];
          modifiedOdd[modifiedOdd.Count - 2] = temp;
        }

        List<int> candidate1 = MergeVectors(modifiedEven, sortedOdd);
        List<int> candidate2 = MergeVectors(sortedEven, modifiedOdd);
        result = (candidate1.SequenceCompareTo(candidate2) <= 0) ? candidate1
                                                                 : candidate2;
      }
      Console.WriteLine(string.Join(" ", result));
    }
  }

  static void Main() { ProcessTestCases(); }
}

static class Extensions {
  // Compares two sequences lexicographically
  public static int SequenceCompareTo<T>(this IEnumerable<T> first,
                                         IEnumerable<T> second)
      where T : IComparable<T> {
    using (var e1 = first.GetEnumerator()) using (var e2 =
                                                      second.GetEnumerator()) {
      while (e1.MoveNext()) {
        if (!e2.MoveNext())
          return 1;
        int comparison = e1.Current.CompareTo(e2.Current);
        if (comparison != 0)
          return comparison;
      }
      return e2.MoveNext() ? -1 : 0;
    }
  }
}


// https://github.com/VaHiX/codeForces/