// Problem: CF 2144 A - Cut the Array
// https://codeforces.com/contest/2144/problem/A

/*
 * Problem: Cut the Array
 * 
 * Algorithm/Techniques: Greedy approach with prefix sum and modulo operations.
 * 
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(n) for storing the array and prefix sums.
 * 
 * The solution checks whether the total sum of the array is divisible by 3.
 * If yes, it's always possible to split into three parts with equal remainders (0).
 * Otherwise, we just output 0 0 as no valid cut exists under given constraints.
 */

import java.io.*;
import java.util.StringTokenizer;

public class cutthearray {
    public static void main(String[] args)throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        int t = Integer.parseInt(br.readLine().trim()); // Read number of test cases
        StringTokenizer st;
        while(t-->0){
            int n = Integer.parseInt(br.readLine().trim()); // Read size of array
            st = new StringTokenizer(br.readLine().trim()); // Read elements
            int[] arr = new int[n]; // Array to store input elements
            int sum = 0; // Variable to store total sum
            for(int i = 0; i < n; i++){
                arr[i] = Integer.parseInt(st.nextToken()); // Parse each element
                sum += arr[i]; // Add to total sum
            }
            if(sum % 3 != 0){
                sb.append(0+" "+0).append('\n'); // If sum not divisible by 3, no valid split
            }else{
                sb.append(1+" "+2).append('\n'); // Otherwise, output any valid indices (1 2 works for all)
            }
        }
        System.out.print(sb); // Print the result
    }
}


// https://github.com/VaHiX/codeForces/