// Problem: CF 2104 F - Numbers and Strings
// https://codeforces.com/contest/2104/problem/F

/**
 * F. Numbers and Strings
 * 
 * Problem Description:
 * For each integer x from 1 to n, we form the string S(x) by:
 *   - Compute (x+1)
 *   - Concatenate x and (x+1) in decimal without separators or leading zeros
 *   - Sort all digits of the concatenated result in non-decreasing order
 * 
 * Task: Count how many distinct strings among S(1), S(2), ..., S(n).
 * 
 * Algorithm:
 * - Precompute all valid signature combinations for digits that can occur
 *   in S(x) based on x and (x+1) with digit counts.
 * - Generate possible digit signatures by DFS, using memoization to avoid recomputation.
 * - For large k values, handle base cases of powers of 10 to cover all valid numbers up to n.
 * - Store minimal representations per signature to reduce space and time.
 * - Answer queries using binary search on sorted list of computed values.
 * 
 * Time Complexity: O(9!*K + log(N)) where K is max number of digits (10), N <= 10^9
 * Space Complexity: O(4*10^5) for caching and storage of digit count maps.
 */
import java.io.*;
import java.util.*;
public class Main {
    static final int MAX_DIGIT_SUM = 9; // Max possible sum of digits
    static final int MAX_K = 10;         // Max digits in number representation
    static final int MAX_N = 1_000_000_000; // Upper bound on input n
    static int[] pow10 = new int[MAX_K+1]; // Precomputed powers of 10
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        pow10[0] = 1;
        for (int i = 1; i <= MAX_K; i++) {
            pow10[i] = pow10[i-1] * 10;
        }
        
        HashMap<Long,Integer> sig2minx = new HashMap<>(400_000); // Maps digit signature -> minimal value
        int[] m = new int[10]; // Temporary array to hold digit counts
        
        for (int t = 1; t <= MAX_DIGIT_SUM; t++) {
            genM(0, t, m, sig2minx); // Generate all valid combinations of digit sums
        }
        
        int[] base0 = new int[10];
        base0[1] = 1; // Special case for handling x = 1 which results in "12" -> "12" sorted
        
        int[] sigCnt = new int[10]; // Temporary array to hold signature counting
        
        for (int k = 1; k <= MAX_K; k++) {
            int x = pow10[k] - 1; // Generate numbers like 9, 99, 999...
            if (x > MAX_N) break;
            
            System.arraycopy(base0, 0, sigCnt, 0, 10); // Copy base digit counts
            sigCnt[0] += k; // Adjust for leading zeros in powers of 10
            sigCnt[9] += k; // Similarly adjust for trailing 9s
            
            long key = pack(sigCnt); // Pack into key for map
            sig2minx.merge(key, x, Math::min);
        }
        
        int sz = sig2minx.size(); // Size of unique signatures
        int[] mins = new int[sz]; // Array of minimal values
        int[] i = {0}; // Wrapper to use in lambda (array is passed by reference)
        
        for (int v : sig2minx.values()) mins[i[0]++] = v; // Populate array with values
        
        Arrays.sort(mins); // Sort for binary search later
        
        int t = Integer.parseInt(br.readLine().trim()); // Number of test cases
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());
            pw.println(upperBound(mins, n)); // Print result using binary search
        }
        pw.flush(); // Flush output buffer
    }
    
    /**
     * Recursively generate all possible digit distributions for a total digit sum `rem`.
     * For given index `idx`, distribute digits from 0 to rem into m[idx].
     */
    static void genM(int idx, int rem, int[] m, HashMap<Long,Integer> sig2minx) {
        if (idx == 9) { // Base case: fill last digit slot
            m[9] = rem;
            processM(m, sig2minx); // Process current combi with digit counts
            m[9] = 0;             // Reset for next iteration
            return;
        }
        for (int v = 0; v <= rem; v++) {
            m[idx] = v;
            genM(idx+1, rem-v, m, sig2minx); // Recursive call to fill rest of slots
        }
        m[idx] = 0; // Reset back
    }
    
    /**
     * Process the current digit count array `m` to compute valid number strings.
     * Handles two different cases based on whether total sum of digits is 1 or not.
     */
    static void processM(int[] m, HashMap<Long,Integer> sig2minx) {
        int t = Arrays.stream(m).sum(); // Total count of digits
        int[] sigCnt = new int[10];      // Signature counter
        
        if (t == 1) { // Special case: only one non-zero digit
            for (int d = 0; d < 10; d++) if (m[d] == 1) {
                if (d != 0 && d != 9) { // Skip 0 and 9 since they don't form valid x+1 pairs directly
                    int y = d;
                    int[] base = new int[10];
                    base[d]++; // Assign this digit to base

                    int v2 = y + 1; 
                    while (v2>0) { 
                        base[v2%10]++; 
                        v2/=10; 
                    }
                    
                    for (int k = 0; k <= MAX_K; k++) {
                        long x = (long)y*pow10[k] + (pow10[k]-1); // Construct x and compute S(x)
                        if (x > MAX_N) break;
                        
                        System.arraycopy(base,0,sigCnt,0,10);
                        sigCnt[0]+=k; 
                        sigCnt[9]+=k;
                        
                        long key = pack(sigCnt);
                        sig2minx.merge(key, (int)x, Math::min);
                    }
                }
                break;
            }
        } else { // General case
            for (int d = 0; d < 9; d++) if (m[d] > 0) {
                int[] m2 = m.clone(); // Clone to preserve original state
                m2[d]--;
                
                int s=-1;
                for (int c = 1; c <= 9; c++) if (m2[c]>0) { s=c; break; } // Find next significant digit

                if (s < 0) continue;
                m2[s]--;
                
                StringBuilder sb = new StringBuilder(t);
                sb.append((char)('0'+s));
                for (int c = 0; c < 10; c++) for (int cnt=0; cnt<m2[c]; cnt++)
                    sb.append((char)('0'+c));
                sb.append((char)('0'+d));
                
                int y = Integer.parseInt(sb.toString());
                int[] base = m.clone();
                int v2 = y+1;
                while (v2>0) { 
                    base[v2%10]++; 
                    v2/=10; 
                }

                for (int k = 0; k <= MAX_K; k++) {
                    long x = (long)y*pow10[k] + (pow10[k]-1);
                    if (x > MAX_N) break;
                    
                    System.arraycopy(base,0,sigCnt,0,10);
                    sigCnt[0]+=k; 
                    sigCnt[9]+=k;
                    
                    long key = pack(sigCnt);
                    sig2minx.merge(key, (int)x, Math::min);
                }
            }
        }
    }
    
    /**
     * Packs the digit count array into a single long key for hashing.
     * Each digit count is stored using 5 bits (0-31 range allowed).
     */
    static long pack(int[] cnt) {
        long key = 0;
        for (int i = 0; i < 10; i++) 
            key |= ((long)cnt[i]) << (5*i); // Store each of 10 digits using 5 bits
        return key;
    }
    
    /**
     * Binary search for the index where value exceeds x.
     */
    static int upperBound(int[] a, int x) {
        int l=0, r=a.length;
        while (l<r) {
            int m=(l+r)>>>1;
            if (a[m] <= x) l=m+1;
            else r=m;
        }
        return l;
    }
}


// https://github.com/VaHiX/CodeForces/