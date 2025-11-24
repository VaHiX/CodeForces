// Problem: CF 1999 F - Expected Median
// https://codeforces.com/contest/1999/problem/F

/*
 * Problem: F. Expected Median
 * 
 * Algorithm/Techniques: Combinatorics, Mathematical Optimization
 * 
 * Time Complexity: O(n + k), where n is the length of the array
 * Space Complexity: O(n), for storing precomputed factorials and inverse factorials
 * 
 * This solution uses combinatorial mathematics to efficiently compute the sum
 * of all medians over all subsequences of length k. The key insight is to
 * count how many times each possible median value (0 or 1) appears as the median
 * in all valid subsequences.
 */
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.lang.invoke.MethodHandles;
import java.util.Random;
import java.util.StringTokenizer;
public class C1999F {
  static final int MOD = 1000000007;
  static final Random RAND = new Random();
  static final Combination COMB = new Combination(200000);
  static int solve(int[] a, int k) {
    int n = a.length;
    int[] cnt = new int[2];
    for (int i = 0; i < n; i++) {
      cnt[a[i]]++; // Count occurrences of 0s and 1s
    }
    // Determine valid range of median values
    int minh = Math.max((k+1)/2, k - cnt[0]);
    int maxh = Math.min(k, cnt[1]);
    int ans = 0;
    // For each possible count of 1s in the subsequence, calculate contribution
    for (int h = minh; h <= maxh; h++) {
      // Number of ways to choose h 1s from cnt[1] 1s
      // and (k-h) 0s from cnt[0] 0s
      ans = (int) ((ans + 1L * COMB.choose(cnt[0], k-h) * COMB.choose(cnt[1], h)) % MOD);
    }
    return ans;
  }
  static class Combination {
    final int n;
    int[] fact;
    int[] finv;
    public Combination(int n) {
      this.n = n;
      this.fact = new int[n+1];
      this.finv = new int[n+1];
      fact[0] = 1;
      finv[0] = 1;
      for (int i = 1; i <= n; i++) {
        fact[i] = (int) (((long) fact[i-1] * i) % MOD);
      }
      finv[n] = inverse(fact[n]);
      for (int i = n-1; i >= 1; i--) {
        finv[i] = (int) ((long)finv[i+1] * (i+1) % MOD);
      }
    }
    public int choose(int m, int k) {
      // Calculate combination C(m,k) = m! / (k! * (m-k)!)
      return (int) ((((long)fact[m] * finv[k] % MOD) * finv[m-k]) % MOD);
    }
    public static int inverse(long a) {
      // Calculate modular inverse using Fermat's little theorem
      return power(a, MOD - 2);
    }
    public static int power(long x, int y) {
      if (y == 0) {
        return 1;
      }
      x = x % MOD;
      long w = power(x, y / 2);
      w = (w * w) % MOD;
      return (int) (y % 2 == 0 ? w : (w * x) % MOD);
    }
    public static int[] computeInverseArr(int n) {
      int[] dp = new int[n+1];
      dp[1] = 1;
      for (int i = 2; i <= n; ++i) {
        dp[i] = (int) (MOD - (long) MOD / i * dp[MOD % i] % MOD);
      }
      return dp;
    }
    public int permute(int m, int k) {
      // Calculate permutation P(m,k) = m! / (m-k)!
      return (int) ((long)fact[m] * finv[m-k] % MOD);
    }
  }
  static int solveNaive(int[] a, int k) {
    int n = a.length;
    int[] cnt = new int[2];
    int ans = 0;
    // Brute force approach - generates all 2^n subsequences
    for (int i = 0; i < (1 << n); i++) {
      if (Integer.bitCount(i) != k) {
        continue;
      }
      cnt[0] = 0;
      cnt[1] = 0;
      for (int j = 0; j < n; j++) {
        if ((i & (1 << j)) != 0) {
          cnt[a[j]]++;
        }
      }
      // If 0s count < 1s count, median is 0
      ans = (ans + (cnt[0] < cnt[1] ? 1 : 0)) % MOD;
    }
    return ans;
  }
  static void test(int[] a, int k) {
    System.out.format("test(new int[] %s, %d);\n", trace(a), k);
    int ans = solve(a, k);
    int exp = a.length <= 28 ? solveNaive(a, k) : -1;
    System.out.format("Result: %d, Expected: %d\n", ans, exp);
  }
  public static void main(String[] args) {
    //doTest(); // Uncomment to run tests for verification
    MyScanner in = new MyScanner();
    int T = in.nextInt();
    for (int t = 1; t <= T; t++) {
      int n = in.nextInt();
      int k = in.nextInt();
      int[] a = in.nextIntArr(n);
      int ans = solve(a, k);
      System.out.println(ans);
    }
  }
  static void output(int[] a) {
    if (a == null) {
      System.out.println("-1");
      return;
    }
    StringBuilder sb = new StringBuilder();
    for (int v : a) {
      sb.append(v);
      sb.append(' ');
    }
    System.out.println(sb.toString());
  }
  static void myAssert(boolean cond) {
    if (!cond) {
      throw new RuntimeException("Unexpected");
    }
  }
  static String trace(int[][] a) {
    StringBuilder sb = new StringBuilder();
    sb.append('{');
    for (int i = 0; i < a.length; i++) {
      if (i > 0) {
        sb.append(',');
      }
      sb.append('{');
      for (int j = 0; j < a[i].length; j++) {
        if (j > 0) {
          sb.append(',');
        }
        sb.append(a[i][j]);
      }
      sb.append('}');
    }
    sb.append('}');
    return sb.toString();
  }
  static String trace(int[] a) {
    StringBuilder sb = new StringBuilder();
    sb.append('{');
    for (int v : a) {
      if (sb.length() > 1) {
        sb.append(',');
      }
      sb.append(v);
    }
    sb.append('}');
    return sb.toString();
  }
  static class MyScanner {
    BufferedReader br;
    StringTokenizer st;
    public MyScanner() {
      try {
        final String USERDIR = System.getProperty("user.dir");
        String cname = MethodHandles.lookup().lookupClass().getCanonicalName().replace(".MyScanner", "");
        cname = cname.lastIndexOf('.') > 0 ? cname.substring(cname.lastIndexOf('.') + 1) : cname;
        final File fin = new File(USERDIR + "/io/c" + cname.substring(1,4) + "/" + cname + ".in");
        br = new BufferedReader(new InputStreamReader(fin.exists()
            ? new FileInputStream(fin) : System.in));
      } catch (Exception e) {
        br = new BufferedReader(new InputStreamReader(System.in));
      }
    }
    public String next() {
      try {
        while (st == null || !st.hasMoreElements()) {
          st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
      } catch (Exception e) {
        throw new RuntimeException(e);
      }
    }
    public int nextInt() {
      return Integer.parseInt(next());
    }
    public long nextLong() {
      return Long.parseLong(next());
    }
    public int[] nextIntArr(int n) {
      int[] a = new int[n];
      for (int i = 0; i < n; i++) {
        a[i] = nextInt();
      }
      return a;
    }
    public int[][] nextIntArr2D(int n, int m) {
      int[][] a = new int[n][m];
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          a[i][j] = nextInt();
        }
      }
      return a;
    }
  }
}


// https://github.com/VaHiX/CodeForces/