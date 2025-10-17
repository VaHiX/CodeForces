// Problem: CF 2129 C1 - Interactive RBS (Easy Version)
// https://codeforces.com/contest/2129/problem/C1

/*
 * Problem: C1. Interactive RBS (Easy Version)
 * 
 * Purpose: This program determines a hidden bracket sequence of length n using interactive queries.
 * It uses a divide-and-conquer approach to deduce the color (bracket type) of each position,
 * followed by a flip check if needed.
 * 
 * Algorithms/Techniques:
 * - Interactive binary search / divide and conquer
 * - Query-based deduction using function f(t) = count of regular bracket substrings in t
 * - Color tracking: color[i] represents the type of bracket at i (true = ')', false = '(')
 * - Flip detection to ensure correct final sequence
 * 
 * Time Complexity: O(n^2) worst case for the algorithm due to multiple queries and comparisons.
 * Space Complexity: O(n) for storing the boolean array 'color' indicating bracket types.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.ArrayList;
import java.util.List;

public final class Main {
    private static int MAX_N = 3005;
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer s = new StringTokenizer(br.readLine());
        int T = Integer.parseInt(s.nextToken());
        
        for (int t = 0; t < T; ++t) {
            s = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(s.nextToken());
            boolean[] color = new boolean[n + 1]; // color[i] represents type of bracket at i (true = ')', false = '(')
            color[1] = true; // Initialize first element as ')' - arbitrary choice
            
            String request;
            int v;
            
            // Process pairs of elements to determine their colors
            for (int i = 1; i < n; i += 2) {
                if (i + 2 <= n) {
                    // Query for a specific pattern to deduce pair relationships
                    request = String.format("? 12 %d %d %d %d %d %d %d %d %d %d %d %d", 
                        i, i + 1, i + 1, i, i + 1, i + 2, i + 2, i + 1, i, i + 1, i + 1, i);
                    System.out.println(request);
                    s = new StringTokenizer(br.readLine());
                    v = Integer.parseInt(s.nextToken());
                    
                    // Interpret query result to set colors of the current pair
                    if (v == 0) {
                        color[i + 1] = color[i]; 
                        color[i + 2] = color[i + 1];
                    } else if (v == 2) {
                        color[i + 1] = color[i]; 
                        color[i + 2] = !color[i + 1];
                    } else if (v == 3) {
                        color[i + 1] = !color[i]; 
                        color[i + 2] = color[i + 1];
                    } else {
                        color[i + 1] = !color[i]; 
                        color[i + 2] = !color[i + 1];
                    }
                } else if (i + 1 <= n) {
                    // Special case for odd-length segments
                    request = String.format("? 4 %d %d %d %d", i, i + 1, i + 1, i); 
                    System.out.println(request);
                    s = new StringTokenizer(br.readLine());
                    v = Integer.parseInt(s.nextToken());
                    
                    // Interpret result to determine color of last element
                    if (v == 1) {
                        color[i + 1] = !color[i];
                    } else {
                        color[i + 1] = color[i];
                    }
                }
            }
            
            boolean isFlip = false;
            // Detect if we need to flip all colors to match the hidden sequence
            for (int i = 2; i <= n; ++i) {
                if (color[1] != color[i]) {
                    System.out.println("? 2 1 " + i);
                    s = new StringTokenizer(br.readLine());
                    v = Integer.parseInt(s.nextToken());
                    // Check consistency between known color and result of query
                    if (v == 1 && color[1]) {
                        isFlip = true;
                    } else if (v == 0 && !color[1]) {
                        isFlip = true;
                    }
                    break;
                }
            }
            
            // Flip colors if needed to align with hidden bracket sequence
            if (isFlip) {
                for (int i = 1; i <= n; ++i) {
                    color[i] = !color[i];
                }
            }
            
            // Construct final answer string from determined colors
            StringBuilder s1 = new StringBuilder();
            for (int i = 1; i <= n; ++i) {
                if (color[i]) {
                    s1.append(")");
                } else {
                    s1.append("(");
                }
            }
            System.out.println("! " + s1.toString());
        }
    }
    
    private static int f(String s) {
        int ans = 0;
        for (int i = 0; i < s.length(); ++i) {
            int ct = 0;
            for (int j = i; j < s.length() && ct >= 0; ++j) {
                if (s.charAt(j) == ')') {
                    ct--;
                } else {
                    ct++;
                }
                // If balance becomes zero, increment count (a valid substring)
                if (ct == 0) {
                    ans++;
                }
            }
        }
        return ans;
    }
}


// https://github.com/VaHiX/CodeForces/