// Problem: CF 2148 D - Destruction of the Dandelion Fields
// https://codeforces.com/contest/2148/problem/D

/*
 * Problem: Destruction of the Dandelion Fields
 * 
 * Purpose:
 * Farmer John wants to maximize the number of dandelions he can cut by visiting n fields in an optimal order.
 * The lawnmower toggles its state when visiting a field with an odd number of dandelions.
 * If the mower is ON, all dandelions in that field are cut; otherwise, none are cut.
 *
 * Algorithm:
 * 1. Sort the array of dandelions in ascending order.
 * 2. Identify and collect all odd values into a separate array.
 * 3. Calculate initial sum of all fields.
 * 4. To maximize the result, we must keep at least one odd-numbered field to turn the mower ON,
 *    but only cut the largest odd numbers (as they are contributing the most to the final sum).
 *    We remove the smallest half of the sorted odds from the total sum to ensure optimal state management.
 *
 * Time Complexity: O(n log n) - due to sorting step
 * Space Complexity: O(n) - for storing arrays of size n
 */
import java.util.Arrays;
import java.util.Scanner;
public class Main {
	public static void main(String[] args) {
	 Scanner s = new Scanner(System.in);
	 int t= s.nextInt();
	 while(t-->0){
	     int n = s.nextInt();
	    long [] a = new long[n];
	    for(int i = 0;i<n;i++)
	    {
	        a[i]=s.nextLong(); // Read input values
	    }
	    Arrays.sort(a); // Sort the array to process in ascending order
	    long sum = 0;
	    int k = 0; // Flag to check if there's any odd number
	    long [] odd = new long[n]; // Store odd numbers
	    int m=0; // Count of odd numbers
	    for(int i= n-1;i>=0;i--){ // Traverse from largest to smallest
	        if(a[i]%2==1) // Check if current number is odd
	          {k=1;
	           odd[m]=a[i];
	          m++;} // Store the odd number and increment count
	         sum+=a[i]; // Add to total sum regardless of parity
	    }
	    int temp = m%2==0 ? m/2:m/2+1; // Decide how many odds to exclude (to keep at least one odd turned on)
	    for(int i = m-1;i>=temp;i--){ // Subtract the smaller odd values from sum to optimize final result
	        sum = sum-odd[i];
	    }
	    if(k==0) // If no odd numbers exist, mower stays off and no cutting occurs
	     System.out.println(0);
	    else{
	        System.out.println(sum); // Output the maximum cut possible
	    }
	 }
	s.close();
}
}

// https://github.com/VaHiX/codeForces/