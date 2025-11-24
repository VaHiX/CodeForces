// Problem: CF 1951 F - Inversion Composition
// https://codeforces.com/contest/1951/problem/F

/*
 * Problem: F. Inversion Composition
 * Purpose: Given a permutation p and target number of inversions k,
 *          find a permutation q such that inv(q) + inv(q * p) = k.
 * 
 * Algorithm:
 * 1. Compute the number of inversions in p, and store the count of how many
 *    elements are larger than the current element in the permutation p.
 * 2. Using binary indexed tree (Fenwick tree) to efficiently compute prefix sums.
 * 3. Adjust k to account for inversions in p alone.
 * 4. Split the search space to construct q such that inv(q) + inv(q * p) = k.
 * 5. Use greedy approach and careful construction to generate valid q.
 * 
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n) for arrays and data structures
 */
using System;
public class Program {
  static int n;
  static int[] p = new int[301000];  // mapping from value to index in permutation
  static int[] tr = new int[301000];  // Fenwick tree for counting elements
  static long m;  // adjusted target inversions
  static int[] jd = new int[300100];  // count of elements larger than current element in p
  static int[] q = new int[301000];  // result permutation q
  static int Ask(int x) {
    int s = 0;
    for (; x > 0; x -= (x & -x))  // Fenwick tree query
      s += tr[x];
    return s;
  }
  static void Ad(int x, int z) {
    for (; x <= n; x += (x & -x))  // Fenwick tree update
      tr[x] += z;
  }
  static void Sol() {
    string[] input = Console.ReadLine().Split();
    n = int.Parse(input[0]);
    m = long.Parse(input[1]);
    input = Console.ReadLine().Split();
    for (int i = 1; i <= n; i++) {
      p[int.Parse(input[i - 1])] = i;  // map value to its position in p
      tr[i] = 0;
    }
    long su = 0, sp = 0;
    for (int i = 1; i <= n; i++) {
      jd[i] = Ask(p[i]);  // count elements greater than p[i] in current prefix
      su += i - 1 - jd[i];  // accumulate inversions in p
      sp += jd[i];  // sum of elements larger than current element
      Ad(p[i], 1);  // update Fenwick tree
    }
    m -= su;  // adjust target to account for inversions in p
    if (m < 0 || (m & 1) != 0) {  // check if required value is feasible
      Console.WriteLine("NO");
      return;
    }
    m /= 2;  // divide by 2 to split between inv(q) and inv(q*p)
    if (m > sp) {  // check if it is possible to split
      Console.WriteLine("NO");
      return;
    }
    Console.WriteLine("YES");
    int xx = n + 1;
    for (int i = 1; i <= n; i++) {
      if (m > jd[i]) {
        m -= jd[i];  // reduce m by number of elements larger than current
      } else {
        xx = i;  // determine the cut point
        break;
      }
    }
    for (int i = xx + 1; i <= n; i++) {
      q[i] = i;  // initialize elements after xx to identity
    }
    var sb = new System.Collections.Generic.List<int>();  // prepare to build list
    for (int i = 1; i < xx; i++) {
      if (p[i] < p[xx]) {  // if i is smaller than xx in p
        sb.Add(xx - i);  // store difference
      }
    }
    q[xx] = m > 0 ? sb[(int)m - 1] : xx;  // assign value at cut point
    for (int i = 1; i < xx; i++) {
      q[i] = xx - i;  // assign to construct q
      if (q[i] >= q[xx])
        q[i]++;  // adjust indices to account for shift
    }
    for (int i = 1; i <= n; i++) {
      Console.Write(q[i] + " ");  // output the result
    }
    Console.WriteLine();
  }
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0)
      Sol();
  }
}


// https://github.com/VaHiX/CodeForces/