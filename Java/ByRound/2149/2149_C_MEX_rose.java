// Problem: CF 2149 C - MEX rose
// https://codeforces.com/contest/2149/problem/C

/*
 * Problem: C. MEX rose
 * Purpose: To find the minimum number of operations to make the MEX (minimum excluded) of an array equal to k.
 * Approach:
 *   - Count how many elements are less than k and store them in a set to determine unique values.
 *   - Count how many elements are exactly equal to k.
 *   - Calculate two possible outcomes:
 *     1. The number of operations needed to ensure all values from 0 to k-1 are present (ans = k - set.size())
 *     2. The number of operations needed to remove all occurrences of k (sames)
 *   - Return the maximum of these two values.
 *
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) for storing the set of elements less than k.
 */

import java.util.*;
public class Main
{
	public static void main(String[] args) {
	    Scanner sc= new Scanner(System.in);
	    int t=sc.nextInt(); // Read number of test cases
	    while(t-- >0){
	        int n=sc.nextInt(); // Read array length
	        int k=sc.nextInt(); // Read target MEX value
	        int sames=0; // Count of elements equal to k
	        int[] arr=new int[n]; // Input array
	        Set<Integer> set=new HashSet<>(); // Store unique elements less than k
	        for(int i=0;i<n;i++){
	            arr[i]=sc.nextInt();
	            if(k==arr[i]){ // If current element equals k
	                sames++; // Increment count of elements equal to k
	            }
	            if(arr[i]<k){ // If current element is less than k
	                set.add(arr[i]); // Add to the set to track unique values
	            }
	        }
	        int ans=k-set.size(); // Operations needed to fill 0 to k-1
	        System.out.println(Math.max(ans,sames)); // Return max of two strategies
	    }
	}
}


// https://github.com/VaHiX/CodeForces/