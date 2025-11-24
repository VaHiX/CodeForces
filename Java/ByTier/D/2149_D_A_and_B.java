// Problem: CF 2149 D - A and B
// https://codeforces.com/contest/2149/problem/D

/*
 * Problem: D. A and B
 * Purpose: Find the minimum number of adjacent swaps to make all characters of one type ('a' or 'b') form a single continuous block.
 *
 * Algorithm:
 * - For each character type ('a' and 'b'), collect their positions in lists.
 * - For each list, compute the minimum cost to align those positions into a contiguous block.
 * - The cost is calculated as the sum of distances from the median position.
 * - Time Complexity: O(n) per test case (linear scan and median-based cost calculation)
 * - Space Complexity: O(n) for storing positions of characters
 */

import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        while(t-- > 0){
            int n = sc.nextInt(); // Read length of the string
            String s = sc.next(); // Read the string
            List<Integer> a = new ArrayList<>(); // Store positions of 'a'
            List<Integer> b = new ArrayList<>(); // Store positions of 'b'
            for(int i = 0; i < n; i++){
                if(s.charAt(i) == 'a')
                    a.add(i);
                else
                    b.add(i);
            }
            System.out.println(Math.min(cost(a), cost(b))); // Output minimum cost for either block
        }
    }
    private static long cost(List<Integer> l){ // Compute minimal operations to align positions in list
        int n = l.size();
        if(n <= 1)
            return 0; // No operations needed if less than two elements
        int mid = n / 2; // Find median index
        long c = 0;
        for(int i = 0; i < n; i++)
            c += Math.abs(l.get(i) - l.get(mid) + mid - i); // Calculate total cost using median
        return c;
    }
}


// https://github.com/VaHiX/CodeForces/