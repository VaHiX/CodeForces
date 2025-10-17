// Problem: CF 2152 A - Increase or Smash
// https://codeforces.com/contest/2152/problem/A

/**
 * Problem: A. Increase or Smash
 * Purpose: Find the minimum number of operations (Increase and Smash) to transform an array of zeros into a target array.
 * Algorithms/Techniques: Hashmap for tracking unique values, greedy approach.
 * 
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(n) for storing unique elements in hashmap.
 */
import java.util.*;
import java.lang.Math;
public class Main {
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int t=s.nextInt(); // Read number of test cases
		for(int j=0;j<t;j++) {
			int n=s.nextInt(); // Read size of the array
			HashMap<Integer,Integer> hash=new HashMap(); // Hashmap to store unique values from the target array
			for(int i=0;i<n;i++) 
				hash.put(s.nextInt(), 1); // Add each element to hashmap (only unique elements matter)
			System.out.println(2*hash.size()-1); // Minimum operations = 2 * unique_elements - 1
		}
	}
}


// https://github.com/VaHiX/CodeForces/