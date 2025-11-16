// Problem: CF 2119 B - Line Segments
// https://codeforces.com/contest/2119/problem/B

/*
 * Problem: B. Line Segments
 * 
 * Purpose:
 * Determine if it's possible to reach from point (px, py) to point (qx, qy)
 * by performing exactly n moves, where each move has a fixed Euclidean distance ai.
 * 
 * Approach:
 * 1. Compute the direct distance between start and end points.
 * 2. Sum all distances in the array a[].
 * 3. Check whether it is possible to reach the destination using triangle inequality.
 *    Specifically, we ensure that max(a[i]) <= sum of all a[i] - max(a[i]) + direct_distance.
 *    
 * Time Complexity: O(n log n) due to sorting the array.
 * Space Complexity: O(n) for storing the array of distances.
 */

import java.util.*;
import java.lang.*;
import java.io.*;
public class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		Scanner sc=new Scanner(System.in);
		int T=sc.nextInt();
		for(int h=0;h<T;h++){
		    int n=sc.nextInt(); // Number of operations
		    int px=sc.nextInt(); // Start x-coordinate
		    int py=sc.nextInt(); // Start y-coordinate
		    int qx=sc.nextInt(); // End x-coordinate
		    int qy=sc.nextInt(); // End y-coordinate
    		double arr[]=new double[n+1]; // Array to store distances, plus one for direct distance
    		arr[n]=Math.sqrt(Math.pow(px-qx,2)+Math.pow(py-qy,2)); // Direct distance from start to end point
    		double sum=arr[n]; // Initialize sum with the direct distance
    		for(int i=0;i<n;i++){
    		    arr[i]=sc.nextDouble(); // Read each operation distance
    		    sum=sum+arr[i]; // Add it to the total distance sum
    		}
    		Arrays.sort(arr); // Sort array to find maximum element easily
    		sum=sum-arr[n]; // Subtract the direct distance from sum to get total of move distances
    		if(arr[n]>sum) // If the direct distance exceeds the sum of moves, it's impossible
    		System.out.println("No");
    		else
    		System.out.println("Yes"); // Otherwise, it is possible
		}
	}
}


// https://github.com/VaHiX/CodeForces/