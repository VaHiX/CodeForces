// Problem: CF 2111 C - Equal Values
// https://codeforces.com/contest/2111/problem/C

/*
 * Problem: C. Equal Values
 * 
 * Purpose: Given an array of integers, find the minimum cost to make all elements equal
 *          using two types of operations:
 *          1. Set all elements to the left of position i to a[i], cost = (i-1) * a[i]
 *          2. Set all elements to the right of position i to a[i], cost = (n-i) * a[i]
 *
 * Algorithms/Techniques:
 * - For each possible target value (from array), calculate minimal cost
 * - Use prefix and suffix processing to efficiently compute costs
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the array storage
 */
import java.util.Scanner;
public class vvv {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t-->0){
            int n= sc.nextInt();
            long a [] = new long[n];
            for (int i = 0; i <n; i++) {
                a[i]=sc.nextLong();
            }
            long ans = Long.MAX_VALUE;
            long temp = (n-1)*a[0]; // Initial cost if we set all elements to a[0]
            ans = temp;
            for(int i = 1;i<n;i++){
                if(a[i]==a[i-1]){
                    // If current element equals previous, no change in cost calculation
                    temp -= a[i];
                }
                else{
                    // Calculate new cost when switching to element at index i
                    temp = (i*a[i]) + (n-(i+1))*a[i];
                }
             ans = Math.min(ans, temp); // Keep track of minimum cost
            }
            System.out.println(ans);
        }
    }
}


// https://github.com/VaHiX/CodeForces/