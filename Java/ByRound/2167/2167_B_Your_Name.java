// Problem: CF 2167 B - Your Name
// https://codeforces.com/contest/2167/problem/B

import java.io.*;
import java.util.*;
public class Main {
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        FastScanner(InputStream is) { br = new BufferedReader(new InputStreamReader(is)); }
        String next() throws Exception {
            while (st == null || !st.hasMoreTokens()) st = new StringTokenizer(br.readLine());
            return st.nextToken();
        }
        int nextInt() throws Exception { return Integer.parseInt(next()); }
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        int q = fs.nextInt();
        StringBuilder sb = new StringBuilder();
        while (q-- > 0) {
            int n = fs.nextInt();
            String s = fs.next();
            String t = fs.next();
            int[] cnt = new int[26];
            // Count frequency of each character in string s
            for (char c : s.toCharArray()) cnt[c - 'a']++;
            // Decrement frequency for each character in string t
            for (char c : t.toCharArray()) cnt[c - 'a']--;
            boolean ok = true;
            // Check if all counts are zero (meaning s and t have same characters with same frequencies)
            for (int x : cnt) if (x != 0) { ok = false; break; }
            sb.append(ok ? "YES\n" : "NO\n");
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/CodeForces/