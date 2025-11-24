// Problem: CF 2112 A - Race
// https://codeforces.com/contest/2112/problem/A

/*
 * Problem: Race
 * 
 * Purpose: Determine if Bob can choose a starting point such that he is guaranteed to reach the prize faster
 *          than Alice, regardless of whether the prize drops at point x or y.
 * 
 * Algorithm/Techniques:
 * - For each test case, we evaluate if there exists a point Bob can choose (not equal to a) such that
 *   for both possible prize locations (x and y), his distance is strictly less than Alice's.
 * - Key logic check:
 *   1. If a is the midpoint of x and y (i.e., a = (x + y)/2), then regardless of where the prize is, 
 *      Alice and Bob will be equidistant from it. So, NO.
 *   2. If a lies within the interval [min(x,y), max(x,y)], then Alice's distance is less than or equal 
 *      to Bob's for at least one case (if Bob stands at x or y). So, NO.
 *   3. Otherwise, there exists a point Bob can choose that guarantees faster arrival.
 * 
 * Time Complexity: O(t), where t is the number of test cases. Each operation inside the loop is O(1).
 * Space Complexity: O(1), constant space used.
 */

import java.util.*;
public class Main {
    public static void main(String[] args){
      Scanner sc= new Scanner(System.in);
      int t = sc.nextInt(); // Read number of test cases
      while(t-->0){ // Process each test case
        int a = sc.nextInt(); // Alice's starting position
        int x = sc.nextInt(); // Prize location 1
        int y = sc.nextInt(); // Prize location 2
        
        // Check three conditions:
        // 1. If a is the midpoint of x and y, then distance from a to either x or y is same as 
        //    Alice's distance (in that case, Bob cannot be faster).
        // 2. If a lies inside the range [min(x,y), max(x,y)], then in at least one case,
        //    Alice will reach equal or faster than Bob.
        // 3. Otherwise, there exists a position for Bob to choose such that he is always faster.
        if(a==(x+y)/2 || (a>=x && a<=y) || (a>=y && a<=x)){
            System.out.println("NO");
        }else{
            System.out.println("YES");
        }
      }
    }
}


// https://github.com/VaHiX/CodeForces/