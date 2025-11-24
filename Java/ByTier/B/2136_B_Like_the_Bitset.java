// Problem: CF 2136 B - Like the Bitset
// https://codeforces.com/contest/2136/problem/B

/*
B. Like the Bitset
time limit per test1 second
memory limit per test256 megabytes

Algorithm/Techniques:
- Sliding window technique to check for valid placement of 0s in a window of size k.
- Greedy assignment of numbers from left and right ends to satisfy constraints.

Time Complexity: O(n) per test case, where n is the length of string s.
Space Complexity: O(n) for the input and output storage.

The problem asks to construct a permutation of integers 1 to n such that for each position i with s[i] = '1',
every interval [l,r] with length at least k covering i has a maximum element among p[l], ..., p[r] not equal to p[i].

Approach:
- First, check if it's possible to have the required constraint. This is done by ensuring that in every window of size k,
  there's at least one '0'. If any window contains all '1's, it's impossible.
- If possible, assign values greedily: 
   - For positions with '0', we can assign from low ends (1,2,...)
   - For positions with '1', we can assign from high ends (n,n-1,...) to avoid conflicts.
   - However, in this code, a different approach is used:
     - Assign increasing numbers from left for 0's and decreasing from right for 1's.
     - A sliding window tracks how many 0s exist in each size-k window.
     - If all windows have at least one 0, then it's possible to assign values appropriately.

Key points in implementation:
- Initialize sliding window of size k to count 0s.
- For each new position, remove the leftmost element and add the rightmost.
- Mark impossible if any window has zero 0s.
- If possible, use greedy assignment from both ends.
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
public class B {
    public static void main(String[] args) throws Exception {
        BufferedReader bu = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        String[] s = bu.readLine().split(" ");
        int tt = Integer.parseInt(s[0]);
        for (int t = 0; t < tt; t++) {
            s = bu.readLine().split(" ");
            int n = Integer.parseInt(s[0]), k = Integer.parseInt(s[1]);
            char[] a = bu.readLine().toCharArray();
            int cur0 = 0;
            // Count initial '0's in the first window of size k
            for (int i = 0; i < k; i++) if (a[i] == '0') cur0++;
            boolean possible = cur0 > 0; // If no '0' in first window, impossible
            // Slide the window across the array
            for (int i = k; i < n; i++) {
                if (a[i - k] == '0') cur0--; // Remove leftmost element of previous window
                if (a[i] == '0') cur0++;     // Add new rightmost element
                possible &= cur0 > 0;        // If no '0' now, impossible
            }
            if (possible) {
                sb.append("YES\n");
                int low = 1, high = n;
                for (char c : a) sb.append(c == '0' ? high-- : low++).append(" "); // Assign from both ends
                sb.append("\n");
            } else sb.append("NO\n");
        }
        System.out.print(sb);
    }
}


// https://github.com/VaHiX/codeForces/