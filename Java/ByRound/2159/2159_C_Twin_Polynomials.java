// Problem: CF 2159 C - Twin Polynomials
// https://codeforces.com/contest/2159/problem/C

/*
C. Twin Polynomials
Algorithms/Techniques: Dynamic Programming, Math, Graph Theory (Cycle Detection and Counting), Modular Arithmetic

Time Complexity: O(N) where N is the maximum possible degree of polynomial, as we precompute
                 the count array up to N and process each test case in O(N) time.

Space Complexity: O(N) for storing the count array and auxiliary data structures per test case.
*/

import java.io.*;
import java.util.*;
public class C1058{
   public static long MOD = 1000000007L;
   public static void main(String[] args)throws IOException{
      BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
      PrintWriter out = new PrintWriter(System.out);
      int N = 400005;
      long[] count = new long[N];
      count[0] = 1L;
      count[1] = 2L;
      // Precompute the number of ways to assign values for cycles
      for(int k = 2; k < N; k++){
         count[k] = (2L * count[k-1] + count[k-2] * (long)(k-1) + MOD)%MOD;
      }
      int t = Integer.parseInt(f.readLine());
      for(int q = 1; q <= t; q++){
         int n = Integer.parseInt(f.readLine());
         StringTokenizer st = new StringTokenizer(f.readLine());
         int[] array = new int[n+1];
         HashSet<Integer> hset = new HashSet<Integer>();
         boolean fail = false;
         // Parse input and validate initial values
         for(int k = 0; k <= n; k++){
            array[k] = Integer.parseInt(st.nextToken());
            if(array[k] > 0 && (hset.contains(array[k]) || array[k] > n)){
               fail = true;
            }
            hset.add(array[k]);
         }
         // Check for invalid structure
         if(!fail){
            for(int k = 1; k <= n; k++){
               if(array[k] == k || array[k] == 0 || array[k] == -1) continue;
               if(array[array[k]] != k && array[array[k]] != -1) fail = true;
            }
         }
         if(fail){
            out.println("0");
            continue;
         }
         // Process the array to identify cycles and set symmetric connections
         for(int k = 1; k <= n; k++){
            if(array[k] == k || array[k] == 0 || array[k] == -1) continue;
            array[array[k]] = k;
         }
         int empty = 0;
         // Count number of unassigned variables (marked as -1)
         for(int k = 1; k <= n; k++){
            if(array[k] == -1){
               empty++;
            }
         }
         long answer = count[empty];
         // Adjust for special condition where last element is unassigned
         if(array[n] == -1){
            answer = ((answer - count[empty-1])%MOD + MOD)%MOD;
         }
         out.println(answer);
      }
      out.close();
   }
}


// https://github.com/VaHiX/CodeForces/