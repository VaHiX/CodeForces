// Problem: CF 2117 B - Shrink
// https://codeforces.com/contest/2117/problem/B

/*
B. Shrink
Algorithms/Techniques: Constructive Algorithm
Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (not counting output)

The problem asks to construct a permutation of length n that maximizes the number of "shrink" operations.
A shrink operation removes an element which is strictly greater than both its neighbors.

To maximize the number of operations:
We arrange the array such that we can keep removing peaks (elements greater than both neighbors).
The optimal strategy is to place smaller elements at the start, then increase the values in a way that
allows for maximum peak removals. The approach is to print numbers from 2 to n followed by 1.
This ensures a pattern where we can remove middle elements as peaks repeatedly.

For example:
- For n=3: [2,3,1] → removes 3 (peak), remaining [2,1] → no more peaks
- For n=6: [2,3,6,4,5,1] → multiple peaks can be removed
*/
import java.util.* ; 
public class Main{
    public static void main(String []args){
        Scanner sc = new Scanner(System.in) ; 
        int t = sc.nextInt() ; 
        while(t -- > 0){
            int n = sc.nextInt() ; 
            for(int i = 2 ; i <= n ; i++){
                System.out.print(i  + " ") ; // Print numbers from 2 to n
            }
            System.out.println("1") ; // Then print 1 at the end
        }
    }
}


// https://github.com/VaHiX/CodeForces/