// Problem: CF 2113 A - Shashliks
// https://codeforces.com/contest/2113/problem/A

/**
 * Problem: A. Shashliks
 * 
 * Purpose: Determine the maximum number of shashlik portions that can be cooked given
 *          initial grill temperature and cooking requirements for two types of shashlik.
 * 
 * Algorithm: Greedy approach with optimization.
 *            - For each test case, we try to maximize the total number of shashlik cooked.
 *            - First, ensure that type 1 has lower or equal temperature requirement than type 2 (a <= b).
 *            - Then, greedily consume as many portions of type 1 as possible to minimize temperature drops,
 *              and then compute how many portions of type 2 can be cooked with remaining temperature.
 * 
 * Time Complexity: O(1) per test case - constant time operations.
 * Space Complexity: O(1) - only using a fixed amount of extra variables.
 */

import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t-- !=0){
            int k = sc.nextInt(); // initial temperature
            int a = sc.nextInt(); // required temp for type 1
            int b = sc.nextInt(); // required temp for type 2
            int x = sc.nextInt(); // temp drop after cooking type 1
            int y = sc.nextInt(); // temp drop after cooking type 2
            int c = 0; // count of shashlik portions
            
            // Ensure a <= b to simplify logic
            if(x>y){
                int tp = a;
                a = b;
                b = tp;
                tp = x;
                x = y;
                y = tp;
            }
            
            // Try to cook as many portions of type 1 (with lower requirement) as possible
            if(k>=a){
                int m1 = (k-a)/x+1;  // number of type 1 portions we can cook
                k -=m1*x;   // update remaining temperature after cooking m1 portions
                c+=m1;      // increase counter by m1
            }
            
            // Try to cook as many portions of type 2 (higher requirement) as possible with remaining temperature
            if(k>=b){
                int m2 = (k-b)/y+1;  // number of type 2 portions we can cook
                c+=m2;      // increase counter by m2
            }
            
            System.out.println(c);
        }
    }
}


// https://github.com/VaHiX/CodeForces/