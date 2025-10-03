// Problem: CF 2146 A - Equal Occurrences
// https://codeforces.com/contest/2146/problem/A

/*
 * Problem: Find the length of the longest balanced subsequence in a non-decreasing array.
 * 
 * A subsequence is balanced if all elements appear the same number of times.
 * 
 * Approach:
 * 1. For each possible frequency k (from 1 to n), count how many distinct numbers
 *    in the array occur at least k times.
 * 2. The product of this count and k gives a candidate for the longest balanced subsequence
 *    with that frequency.
 * 3. Return the maximum such product across all valid k values.
 *
 * Time Complexity: O(n^2), where n is the size of input array.
 * Space Complexity: O(101) = O(1), since we use a fixed-size frequency array of size 101.
 */

import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner sc=new Scanner (System.in);
        int t=sc.nextInt();
        while(t-->0){
            int n=sc.nextInt();
            int arr[]=new int[n];
            for(int i=0;i<n;i++){
                arr[i]=sc.nextInt(); // Read array elements
            }
            int freq[]=new int[101]; // Frequency array to count occurrences of each number (1-100)
            for(int i=0;i<n;i++){
                freq[arr[i]]++; // Count frequency of each element
            }
            int res=0; // Result to store maximum length of balanced subsequence
            for(int k=1;k<=n;k++){ // Try all possible frequencies from 1 to n
                int count=0;
                for(int i=1;i<=100;i++){
                    if(freq[i]>=k) // If element i occurs at least k times
                        count++; // Increment count of distinct elements with at least k occurrences
                }
                if(count*k>res) // Check if this combination gives a better result
                    res=count*k;
            }
            System.out.println(res); // Print the maximum length found
        }
    }
}


// https://github.com/VaHiX/CodeForces/