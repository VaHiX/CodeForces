// Problem: CF 2108 F - Fallen Towers
// https://codeforces.com/contest/2108/problem/F

/*
F. Fallen Towers

Purpose:
This program solves a problem where we have an array of towers with certain block heights.
We are allowed to knock down each tower exactly once. When knocking down a tower at position i,
we increase the next a[i] towers by 1 block, and set that tower's height to 0.
The goal is to find the maximum MEX (minimum excludant) of the final non-decreasing array after all operations.

Algorithms/Techniques:
- Binary search on the answer (the MEX value)
- Difference array technique for efficient range updates
- Simulation with difference arrays to check if a certain MEX is achievable

Time Complexity: O(n * log(max(a))) where n is the size of the array and max(a) is the maximum value in the array.
Space Complexity: O(n) for storing the array and difference array.

*/

import java.util.*;
import static java.lang.Math.*;

public class Main
{
    static Scanner scanner=new Scanner(System.in);
    public static void main(String[] args)
    {
        int T=scanner.nextInt();
        for(int i=1;i<=T;i++)
            Solve();
    }
    static void Solve()
    {
        int n=scanner.nextInt();
        int[] a=new int[n+1];
        int[] s=new int[n+1]; // Difference array for range updates
        for(int i=1;i<=n;i++)
            a[i]=min(n,scanner.nextInt()); // Clamp values to avoid out-of-bounds access
        int L=0,R=n,mid;
        while(L<R)
        {
            mid=(L+R+1)/2; // Binary search mid point
            for(int i=1;i<=n;i++)
                s[i]=0; // Reset difference array
            int cnt=0;
            boolean chk=true;
            for(int i=1;i<=n;i++)
            {
                cnt-=s[i]; // Apply pending updates to current position
                int goal=max(0,i+mid-n); // Calculate required height at position i to maintain non-decreasing order
                if(cnt<goal) // If current height is less than required, impossible to achieve this MEX
                {
                    chk=false;
                    break;
                }
                if(cnt+a[i]!=goal) // If we can knock down tower i and still satisfy the constraint
                {
                    if(cnt-goal+i+a[i]<n) // Check bounds before updating difference array
                        s[cnt-goal+i+a[i]+1]++; // Update difference array to track future increase
                    cnt++; // Increment count after applying operation
                }
            }
            if(chk)
                L=mid; // If successful, try higher MEX value
            else
                R=mid-1; // Otherwise, try lower MEX value
        }
        System.out.println(L+1); // Add 1 because L represents the maximum valid MEX minus one
    }
}


// https://github.com/VaHiX/CodeForces/