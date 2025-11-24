// Problem: CF 2060 F - Multiplicative Arrays
// https://codeforces.com/contest/2060/problem/F

/*
Problem: F. Multiplicative Arrays
Purpose: Given integers k and n, count the number of integer arrays a such that:
1. 1 ≤ |a| ≤ n (length of array is between 1 and n)
2. 1 ≤ a_i ≤ k (elements are between 1 and k)
3. Product of all elements in array equals x (for each x from 1 to k)

Algorithm: Dynamic Programming with inclusion-exclusion principle
Time Complexity: O(k * log(k) + k * MAX_M) where MAX_M = 20
Space Complexity: O(k * MAX_M + MAX_M)

Note: The solution uses precomputed factorials and their modular inverses for efficient computation
of binomial coefficients and modular arithmetic operations.
*/

using System;
using System.Collections.Generic;
class Utility {
  public static void BFS(Dictionary<int, List<int>> graph, int start) {
    var queue = new Queue<int>();
    var visited = new HashSet<int>();
    queue.Enqueue(start);
    visited.Add(start);
    while (queue.Count > 0) {
      int node = queue.Dequeue();
      Console.Write(node + " ");
      foreach (var neighbor in graph[node]) {
        if (!visited.Contains(neighbor)) {
          visited.Add(neighbor);
          queue.Enqueue(neighbor);
        }
      }
    }
  }
  public static void DFS(Dictionary<int, List<int>> graph, int start,
                         HashSet<int> visited = null) {
    if (visited == null)
      visited = new HashSet<int>();
    visited.Add(start);
    Console.Write(start + " ");
    foreach (var neighbor in graph[start]) {
      if (!visited.Contains(neighbor))
        DFS(graph, neighbor, visited);
    }
  }
  public static long Phi(long n) {
    long ans = n;
    for (long i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        while (n % i == 0)
          n /= i;
        ans -= ans / i;
      }
    }
    if (n > 1)
      ans -= ans / n;
    return ans;
  }
  public static bool BinarySearch(int[] arr, int target) {
    int l = 0, r = arr.Length - 1;
    while (l <= r) {
      int mid = (l + r) / 2;
      if (arr[mid] == target)
        return true;
      else if (arr[mid] > target)
        r = mid - 1;
      else
        l = mid + 1;
    }
    return false;
  }
  public static long[][] MatrixMultiply(long[][] A, long[][] B, long mod) {
    int n = A.Length, m = B[0].Length, p = B.Length;
    var result = new long [n][];
    for (int i = 0; i < n; i++)
      result[i] = new long[m];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        long sum = 0;
        for (int k = 0; k < p; k++) {
          sum = (sum + A[i][k] * B[k][j] % mod) % mod;
        }
        result[i][j] = sum;
      }
    }
    return result;
  }
  public static long[][] MatrixExponentiation(long[][] matrix, int n,
                                              long mod) {
    int size = matrix.Length;
    var result = new long [size][];
    for (int i = 0; i < size; i++) {
      result[i] = new long[size];
      result[i][i] = 1;
    }
    var baseMatrix = matrix;
    while (n > 0) {
      if (n % 2 == 1)
        result = MatrixMultiply(result, baseMatrix, mod);
      baseMatrix = MatrixMultiply(baseMatrix, baseMatrix, mod);
      n /= 2;
    }
    return result;
  }
  public static bool IsPrime(long n, int k = 7) {
    if (n < 2)
      return false;
    if (n == 2 || n == 3)
      return true;
    if (n % 2 == 0)
      return false;
    long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
      d /= 2;
      s++;
    }
    var rand = new Random();
    for (int i = 0; i < k; i++) {
      long a = 2 + rand.Next() % (n - 2);
      long x = Power(a, d, n);
      if (x == 1 || x == n - 1)
        continue;
      bool composite = true;
      for (int r = 0; r < s - 1; r++) {
        x = Power(x, 2, n);
        if (x == n - 1) {
          composite = false;
          break;
        }
      }
      if (composite)
        return false;
    }
    return true;
  }
  public static long Power(long x, long y, long p) {
    long res = 1;
    x %= p;
    while (y > 0) {
      if ((y & 1) == 1)
        res = (res * x) % p;
      y >>= 1;
      x = (x * x) % p;
    }
    return res;
  }
  public static (long[], long[]) Factorials(int N, long MOD) {
    var fact = new long[N + 1];
    var invFact = new long[N + 1];
    fact[0] = invFact[0] = 1;
    for (int i = 1; i <= N; i++)
      fact[i] = fact[i - 1] * i % MOD;
    invFact[N] = Power(fact[N], MOD - 2, MOD);
    for (int i = N - 1; i >= 0; i--)
      invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    return (fact, invFact);
  }
  public static long NCR(int n, int r, long[] fact, long[] invFact, long MOD) {
    if (r > n)
      return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
  }
  public static List<long> Factors(long n) {
    var result = new List<long>();
    for (long i = 1; i * i <= n; i++) {
      if (n % i == 0) {
        result.Add(i);
        if (i != n / i)
          result.Add(n / i);
      }
    }
    return result;
  }
  public static long ModularInverse(long a, long m) {
    return Power(a, m - 2, m);
  }
  public static long BinaryExponentiation(long a, long b, long mod) {
    long res = 1;
    while (b > 0) {
      if (b % 2 == 1)
        res = (res * a) % mod;
      a = (a * a) % mod;
      b /= 2;
    }
    return res;
  }
}
class Program {
  const int MOD = 998244353;
  const int MAX_M = 20;
  static long ModPow(long a, long b, long mod) {
    long res = 1;
    a %= mod;
    while (b > 0) {
      if ((b & 1) == 1)
        res = res * a % mod;
      a = a * a % mod;
      b >>= 1;
    }
    return res;
  }
  static void Precompute(out long[] fact, out long[] inv_fact,
                         out long[] inv_num) {
    fact = new long[MAX_M + 1];
    inv_fact = new long[MAX_M + 1];
    inv_num = new long[MAX_M + 2];
    fact[0] = 1;
    for (int i = 1; i <= MAX_M; i++) {
      fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[MAX_M] = ModPow(fact[MAX_M], MOD - 2, MOD);
    for (int i = MAX_M - 1; i >= 0; i--) {
      inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
    for (int i = 1; i <= MAX_M + 1; i++) {
      inv_num[i] = ModPow(i, MOD - 2, MOD);
    }
  }
  static void Solve() {
    long[] fact, inv_fact, inv_num;
    Precompute(out fact, out inv_fact, out inv_num);
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] inputs = Console.ReadLine().Split();
      int k = int.Parse(inputs[0]);
      long n = long.Parse(inputs[1]);
      List<int>[] divisors = new List<int>[k + 1];
      for (int i = 0; i <= k; i++)
        divisors[i] = new List<int>();
      for (int d = 2; d <= k; d++) {
        for (int x = d; x <= k; x += d) {
          divisors[x].Add(d);
        }
      }
      long[,] F = new long[MAX_M + 1, k + 1];
      for (int x = 1; x <= k; x++) {
        if (x >= 2 && x <= k) {
          F[1, x] = 1;
        }
      }
      for (int m = 2; m <= MAX_M; m++) {
        for (int x = 1; x <= k; x++) {
          foreach (int d in divisors[x]) {
            if (x / d >= 1) {
              F[m, x] = (F[m, x] + F[m - 1, x / d]) % MOD;
            }
          }
        }
      }
      long[] C_nm = new long[MAX_M + 1];
      C_nm[0] = 1;
      for (int m = 1; m <= MAX_M; m++) {
        if (m > n) {
          C_nm[m] = 0;
        } else {
          long c = 1;
          for (int i = 0; i < m; i++) {
            c = c * ((n - i) % MOD) % MOD;
          }
          c = c * inv_fact[m] % MOD;
          C_nm[m] = c;
        }
      }
      long[] C_n1_m1 = new long[MAX_M + 1];
      for (int m = 1; m <= MAX_M; m++) {
        if (m > n) {
          C_n1_m1[m] = 0;
        } else {
          long c = C_nm[m];
          c = c * ((n + 1) % MOD) % MOD;
          c = c * inv_num[m + 1] % MOD;
          C_n1_m1[m] = c;
        }
      }
      long[] answer = new long[k + 1];
      for (int x = 1; x <= k; x++) {
        if (x == 1) {
          answer[x] = n % MOD;
        } else {
          long sum = 0;
          for (int m = 1; m <= MAX_M; m++) {
            if (m > n)
              continue;
            sum = (sum + (F[m, x] * C_n1_m1[m]) % MOD) % MOD;
          }
          answer[x] = sum;
        }
      }
      for (int x = 1; x <= k; x++) {
        Console.Write(answer[x] + (x < k ? " " : "\n"));
      }
    }
  }
  static void Main() { Solve(); }
}


// https://github.com/VaHiX/CodeForces/