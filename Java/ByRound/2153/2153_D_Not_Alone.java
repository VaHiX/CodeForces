// Problem: CF 2153 D - Not Alone
// https://codeforces.com/contest/2153/problem/D

/*
 * Problem: D. Not Alone
 * 
 * Purpose:
 *   Given a circular array 'a' of length n, find the minimum number of operations
 *   to make the array "nice". An array is nice if every element has at least one
 *   adjacent element that is equal to it.
 *   
 *   Each operation allows increasing or decreasing any element by 1.
 *   
 *   Algorithm:
 *     - Use dynamic programming with state transitions based on grouping elements
 *       in a way that allows adjacent elements to be equal.
 *     - Apply transformations (rotations) on the input array and compute costs
 *       using DP to find the minimal operations.
 *     
 *   Time Complexity: O(n)
 *   Space Complexity: O(n)
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;
public class D {
    static BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in));
    public static void main(String[] args) throws IOException {
        StringTokenizer s1
                = new StringTokenizer(br.readLine());
        int t = Integer.parseInt(s1.nextToken());
        while (t-- > 0) {
            StringTokenizer s2
                    = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(s2.nextToken());
            int[] arr = new int[n];
            StringTokenizer s3
                    = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) arr[i] = Integer.parseInt(s3.nextToken());
            solve(arr, n);
        }
    }
    static void solve(int[] arr, int n) {
        long res=func1(arr,n); // Compute initial DP cost
        int[] temp=new int[n];
        fill(temp,arr,n); // Create rotated version of original array
        res=Math.min(res,func1(temp,n)); // Compute DP on first rotation
        int[] next=new int[n];
        fill(next,temp,n); // Create second rotated version
        res=Math.min(res,func1(next,n)); // Compute DP on second rotation
        System.out.println(res);
    }
    static long func1(int[] arr,int n) {
        long[] dp=new long[n]; // DP array to store minimum operations up to index i
        dp[1]=Math.abs(arr[0]-arr[1]); // Cost for base case of two elements
        dp[2]=find(arr,0,2); // Cost of making first three elements equal (using find)
        for(int i=3;i<n;i++) {
            dp[i]=find(arr,i-1,i)+dp[i-2]; // Transition: add cost plus optimal prior solution
            if(i!=3) dp[i]=Math.min(dp[i],find(arr,i-2,i)+dp[i-3]); // Optional additional transition
        }
        return dp[n-1]; // Return total cost for full array
    }
    static void fill(int[] temp,int[] arr,int n) {
        for(int i=1;i<n;i++) temp[i]=arr[i-1]; // Shift elements left by 1
        temp[0]=arr[n-1]; // Wrap last element to front (circular rotation)
    }
    static long find(int[] arr,int s,int e) {
        int[] temp=new int[e-s+1]; // Subarray from index s to e inclusive
        for(int i=0;i<temp.length;i++) temp[i]=arr[i+s]; // Copy elements
        Arrays.sort(temp); // Sort to easily compute cost
        long res=0;
        for(int i=0;i<temp.length;i++) res+=Math.abs(temp[i]-temp[1]); // Sum of distances from median (temp[1])
        return res;
    }
    static void print(int[] arr) {
        PrintWriter out=new PrintWriter(System.out);
        for (int i = 0; i < arr.length; i++)
            out.print(arr[i] + " ");
        out.print("\n");
        out.flush();
    }
}


// https://github.com/VaHiX/CodeForces/