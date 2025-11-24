// Problem: CF 2144 E2 - Looking at Towers (difficult version)
// https://codeforces.com/contest/2144/problem/E2

/**
 * Problem: E2. Looking at Towers (difficult version)
 * 
 * Given a sequence of tower heights, count the number of subsequences such that:
 * - The set of visible heights from the left matches the original sequence's left view
 * - The set of visible heights from the right matches the original sequence's right view
 * 
 * Key Techniques:
 * - Coordinate compression using TreeMap
 * - Segment tree (Binary Indexed Tree) for counting and updating
 * - Two-pass dynamic programming:
 *   - Forward pass to compute prefix contributions
 *   - Backward pass to compute suffix contributions
 * 
 * Time Complexity: O(n log n) per test case due to sorting, coordinate compression,
 *                   and BIT operations. Overall O(\sum n log n) across all test cases.
 * Space Complexity: O(n) for arrays and data structures.
 */
import java.util.*;
public class Main {
    static final int MOD = 998244353;
    static final int MAXN = 300_012;
    static long[] pw = new long[MAXN];
    static long[] inv = new long[MAXN];
    static int[] bit = new int[MAXN];
    
    // Initialize precomputed powers of 2 and inverse powers
    static void clear(int n) {
        pw[0] = inv[0] = 1;
        for (int i = 1; i <= n + 1; i++) {
            pw[i] = pw[i - 1] * 2 % MOD;
            inv[i] = inv[i - 1] * 499122177 % MOD; 
        }
        Arrays.fill(bit, 0);
    }
    
    // Update BIT at index i by adding x
    static void upd(int i, int x, int n) {
        while (i <= n + 1) {
            bit[i] += x;
            i |= i + 1;
        }
    }
    
    // Get prefix sum up to index i
    static int get(int i) {
        int ans = 0;
        while (i >= 0) {
            ans += bit[i];
            i = (i & (i + 1)) - 1;
        }
        return ans;
    }
    
    // Get range sum [l, r]
    static int get(int l, int r) {
        return get(r) - get(l - 1);
    }
    
    static void solve(Scanner sc) {
        int n = sc.nextInt();
        int[] a = new int[n + 2]; 
        int[] pref = new int[n + 2];
        int[] suff = new int[n + 2];
        ArrayList<Integer>[] g = new ArrayList[n + 2];
        for (int i = 0; i <= n + 1; i++) g[i] = new ArrayList<>();
        ArrayList<Integer> vList = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            a[i] = sc.nextInt();
            vList.add(a[i]);
        }
        TreeSet<Integer> set = new TreeSet<>(vList);
        HashMap<Integer, Integer> map = new HashMap<>();
        int idx = 1;
        for (int x : set) map.put(x, idx++);
        for (int i = 1; i <= n; i++) {
            a[i] = map.get(a[i]);
            g[a[i]].add(i);
        }
        g[0].add(0);
        g[0].add(n + 1);
        clear(n);
        
        // Monotonic stack from right to left for computing prefix dp
        Stack<Integer> s = new Stack<>();
        a[n + 1] = 0;
        for (int i = n; i >= 1; i--) {
            while (!s.isEmpty() && a[s.peek()] <= a[i]) s.pop();
            s.push(i);
        }
        s.push(0);
        Collections.reverse(s);
        upd(0, 1, n);
        pref[0] = 1;
        int szl = s.size() - 1;
        for (int k = 1; k <= szl; k++) {
            ArrayList<Integer> temp = new ArrayList<>(g[a[s.get(k)]]);
            // Union all indices of previous element
            for (int x : g[a[s.get(k - 1)]]) temp.add(x);
            Collections.sort(temp);
            int way = 0;
            for (int i : temp) {
                if (a[i] == a[s.get(k - 1)]) {
                    way = (int)((way + inv[get(i)] * 1L * pref[i]) % MOD);
                } else {
                    pref[i] = (int)(way * 1L * pw[get(i)] % MOD);
                }
            }
            // Update BIT with elements from current stack element
            for (int x = a[s.get(k - 1)] + 1; x <= a[s.get(k)]; x++) {
                for (int i : g[x]) upd(i, 1, n);
            }
        }
        
        clear(n);
        s.clear();
        
        // Monotonic stack from left to right for computing suffix dp
        for (int i = 1; i <= n; i++) {
            while (!s.isEmpty() && a[s.peek()] <= a[i]) s.pop();
            s.push(i);
        }
        s.push(n + 1);
        Collections.reverse(s);
        upd(n + 1, 1, n);
        suff[n + 1] = 1;
        int szr = s.size() - 1;
        for (int k = 1; k <= szr; k++) {
            ArrayList<Integer> temp = new ArrayList<>(g[a[s.get(k)]]);
            // Union all indices of previous element
            for (int x : g[a[s.get(k - 1)]]) temp.add(x);
            Collections.sort(temp, Collections.reverseOrder());
            int way = 0;
            for (int i : temp) {
                if (a[i] == a[s.get(k - 1)]) {
                    way = (int)((way + inv[get(i, n + 1)] * 1L * suff[i]) % MOD);
                } else {
                    suff[i] = (int)(way * 1L * pw[get(i, n + 1)] % MOD);
                }
            }
            // Update BIT with elements from current stack element
            for (int x = a[s.get(k - 1)] + 1; x <= a[s.get(k)]; x++) {
                for (int i : g[x]) upd(i, 1, n);
            }
        }
        
        long ans = 0;
        int way = 0;
        // Final calculation combining prefix and suffix dp
        // Count valid subsequences matching both left and right views
        for (int i = 1; i <= n; i++) {
            if (a[i] == a[s.get(szr)]) {
                ans = (ans + suff[i] * 1L * way % MOD * pw[i - 1] + suff[i] * 1L * pref[i]) % MOD;
                way = (int)((way + inv[i] * 1L * pref[i]) % MOD);
            }
        }
        System.out.println(ans);
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) solve(sc);
    }
}


// https://github.com/VaHiX/CodeForces/