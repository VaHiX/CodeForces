// Problem: CF 2107 F1 - Cycling (Easy Version)
// https://codeforces.com/contest/2107/problem/F1

/*
 * Problem: F1. Cycling (Easy Version)
 *
 * Purpose:
 *   This code solves a problem where Leo wants to move from behind the last cyclist to in front of the first,
 *   using two operations:
 *     1. Move ahead of a cyclist (cost = cyclist's agility value).
 *     2. Swap two cyclists' agility values (cost = difference of their indices).
 *
 * Algorithm:
 *   - Uses a stack to track potential positions Leo can be in.
 *   - Processes elements from right to left, maintaining an optimal cost to reach the front.
 *   - At each step, either moves ahead or swaps with a better configuration.
 *
 * Time Complexity:
 *   O(n) for each test case, where n is the size of the array. Each element is pushed and popped at most once.
 *
 * Space Complexity:
 *   O(n), due to the stack usage which can grow up to n elements in worst case.
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

public class F1 {
    static BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in));
    
    public static void main(String[] args) throws IOException {
        StringTokenizer s1 = new StringTokenizer(br.readLine());
        int t = Integer.parseInt(s1.nextToken());
        while (t-- > 0) {
            StringTokenizer s2 = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(s2.nextToken());
            long[] arr = new long[n];
            StringTokenizer s3 = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) arr[i] = Integer.parseInt(s3.nextToken());
            solve(arr, n);
        }
    }
    
    static void solve(long[] arr, int n) {
        Stack<Integer> s=new Stack<>();
        s.push(n-1); // Initially at the last cyclist's position
        long sum=arr[n-1]; // Cost to be ahead of the last cyclist
        
        for(int i=n-2;i>=0;i--) { // Iterate from second last to first element
            if(arr[i]>arr[s.peek()]) {
                // If current cyclist is better than top of stack, we should move ahead and add cost
                sum+=arr[s.peek()]+1;
                continue;
            }
            
            // Check if it's optimal to restart with a new configuration
            if(sum>=(arr[i]+2)*(n-i-1)) {
                s=new Stack<>(); // Reset stack
                sum=(arr[i]+2)*(n-i-1); // New cost based on this position and remaining elements
                sum+=arr[i]; // Add the cost of current element to be ahead of it
            } else {
                sum+=arr[i]; // Just add current cyclist's cost
            }
            s.push(i); // Push current index into stack for potential future moves
        }
        
        System.out.println(sum);
    }
    
    static void print(int[] arr) {
        PrintWriter out=new PrintWriter(System.out);
        for (int i = 0; i < arr.length; i++)
            out.print(arr[i] + " ");
        out.print("\n");
        out.flush();
    }
}

class Pair {
    int s,e;
    Pair(int s,int e) {
        this.s=s;
        this.e=e;
    }
}


// https://github.com/VaHiX/CodeForces/