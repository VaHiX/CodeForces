// Problem: CF 2117 C - Cool Partition
// https://codeforces.com/contest/2117/problem/C

/*
C. Cool Partition
Algorithms/Techniques: Two-pointer technique with HashSet for tracking element presence
Time Complexity: O(n) per test case, where n is the size of the array
Space Complexity: O(n) for storing elements in hashsets

Problem:
Yousef wants to partition an array into contiguous segments such that each element in a segment also appears in the next segment.
Goal is to maximize the number of such segments.

Approach:
- Use two HashSets: one to track elements in current segment (`set`), another to track all elements seen so far (`supset`)
- Traverse the array and add each element to both sets
- When `set` equals `supset`, we've reached the end of a valid segment. Reset `set` and increment counter.
- Return maximum number of segments found.
*/

import java.util.*;
public class C_Cool_Partition {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        int tcs = sc.nextInt();
        while(tcs-- > 0) {
            int n = sc.nextInt();
            int arr[] = new int[n];
            for(int i=0; i<n; i++) arr[i] = sc.nextInt(); // Read array elements
            int p = 0; // Count of segments
            HashSet<Integer> set = new HashSet<>(); // Elements in current segment
            HashSet<Integer> supset = new HashSet<>(); // All elements seen so far
            for(int i=0; i<n; i++) {
                set.add(arr[i]); // Add to current segment elements
                supset.add(arr[i]); // Add to all seen elements
                if(set.equals(supset)) { // If all elements in current segment also appear in the rest of array so far
                    set.clear(); // Reset current segment
                    p++; // Increment segment count
                }
            }
            System.out.println(p);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/