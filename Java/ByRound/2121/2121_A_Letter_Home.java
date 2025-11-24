// Problem: CF 2121 A - Letter Home
// https://codeforces.com/contest/2121/problem/A

/*
 * Problem: A. Letter Home
 * Purpose: Find the minimum number of steps to visit all given positions starting from position 's'.
 * 
 * Algorithm/Techniques:
 * - Sort the array of positions (already sorted in input)
 * - Calculate the distance between the first and last position in the array (min to max).
 * - Calculate the minimum distance from the starting position 's' to either end of the range.
 * - Total steps = distance between ends + min(start to end).
 * 
 * Time Complexity: O(n) per test case, where n is the number of positions.
 * Space Complexity: O(n), for storing the array of positions.
 */

import java.util.*;
public class Main
{
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt(); // Read number of test cases
		while(t-->0){
		    int n=sc.nextInt(); // Read number of positions to visit
		    int s=sc.nextInt(); // Read starting position
		    int a[]=new int[n]; // Create array to store positions
		    for(int i=0;i<n;i++){
		        a[i]=sc.nextInt(); // Read each position
		    }
		    int min=a[0]; // First (minimum) position in sorted array
		    int max=a[n-1]; // Last (maximum) position in sorted array
		    int distance=max-min; // Distance between first and last position
		    int test=Math.min(Math.abs(s-min),Math.abs(s-max)); // Min dist from start to either end
		    int output=distance+test; // Total steps needed
		    System.out.println(output);
		}
	}
}


// https://github.com/VaHiX/CodeForces/