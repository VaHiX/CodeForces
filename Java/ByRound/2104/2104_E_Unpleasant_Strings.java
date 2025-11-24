// Problem: CF 2104 E - Unpleasant Strings
// https://codeforces.com/contest/2104/problem/E

/*
E. Unpleasant Strings
Algorithm: Dynamic Programming + Preprocessing + Two Pointers
Time Complexity: O(n * k + sum of lengths of all queries)
Space Complexity: O(n * k)

The problem involves determining the minimum number of allowed letters to append to a query string so that it is no longer a subsequence of the given string s.
We use dynamic programming to preprocess for each position in s and each letter, what is the next occurrence of that letter in s.

Approach:
1. Preprocessing step:
   - For each position in string s and each letter (0 to k-1), store the index of the next occurrence of that letter.
   - If no such letter exists from current position onwards, set to n (out of bounds).
2. Using these preprocessed positions:
   - Compute for each position how many steps it takes until we can no longer form a subsequence.
   - This allows fast query processing.

Key Data Structures:
- a[i][c]: next occurrence of letter c starting at position i
- b[i]: minimum number of letters to append to make suffix starting from i not a subsequence

*/
import java.io.*;
import java.util.*;
public class Main{
    public static void main(String[] z)throws Exception{
        BufferedReader r=new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer t=new StringTokenizer(r.readLine());
        int n=Integer.parseInt(t.nextToken()),k=Integer.parseInt(t.nextToken());
        String s=r.readLine();
        int I=n; // Sentinel value meaning "no more occurrences"
        int[][] a=new int[n+2][k]; // Preprocessing array
        for(int c=0;c<k;c++){a[n][c]=I;a[n+1][c]=I;} // Initialize boundaries
        
        // Fill the preprocessing table backwards
        for(int i=n-1;i>=0;i--){
            for(int c=0;c<k;c++)a[i][c]=a[i+1][c]; // Copy from next position
            a[i][s.charAt(i)-'a']=i; // Mark current character's position
        }
        
        int[] b=new int[n+2];
        // Compute minimum steps needed to break subsequence property
        for(int i=n;i>=0;i--){
            boolean f=false;
            for(int c=0;c<k;c++)if(a[i][c]==I){f=true;break;}
            if(f)b[i]=1; // If no characters found, just need 1 more letter
            else{
                int m=1<<30;
                for(int c=0;c<k;c++)m=Math.min(m,b[a[i][c]+1]); // Find minimum steps from all possible next positions
                b[i]=m+1;
            }
        }
        
        int q=Integer.parseInt(r.readLine());
        StringBuilder x=new StringBuilder();
        while(q-->0){
            String v=r.readLine();
            int p=0;boolean h=false;
            for(int i=0;i<v.length();i++){
                int c=v.charAt(i)-'a';
                if(a[p][c]==I){x.append("0\n");h=true;break;} // If no character found, result is 0
                p=a[p][c]+1; // Move to next position
            }
            if(!h)x.append(b[p]).append('\n'); // Output computed steps for breaking subsequence
        }
        System.out.print(x);
    }
}


// https://github.com/VaHiX/CodeForces/