// Problem: CF 2118 B - Make It Permutation
// https://codeforces.com/contest/2118/problem/B

/*
 * Problem: B. Make It Permutation
 * 
 * Purpose: Given an n×n matrix A where A[i][j] = j for all 1 ≤ i,j ≤ n,
 * we need to perform at most 2n operations to make every column a permutation of [1, n].
 * Each operation allows reversing any subarray in a selected row.
 *
 * Algorithm:
 * - For each row i from 1 to n:
 *   - Reverse the entire row (i 1 n)
 *   - If not the last row, reverse the subarray from column i+1 to n in row i
 *
 * Time Complexity: O(n^2) - Due to the nested loops and operations on rows.
 * Space Complexity: O(1) - No extra space used beyond input/output.
 */
import java.util.*;
public class Codes {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int t = input.nextInt();
        while(t-->0){
            int n=input.nextInt();
            System.out.println(2*n-1); // Total operations: 2n - 1
            for(int i=1;i<=n;i++){
                System.out.println(i+" "+ 1 +" "+ i); // Reverse entire row i
                if(i!=n){
                    System.out.println(i+" "+(i+1)+" "+n); // Reverse subarray from i+1 to n in row i
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/