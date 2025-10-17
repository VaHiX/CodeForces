// Problem: CF 2123 E - MEX Count
// https://codeforces.com/contest/2123/problem/E

/*
E. MEX Count

Algorithm/Technique: Difference Array + Frequency Counting

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem asks us to count how many possible MEX values can be obtained 
after removing exactly k elements from the array, for all k from 0 to n.

Approach:
1. For each element in the array, count its frequency.
2. Use a difference array technique to efficiently compute the number of 
   valid MEX values for each k.
3. The key insight is that if we remove exactly k elements, MEX can only be 
   affected by the frequencies of numbers from 0 to n-k.
4. We process frequency counts and update a difference array accordingly,
   then compute prefix sums to get final result.

*/
import java.util.*;
public class E_MEX_Count {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
        while(t-->0){
            int n=sc.nextInt();
            int arr[]=new int[n];
            for(int i=0;i<n;i++) arr[i]=sc.nextInt();
            int f[]=new int[n+1]; // frequency array
            for(int i:arr) f[i]++; // counting frequencies
            int ans[]=new int[n+1];
            for(int i=0;i<=n;i++){
                ans[f[i]]++; // increment count at frequency index
                if(n-i+1<=n) ans[n-i+1]--; // decrement at (n-i+1) to maintain differences
                if(f[i]==0) break; // no more elements with this frequency
            }
            System.out.print(ans[0]+" ");
            for(int i=1;i<=n;i++){
                ans[i]+=ans[i-1]; // prefix sum to compute actual counts
                System.out.print(ans[i]+" ");
            }
            System.out.println();
        }
    }
}


// https://github.com/VaHiX/CodeForces/