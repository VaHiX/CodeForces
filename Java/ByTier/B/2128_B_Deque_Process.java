// Problem: CF 2128 B - Deque Process
// https://codeforces.com/contest/2128/problem/B

/*
 * B. Deque Process
 * 
 * Problem Description:
 * Given a permutation of integers from 1 to n, we need to remove elements one by one
 * either from the left or right end of the array in each turn. The goal is to produce
 * a sequence of removals such that the resulting array q is "good" - meaning there
 * does not exist any 5 consecutive elements forming a strictly increasing or decreasing subsequence.
 * 
 * Algorithm:
 * Greedy approach:
 * At each step, compare the leftmost and rightmost elements.
 * If left < right:
 *   - If turn number is odd, remove left (append 'L')
 *   - If turn number is even, remove right (append 'R')
 * Else:
 *   - If turn number is odd, remove right (append 'R')
 *   - If turn number is even, remove left (append 'L')
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the output string builder
 */

import java.util.Scanner;
public class Main{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int tst = sc.nextInt();
        while(tst-- > 0){
            int n = sc.nextInt();
            int[] arr = new int[n];
            for(int i = 0; i < n; i++){
                arr[i] = sc.nextInt(); // Read array elements
            }
            int i = 0, j = n-1;
            StringBuilder sb = new StringBuilder();
            int idx = 1;
            while(i <= j){
                if(arr[i] < arr[j]){
                    if(idx % 2 == 0){
                        sb.append("R"); // Even turn: Remove from right
                        j--;
                    } else {
                        sb.append("L"); // Odd turn: Remove from left
                        i++;
                    }
                } else {
                    if(idx % 2 == 0){
                        sb.append("L"); // Even turn: Remove from left
                        i++;
                    } else {
                        sb.append("R"); // Odd turn: Remove from right
                        j--;
                    }
                }
                idx++; // Increment turn counter
            }
            System.out.println(sb); // Print the result for current test case
        }
    }
}


// https://github.com/VaHiX/CodeForces/