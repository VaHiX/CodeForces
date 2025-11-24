// Problem: CF 2124 B - Minimise Sum
// https://codeforces.com/contest/2124/problem/B

/*
 * Problem: B. Minimise Sum
 * Purpose: Given an array of integers, we can perform at most one operation where we choose two indices i < j,
 *          add a[j] to a[i], and set a[j] = 0. The goal is to minimize the sum of prefix minimums.
 *
 * Algorithm/Techniques:
 * - Greedy approach: For n=2, we directly compute result using min of elements.
 * - For n>=3, we consider that the first element's contribution in prefix minimums is always a[0].
 *   The second element contributes min(a[0], a[1]), and the rest contribute min prefix up to that point.
 *   To minimize total sum, we try to reduce the effect of later elements by possibly merging with smaller ones.
 *   We look at how changing elements affects prefix mins efficiently — in this case, when n >= 3,
 *   the optimal is to add the smallest element (excluding first) to first element and compute a[0] + min(a[0], a[1]).
 *
 * Time Complexity: O(n) per test case – single pass through array.
 * Space Complexity: O(1) – only using fixed extra variables.
 */

import java.util.*;
public class Main{
	public static void main(String []args){
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		while(t-->0){
			int n = sc.nextInt();
			int arr[] = new int[n];
			for(int i=0;i<n;i++) arr[i]=sc.nextInt(); // Read array elements
			long sum =0;
			if(n==2) sum = arr[0] + Math.min(arr[0],arr[1]); // For two elements, direct formula
			else sum = Math.min(arr[0],arr[1])+arr[0]; // For more than two, optimal is to merge second smallest with first
			System.out.println(sum);
		}
	}
}


// https://github.com/VaHiX/CodeForces/