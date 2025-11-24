// Problem: CF 2117 A - False Alarm
// https://codeforces.com/contest/2117/problem/A

/*
 * Problem: A. False Alarm
 * Algorithm: Greedy + Simulation
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 *
 * Yousef needs to pass through n doors in order. Each door is either open (0) or closed (1).
 * He can use a special button once that makes all closed doors open for x seconds.
 * The goal is to determine if he can pass through all doors using at most one button press.
 *
 * Approach:
 * 1. For each test case, find the first and last closed door (i.e., where a[i] == 1).
 * 2. Calculate the total time required to traverse from first to last closed door.
 * 3. If this time is <= x, then he can use the button at the beginning to cover all doors.
 *    Otherwise, check if he can pass through without the button (i.e., all doors are open).
 */

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int t=input.nextInt(); // Number of test cases
        while(t-- >0){
            int n=input.nextInt(); // Number of doors
            int x=input.nextInt(); // Duration of button effect in seconds
            int l=n; // Leftmost closed door index initialized to n (invalid index)
            int r=0; // Rightmost closed door index initialized to 0
            
            for(int i=0;i<n;++i){
                int a=input.nextInt(); // State of the door at position i
                if (a==1){ // If the door is closed
                    l=Math.min(l, i); // Update leftmost closed door
                    r=Math.max(r, i); // Update rightmost closed door
                }
            }
            
            // If distance between first and last closed door is <= x, button can cover it
            System.out.println(r-l+1<=x?"YES":"NO");
        }
        input.close();
    }
}


// https://github.com/VaHiX/CodeForces/