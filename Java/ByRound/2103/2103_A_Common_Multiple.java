// Problem: CF 2103 A - Common Multiple
// https://codeforces.com/contest/2103/problem/A

/*
 * Problem: Maximum Size of Beautiful Subsequence
 * 
 * Description:
 * An array x_1, x_2, ..., x_m is beautiful if there exists an array y_1, y_2, ..., y_m
 * such that all elements in y are distinct and x_i * y_i is constant for all i.
 * Task is to find the maximum size of a subsequence of given array 'a' that is beautiful.
 * 
 * Approach:
 * The key insight is that for a beautiful subsequence, we need x_i * y_i = k (constant).
 * So, each element x_i must divide some value in y, and the products should be same.
 * This means in any valid beautiful subsequence, if we compute x_i * y_i = k,
 * then all elements x_i of that subsequence can be grouped together with distinct y_i.
 * 
 * The maximum number of distinct elements in a subsequence determines the answer,
 * since we just need to assign different y values to each unique x. 
 * So, simply compute how many distinct elements are present in array a.
 * 
 * Algorithm:
 * For each test case:
 *   - Read n
 *   - Read n integers into array
 *   - Count unique integers using HashSet
 *   - Output size of HashSet (maximum distinct elements)
 *   
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) for storing distinct elements in the HashSet.
 */

import java.util.*;
public class Main
{
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt(); // Read number of test cases
		while(t-->0){
		    int n=sc.nextInt(); // Read size of array
		    HashSet<Integer>hs=new HashSet(); // Use HashSet to store unique elements
		    for(int i=0;i<n;i++)
		        hs.add(sc.nextInt()); // Add each element to set (duplicates ignored)
		    System.out.println(hs.size()); // Print count of unique elements
		}
	}
}


// https://github.com/VaHiX/CodeForces/