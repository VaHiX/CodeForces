// Problem: CF 1890 A - Doremy's Paint 3
// https://codeforces.com/contest/1890/problem/A

/*
Algorithm/Techniques: 
- Sorting the array to group identical elements together.
- Counting distinct elements and checking their distribution.
- For an array to be "good", all adjacent sums must be equal.
  This means that if we have elements a1, a2, ..., an, then:
  a1 + a2 = a2 + a3 = ... = an-1 + an = k
  Which implies a1 = a3 = a5 = ... and a2 = a4 = a6 = ...
  So, in the sorted array, there are at most 2 distinct values.
- We check if the counts of these two values differ by at most 1 to allow a valid arrangement.

Time Complexity: O(n log n) due to sorting, where n is the size of the array.
Space Complexity: O(1) if we ignore the input array space, otherwise O(n) for storing input.
*/
using System;
class Program {
  static int DistinctElements(int[] arr) {
    int cnt = 0;
    for (int i = 0; i < arr.Length; i++) {
      // Skip all duplicates of current element
      while (i < arr.Length - 1 && arr[i] == arr[i + 1]) {
        i++;
      }
      cnt++;
    }
    return cnt;
  }
  static void Main(string[] args) {
    int t = Convert.ToInt32(Console.ReadLine());
    while (t-- > 0) {
      int nj = Convert.ToInt32(Console.ReadLine());
      int[] a = new int[nj];
      string[] input = Console.ReadLine().Split();
      for (int i = 0; i < nj; i++) {
        a[i] = Convert.ToInt32(input[i]);
      }
      Array.Sort(a);
      // If all elements are the same, then it's always good
      if (a[0] == a[nj - 1]) {
        Console.WriteLine("YES");
        continue;
      }
      // If there are more than 2 distinct elements, it's impossible
      if (DistinctElements(a) > 2) {
        Console.WriteLine("NO");
        continue;
      }
      // Find the smallest and largest distinct elements
      int x = a[0];
      int y = a[nj - 1];
      int ax = 0, by = 0;
      // Count occurrences of each element
      foreach (int element in a) {
        if (element == x) {
          ax++;
        } else if (element == y) {
          by++;
        }
      }
      // If counts are equal, arrangement is possible
      if (ax == by) {
        Console.WriteLine("YES");
        continue;
      }
      // If difference between counts is 1, still possible
      int m = ax - by;
      if (Math.Abs(m) == 1) {
        Console.WriteLine("YES");
      } else {
        Console.WriteLine("NO");
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/