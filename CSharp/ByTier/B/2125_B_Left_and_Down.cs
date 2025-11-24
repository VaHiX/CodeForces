// Problem: CF 2125 B - Left and Down
// https://codeforces.com/contest/2125/problem/B

/*
B. Left and Down
Algorithm: Mathematical analysis using GCD and optimization
Time Complexity: O(log(min(a,b))) per test case
Space Complexity: O(1)

The problem involves finding the minimum cost to move a robot from (a, b) to (0, 0) 
using operations of the form (dx, dy) where 0 <= dx, dy <= k. Each unique pair costs 1,
and repeated pairs cost 0.

Key observations:
1. If both a and b are <= k, we can go directly with one operation costing 1.
2. Otherwise, check if there exists a common factor d such that a/d and b/d are both <= k.
   This allows us to use the pair (a/d, b/d) multiple times.
3. We use GCD of a and b to find the minimal number of operations needed.

Approach:
1. If a <= k && b <= k then answer is 1.
2. Find GCD of a and b.
3. Check if either (a/GCD) > k or (b/GCD) > k:
   - If yes, we must use at least 2 operations because no single pair works.
   - If no, we can use a single pair (a/GCD, b/GCD), so answer is 1.
*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Security.AccessControl;
using System.Text;
namespace TestingStuff;
#region Вспомогательные штуки
public class CustomComparer<T> : IComparer<T> {
  private Func<T?, T?, int> compareFunc;
  public CustomComparer(Func<T?, T?, int> compareFunc) => this.compareFunc =
      compareFunc;
  public int Compare(T? x, T? y) => compareFunc(x, y);
}
public static class MathExtensions {
  public static T CeliDiv<T>(this T a, T b)
      where T : INumber<T> { return (a + b - T.One) / b; }
  public static T Gcd<T>(this T a, T b)
      where T : INumber<T> {
    while (!T.IsZero(a) && !T.IsZero(b)) {
      if (a > b)
        a %= b;
      else
        b %= a;
    }
    return T.IsZero(a) ? b : a;
  }
  public static T Gcd<T>(this IReadOnlyList<T> arr)
      where T : INumber<T> {
    T gcd = arr[0];
    for (int i = 1; i < arr.Count; i++) {
      gcd = gcd.Gcd(arr[i]);
    }
    return gcd;
  }
  public static T Lcm<T>(this T a, T b)
      where T : INumber<T> { return a / Gcd(a, b) * b; }
  public static T BinPow<T>(this T x, T pow)
      where T : INumber<T>, IBinaryInteger<T> {
    T ret = T.One;
    pow = T.Abs(pow);
    while (pow != T.Zero) {
      if ((pow & T.One) == T.One)
        ret *= x;
      x *= x;
      pow >>= 1;
    }
    return ret;
  }
  public static T BinPow<T>(this T x, T pow, T mod)
      where T : INumber<T>, IBinaryInteger<T> {
    T ret = T.One;
    x %= mod;
    pow = T.Abs(pow);
    while (pow != T.Zero) {
      if ((pow & T.One) == T.One) {
        ret *= x;
        ret %= mod;
      }
      x *= x;
      x %= mod;
      pow >>= 1;
    }
    return ret;
  }
  public static T GetMaxBit<T>(this T num)
      where T : INumber<T>, IBinaryInteger<T> {
    int res = int.CreateChecked(T.Log2(num));
    return T.One << res;
  }
  public static IReadOnlyList<T> GetDigits<T>(this T num)
      where T : INumber<T> {
    List<T> ret = new List<T>(18);
    T ten = T.CreateChecked(10);
    while (num != T.Zero) {
      ret.Add(num % ten);
      num /= ten;
    }
    return ret;
  }
}
public static class CollectionExtensions {
  public static (T, int, T, int) MinIndexMaxIndex<T>(this IReadOnlyList<T> arr)
      where T : INumber<T> {
    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < arr.Count; i++) {
      if (arr[i] < arr[minIndex])
        minIndex = i;
      if (arr[i] > arr[maxIndex])
        maxIndex = i;
    }
    return (arr[minIndex], minIndex, arr[maxIndex], maxIndex);
  }
  public static int LowerBoundIndex<T>(this IReadOnlyList<T> arr, T value)
      where T : INumber<T> {
    int left = -1, right = arr.Count;
    while (right - left > 1) {
      int mid = (left + right) >> 1;
      if (arr[mid] < value)
        left = mid;
      else
        right = mid;
    }
    return right;
  }
  public static int UpperBoundIndex<T>(this IReadOnlyList<T> arr, T value)
      where T : INumber<T> {
    int left = -1, right = arr.Count;
    while (right - left > 1) {
      int mid = (left + right) >> 1;
      if (arr[mid] <= value)
        left = mid;
      else
        right = mid;
    }
    return right;
  }
}
#endregion

public static class Program {
  public static void Main() {
    var t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      long a = long.Parse(parts[0]);
      long b = long.Parse(parts[1]);
      long k = long.Parse(parts[2]);
      
      if (a <= k && b <= k) {
        Console.WriteLine(1);
        continue;
      }
      
      long gcd = a.Gcd(b); // Compute GCD of a and b
      /*
       * If after dividing by GCD:
       * - a/gcd > k or b/gcd > k, then we can't achieve with one pair,
       *   so must spend at least 2 operations.
       * - Else we can use single pair (a/gcd, b/gcd)
       */
      if (gcd == 1 || (a / gcd) > k || (b / gcd) > k) {
        Console.WriteLine(2);
      } else {
        Console.WriteLine(1);
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/