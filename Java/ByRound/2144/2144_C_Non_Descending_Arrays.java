// Problem: CF 2144 C - Non-Descending Arrays
// https://codeforces.com/contest/2144/problem/C

/*
C. Non-Descending Arrays
Algorithms/Techniques: Dynamic Programming with state transitions based on valid swaps
Time Complexity: O(n) per test case
Space Complexity: O(1) additional space (excluding input storage)

For each position i, we determine how many valid ways we can choose to swap or not swap 
the elements at that position such that both arrays remain non-descending.
We track the number of valid combinations using a multiplication of choices at each step.
*/

import java.util.Scanner;
public class C {
    public static final int MOD = 998244353;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = Integer.parseInt(sc.nextLine());
        while(t-->0) {
            int n = Integer.parseInt(sc.nextLine());
            String[] str1 = sc.nextLine().split(" ");
            String[] str2 = sc.nextLine().split(" ");
            long ans = 2; // Start with 2 because we have two choices (swap or not swap) for the first element
            for(int i = 1; i < n; i++) {
                int prevA = Integer.parseInt(str1[i-1]);
                int prevB = Integer.parseInt(str2[i-1]);
                int a = Integer.parseInt(str1[i]);
                int b = Integer.parseInt(str2[i]);
                int curr = 0;
                // Check if keeping current elements (a,b) maintains non-descending order
                if(prevA <= a && prevB <= b) {
                    curr++;
                }
                // Check if swapping current elements (b,a) maintains non-descending order
                if(prevA <= b && prevB <= a) {
                    curr++;
                }
                ans = (ans*curr)%MOD;
            }
            System.out.println(ans);
        }
    }
}


// https://github.com/VaHiX/codeForces/