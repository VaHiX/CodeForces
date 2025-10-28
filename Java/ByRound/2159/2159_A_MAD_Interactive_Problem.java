// Problem: CF 2159 A - MAD Interactive Problem
// https://codeforces.com/contest/2159/problem/A

/*
 * Problem: Find a secret sequence of length 2n where each number from 1 to n appears exactly twice.
 * Algorithm: 
 * 1. First pass: For each position, check if adding it to a growing list gives a MAD > 0.
 *    If yes, store the MAD value and backtrack.
 * 2. Second pass: For positions with 0 in the answer array, use the stored indices to determine values.
 * 
 * Time Complexity: O(n^2) - At most 3n queries, each query takes O(n) time in worst case.
 * Space Complexity: O(n) - For storing the answer array and auxiliary lists.
 */
import java.util.*;
import java.lang.*;
import java.io.*;
public class main
{
    static Scanner sc=new Scanner(System.in);
	public static void main (String[] args) throws java.lang.Exception
	{
		int t=sc.nextInt();
		while(t-->0)
		{
		    int n=sc.nextInt();
		    int ans[]=new int[2*n]; // Stores the final result sequence
		    ArrayList<Integer> al=new ArrayList<>(),al2=new ArrayList<>(); // al: for first pass, al2: for second pass
		    al.add(1); // Start with first element
		    for(int i=1;i<2*n;i++){ // Iterate through indices 1 to 2n-1
		        al.add(i+1); // Add next index to the list
		        int g=query(al); // Query the current subset
		        if(g==0){ // If MAD is 0, this index doesn't help identify duplicates
		        }else{ // If MAD > 0, we found a duplicate number that appears at least twice
		            ans[i]=g; // Store that number in current position
		            al.remove(al.size()-1); // Remove last added index
		            al2.add(i+1); // Add to second list for later processing
		        }
		    }
		    for(int i=0;i<2*n;i++){
		        if(ans[i]==0){ // If position not filled yet
		            al2.add(i+1); // Add index to list
		            int g=query(al2); // Query to find MAD
		            ans[i]=g; // Store the result
		            al2.remove(al2.size()-1); // Remove the index to keep list clean
		        }
		    }
		    System.out.print("! "); // Print answer marker
		    for(int i=0;i<2*n;i++)
		    System.out.print(ans[i]+" "); // Print the answer
		    System.out.println(); // New line
		}
	}
	public static int query(ArrayList<Integer> al) // Function to make a query and return MAD
	{
	    System.out.print("? "+al.size()+" ");
	    for(int i=0;i<al.size();i++)
	    System.out.print(al.get(i)+" ");
	    System.out.println();
	    int g=sc.nextInt();
	    return g;
	}
}


// https://github.com/VaHiX/CodeForces/