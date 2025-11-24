// Problem: CF 2121 C - Those Who Are With Us
// https://codeforces.com/contest/2121/problem/C

/*
 * Problem: C. Those Who Are With Us
 * 
 * Purpose: Given an n x m matrix of integers, determine the minimal possible maximum value 
 *          after performing exactly one operation where we decrease all elements in a 
 *          specified row and column by 1.
 * 
 * Approach:
 * - Find the maximum element in the matrix.
 * - For each cell with maximum value, track how many times it is affected by rows/columns,
 *   storing row and column counts.
 * - Determine if there exists any position such that when we perform the operation,
 *   the maximum value can be reduced.
 * - If not, return max_value - 1; otherwise return max_value.
 * 
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n + m) for storing row/column counts and auxiliary arrays.
 */

import java.util.*;
public class Main
{
	public static void main(String[] args) {
	    Scanner sc=new Scanner(System.in);
	    int tt=sc.nextInt();
	    while(tt-->0){
	        int n=sc.nextInt();
	        int m=sc.nextInt();
	        int arr1[]=new int[n]; // Tracks how many times each row has max value
	        int arr2[]=new int[m]; // Tracks how many times each column has max value
	        int arr[][]=new int[n][m];
	        int maxi=0;
	        for(int i=0;i<n;i++){
	            for(int j=0;j<m;j++){
	                arr[i][j]=sc.nextInt();
	                maxi=Math.max(maxi,arr[i][j]);
	            }
	        }
	        int cnt=0; // Count of maximum elements
	        for(int i=0;i<n;i++){
	            for(int j=0;j<m;j++){
	                if(arr[i][j]==maxi){
	                    cnt++;
	                    arr1[i]++;
	                    arr2[j]++;
	                }
	            }
	        }
	       int f=0;
	      for(int i=0;i<n;i++){
	          for(int j=0;j<m;j++){
	              if(arr[i][j]==maxi){ // If current element is maximum
	                  if(arr1[i]+arr2[j]>cnt){ // If combined row+col count > total max elements
	                      f=1;
	                  }
	              }else if(arr1[i]+arr2[j]>=cnt){ // If operation affects non-maximum element
	                  f=1;
	              }
	          }
	      }
	        System.out.println(f==0?maxi:maxi-1); // Minimize the maximum by reducing it by 1 if needed
	    }
	}
}


// https://github.com/VaHiX/CodeForces/