// Problem: CF 2152 D - Division Versus Addition
// https://codeforces.com/contest/2152/problem/D

/*
 * Problem: D. Division Versus Addition
 * Purpose: For each query, calculate the minimum number of moves Poby makes in a game where:
 *          - Poby reduces an element to floor(element/2) on his turn (starting first)
 *          - Rekkles increases an element by 1 on his turn
 *          - Game ends when all elements become 1
 *          - Both players play optimally
 * 
 * Algorithm:
 *   - For each number, compute how many division operations Poby needs to make it 1.
 *   - Use prefix sums for range queries of the total number of required moves.
 *   - Special handling for numbers where the process has a different pattern (like 3 or (2^(k-1)+1)).
 * 
 * Time Complexity: O(n log max(a[i]) + q)
 * Space Complexity: O(n)
 */
import java.io.*;
import java.util.*;
public class D_Division_Versus_Addition{
    static class FastReader{
        BufferedReader br;
        StringTokenizer st;
        public FastReader(){
            br=new BufferedReader(new InputStreamReader(System.in));
        }
        String next(){
            while(st==null || !st.hasMoreTokens()){
                try {
                    st=new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
        int nextInt(){
            return Integer.parseInt(next());
        }
        long nextLong(){
            return Long.parseLong(next());
        }
        double nextDouble(){
            return Double.parseDouble(next());
        }
        String nextLine(){
            String str="";
            try {
                str=br.readLine().trim();
            } catch (Exception e) {
                e.printStackTrace();
            }
            return str;
        }
    }
    static FastReader vt = new FastReader();
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) {
        try {
            int testCases = 1;
            testCases = vt.nextInt();
            while(testCases-- > 0){
                solve();
            }
            out.flush();
        } catch (Exception e) {
            return;
        }
    }
    static void solve(){
        int n = vt.nextInt();
        int q = vt.nextInt();
        long[] ar = new long[n];
        for(int i = 0; i < n; i++) ar[i] = vt.nextLong();
        int[] count = new int[n+1];
        for(int i=0;i<n;i++){
            int maxbit = getmaxbit(ar[i]);
            if((ar[i]!=(1L<<(maxbit-1))) && ar[i]>3){
                count[i+1] = maxbit;
                // Special case where the number is just more than a power of 2 and not 3
                if(ar[i]==(1L<<(maxbit-1))+1)
                    count[i+1]--;
            }else{
                // Normal case or small numbers that have a different pattern
                count[i+1] = maxbit-1;
            }
        }
        // Prefix sum of moves needed for each position
        for(int i=1;i<=n;i++) count[i] += count[i-1];
        int[] c3 = new int[n+1];
        for(int i=0;i<n;i++){
            int maxbit = getmaxbit(ar[i]);
            // If the number is 3 or of form (2^(k-1) + 1), increment special counter
            if(ar[i]==3){
                c3[i+1] = 1;
            }else if (ar[i]==(1L<<(maxbit-1))+1) {
                c3[i+1] = 1;
            }
        }
        for(int i=1;i<=n;i++) c3[i] += c3[i-1];
        while(q-- > 0){
            int l = vt.nextInt();
            int r = vt.nextInt();
            // Get total moves from l to r
            int c2 = count[r]-count[l-1];
            // Count of special "addition" moves from l to r
            int c33 = c3[r]-c3[l-1];
            // Final answer is the number of division rounds + half the number of additions (as Poby can make one move for two additions)
            long ans = c2+c33/2;
            out.println(ans);
        }
    }
    static void merge(int arr[], int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        int L[] = new int[n1];
        int R[] = new int[n2];
        for (int i = 0; i < n1; ++i)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[m + 1 + j];
        int i = 0, j = 0;
        int k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    static void sort(int arr[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            sort(arr, l, m);
            sort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }
    static void sort2d(int arr[][], int l, int r, int index) {
        if (l < r) {
            int m = l + (r - l) / 2;
            sort2d(arr, l, m, index);
            sort2d(arr, m + 1, r, index);
            merge(arr, l, m, r, index);
        }
    }
    static void merge(int arr[][], int l, int m, int r, int index) {
        // Custom merge for 2D arrays based on column index
        int n1 = m - l + 1;
        int n2 = r - m;
        int[][] L = new int[n1][];
        int[][] R = new int[n2][];
        for (int i = 0; i < n1; ++i)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[m + 1 + j];
        int i = 0, j = 0;
        int k = l;
        while (i < n1 && j < n2) {
            if (L[i][index] <= R[j][index]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    static int getmaxbit(long num){
        // Find the position of the highest set bit in the number
        int res = 0;
        while(num > 0){
            num >>= 1;
            res++;
        }
        return res;
    }
}


// https://github.com/VaHiX/CodeForces/