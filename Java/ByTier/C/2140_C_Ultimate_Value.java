// Problem: CF 2140 C - Ultimate Value
// https://codeforces.com/contest/2140/problem/C

/*
C. Ultimate Value
Time Complexity: O(n) per test case
Space Complexity: O(n) due to array storage and auxiliary variables

Algorithm:
This problem involves a game between Alice and Bob where they alternate turns trying to optimize the function f(a), defined as:
f(a) = cost + (a[0] - a[1] + a[2] - a[3] + ... +/- a[n-1])

Each player can either end the game or swap two elements of the array, which adds (r-l) to the cost.
Alice wants to maximize f(a) and Bob wants to minimize it.
Since players play optimally and there's a fixed number of operations allowed (up to 10^100), 
we need to consider how this affects the alternating sum.

We precompute an initial alternating sum (curr) based on even and odd indexed elements.
Then, we compute bounds for what the minimal and maximal values of the alternating sum can change
based on the possible operations, specifically by tracking max and min values over prefixes/suffixes
with respect to the influence of index parity.

The idea involves dynamic programming or greedy simulation of effects:
- For even indices: min changes
- For odd indices: max changes

This is not a traditional DP but rather an optimization approach to determine how much 
the alternating sum (and thus f(a)) can be altered by optimal swapping.
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;
import java.util.StringTokenizer;

public class codef {
	public static void main(String[] args) throws IOException {
    	 BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         PrintWriter out = new PrintWriter(System.out);
         StringTokenizer st=new StringTokenizer(br.readLine());
         int T=Integer.parseInt(st.nextToken());
         for(int t=0;t<T;t++) {
         st=new StringTokenizer(br.readLine());
         int n= Integer.parseInt(st.nextToken());
        long[] a=new long[n];
        st=new StringTokenizer(br.readLine());
        long curr=0; // compute initial alternating sum
        for(int i=0;i<n;i++) {
        	a[i]=Long.parseLong(st.nextToken());
        	if(i%2==0)
        		curr+=a[i];
        	else
        		curr-=a[i];
        }
        if(n==1)
        	out.println(a[0]);
        else {
        	 long min=2*a[0],max=2*a[1]-1; // initialize bounds for alternating sum changes
        	 long m=2*a[1]-2*a[0]+1; // compute initial difference bound, used to track max gain possible
        	 for(int i=2;i<n;i++) {
        		 if(i%2==0) { // even index: update min and m
        			 m=Math.max(m,max-2*a[i]+i); // update maximum change that can possibly occur from current prefix
        			 min=Math.min(min,2*a[i]+i); // track minimal value of 2*a[i] + i so far
        		 }
        		 else { // odd index: update max and m
        			 m=Math.max(m,2*a[i]+i-min); // update max change possible considering current element's contribution with earlier mins
        			 max=Math.max(max,2*a[i]-i); // track maximum value of 2*a[i] - i seen so far
        		 }
        	 }
        	 if(n%2==0)
        		 out.println(Math.max(curr+n-2,curr+m)); // account for final cost adjustments and maximum possible gains
        	 else
        		 out.println(Math.max(curr+n-1,curr+m)); 
        }
         }
         out.flush();
}
}


// https://github.com/VaHiX/codeForces/