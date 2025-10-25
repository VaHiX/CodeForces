// Problem: CF 2122 E - Greedy Grid Counting
// https://codeforces.com/contest/2122/problem/E

/*
E. Greedy Grid Counting

Task:
Given a 2×n grid where each cell has a value between 1 and k (with -1 representing an empty cell),
count how many ways to fill the grid such that in every subgrid there exists a greedy path
that achieves the maximum possible sum.

Approach:
- Use dynamic programming on the second row.
- Define dp[x][i] = number of ways to fill first x columns with ending value i in row 2.
- Also keep track of "never" states that lead to invalid paths (those where the sum is too low).
- Handle different cases based on whether cells are filled or not (-1, or specific values).
- Time complexity: O(n * k^2)
- Space complexity: O(n * k)

*/
import java.util.*;
import java.io.*;
public class E {
  public static void main(String[] args) throws IOException {
    BufferedReader rr = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(System.out);
    StringTokenizer st = new StringTokenizer(rr.readLine());
    int T = Integer.parseInt(st.nextToken());
    while(T-- > 0) {
      st = new StringTokenizer(rr.readLine());
      int n = Integer.parseInt(st.nextToken());
      int k = Integer.parseInt(st.nextToken());
      int[] a = new int[n - 1];
      int[] b = new int[n - 1];
      long coeff = 1;
      long mod = 998244353;
      st = new StringTokenizer(rr.readLine());
      if(Integer.parseInt(st.nextToken()) == -1) {coeff *= k;} // First cell in row 1 is unfilled
      for(int i = 0; i < n - 1; i++) {
        a[i] = Integer.parseInt(st.nextToken());
      }
      st = new StringTokenizer(rr.readLine());
      for(int i = 0; i < n - 1; i++) {
        b[i] = Integer.parseInt(st.nextToken());
      }
      if(Integer.parseInt(st.nextToken()) == -1) {coeff *= k;} // Last cell in row 2 is unfilled
      if(n == 1) {
        pw.println(coeff);
      } else {
        long[][] dp = new long[n - 1][k]; 
        long[] never = new long[n - 1]; // Tracks invalid paths that go below threshold
        
        // Initialize first column based on constraints
        if(a[0] != -1 && b[0] != -1) {
          int diff = b[0] - a[0];
          if(diff <= 0) {
            never[0] = coeff;
          } else {
            dp[0][diff] = coeff;
          }
        } else if(a[0] != -1) {
          never[0] = coeff * a[0];
          for(int i = 1; i <= k - a[0]; i++) {
            dp[0][i] = coeff;
          }
        } else if(b[0] != -1) {
          never[0] = coeff * (k - b[0] + 1);
          for(int i = 1; i < b[0]; i++) {
            dp[0][i] = coeff;
          }
        } else {
          never[0] = (coeff * (k + 1) * k/2)%mod;
          for(int i = 1; i < k; i++) {
            dp[0][i] = coeff * (k - i);
          }
        }

        for(int x = 1; x < n - 1; x++) {
          if(a[x] != -1 && b[x] != -1) {
            int diff = b[x] - a[x];
            if(diff <= 0) {
              never[x] += never[x - 1]; // All previous invalid combinations continue to be invalid
              never[x] %= mod;
              for(int i = k - 1; i + diff >= 0; i--) {
                dp[x][i + diff] += dp[x - 1][i];
                dp[x][i + diff] %= mod;
              }
            } else {
              dp[x][diff] += never[x - 1]; // Add up invalid paths
              dp[x][diff] %= mod;
              for(int i = 0; i < k; i++) {
                dp[x][diff] += dp[x - 1][i];
                dp[x][diff] %= mod;
              }
            }
          } else if(a[x] != -1) {
            for(int bb = 1; bb <= k; bb++) {
              int diff = bb - a[x];
              if(diff <= 0) {
                never[x] += never[x - 1];
                never[x] %= mod;
                for(int i = k - 1; i + diff >= 0; i--) {
                  dp[x][i + diff] += dp[x - 1][i];
                  dp[x][i + diff] %= mod;
                }
              } else {
                dp[x][diff] += never[x - 1];
                dp[x][diff] %= mod;
                for(int i = 0; i < k; i++) {
                  dp[x][diff] += dp[x - 1][i];
                  dp[x][diff] %= mod;
                }
              }
            }
          } else if(b[x] != -1) {
            for(int aa = 1; aa <= k; aa++) {
              int diff = b[x] - aa;
              if(diff <= 0) {
                never[x] += never[x - 1];
                never[x] %= mod;
                for(int i = k - 1; i + diff >= 0; i--) {
                  dp[x][i + diff] += dp[x - 1][i];
                  dp[x][i + diff] %= mod;
                }
              } else {
                dp[x][diff] += never[x - 1];
                dp[x][diff] %= mod;
                for(int i = 0; i < k; i++) {
                  dp[x][diff] += dp[x - 1][i];
                  dp[x][diff] %= mod;
                }
              }
            }
          } else {
            for(int diff = -k + 1; diff <= k - 1; diff++) {
              long mult = k - Math.abs(diff);
              if(diff <= 0) {
                never[x] += never[x - 1]*mult;
                never[x] %= mod;
                for(int i = k - 1; i + diff >= 0; i--) {
                  dp[x][i + diff] += dp[x - 1][i]*mult;
                  dp[x][i + diff] %= mod;
                }
              }
              if(diff > 0) {
                dp[x][diff] += never[x - 1] * mult;
                dp[x][diff] %= mod;
                for(int i = 0; i < k; i++) {
                  dp[x][diff] += dp[x - 1][i] * mult;
                  dp[x][diff] %= mod;
                }
              }
            }
          }
        }
        long ans = never[n - 2];
        for(int i = 0; i < k; i++) {
          ans += dp[n - 2][i];
          ans %= mod;
        }
        pw.println(ans);
      }
    }
    pw.close();
  }
}


// https://github.com/VaHiX/CodeForces/