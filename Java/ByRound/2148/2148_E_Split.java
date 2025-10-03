// Problem: CF 2148 E - Split
// https://codeforces.com/contest/2148/problem/E

/*
E. Split
Algorithms/Techniques: Two-pointer technique, prefix sum, hashing
Time Complexity: O(n) per test case (amortized)
Space Complexity: O(n) for arrays and auxiliary structures

Farmer John has an array a containing n positive integers and an integer k.
A subarray a[l,r] is awesome if we can distribute elements from it into k multisets such that
each multiset contains exactly the same multiset of elements.
This means each element value v must appear a multiple of k times in the subarray,
and each set gets exactly tot[v]/k copies of value v.

We use two-pointer technique to count valid subarrays efficiently:
- For each right pointer r, we track how many copies of each element are present.
- If we exceed the required count (tot[v]/k) for any value, move left pointer forward
  until all elements are within allowed counts.
- Add number of valid subarrays ending at r to answer.

The code uses a fast input class F to speed up I/O.
*/

import java.io.*;
public class Main{
    static class F{
        private final InputStream in; private final byte[] b=new byte[1<<16]; private int p,q;
        F(InputStream is){in=is;}
        int n()throws Exception{int c; while((c=read())<=32); int s=c=='-'? -1:1; if(c=='-') c=read(); int x=c-'0'; while((c=read())>32) x=x*10 + c-'0'; return s==1?x:-x;}
        private int read()throws Exception{ if(p>=q){ q=in.read(b); p=0; if(q<=0) return -1;} return b[p++]; }
    }
    public static void main(String[] args) throws Exception{
        F f=new F(System.in);
        StringBuilder sb=new StringBuilder();
        int T=f.n(); // number of test cases
        while(T-->0){
            int n=f.n(), k=f.n(); // length of array and number of multisets
            int[] a=new int[n];
            for(int i=0;i<n;i++) a[i]=f.n(); // read array elements
            
            // Count frequency of each element in entire array
            int[] tot=new int[n+1];
            for(int v:a) tot[v]++;
            
            boolean ok=true;
            // Check if total count of each value is divisible by k
            for(int i=1;i<=n;i++) if(tot[i]%k!=0){ok=false;break;}
            if(!ok){sb.append(0).append('\n'); continue;} // not possible if not divisible
            
            // Calculate limit for each element (how many copies per multiset)
            int[] lim=new int[n+1];
            for(int i=1;i<=n;i++) lim[i]=tot[i]/k;
            
            // Current frequency of elements in sliding window
            int[] cur=new int[n+1];
            long ans=0; // total number of awesome subarrays
            int l=0; // left pointer of sliding window
            
            // Two-pointer technique to count valid subarrays ending at r
            for(int r=0;r<n;r++){
                int x=a[r]; // current element
                cur[x]++; // increment its count in current window
                
                // Shrink window from left while exceeding limit
                while(cur[x]>lim[x]) cur[a[l++]]--;
                
                // Add number of valid subarrays ending at r to answer
                ans += r-l+1;
            }
            sb.append(ans).append('\n');
        }
        System.out.print(sb);
    }
}


// https://github.com/VaHiX/codeForces/