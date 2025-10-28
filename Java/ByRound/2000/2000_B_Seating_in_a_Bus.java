// Problem: CF 2000 B - Seating in a Bus
// https://codeforces.com/contest/2000/problem/B

/*
 * Problem: Seating in a Bus
 * 
 * Algorithm/Techniques: Simulation with array tracking
 * 
 * Time Complexity: O(n) where n is the number of seats/passengers
 * Space Complexity: O(n) for the occupied array
 * 
 * Description:
 * We simulate the seating process step-by-step. For each passenger,
 * we check if their chosen seat has at least one occupied neighbor.
 * If not, the passenger did not follow the rule and we return "NO".
 * If all passengers follow the rule, we return "YES".
 */

import java.io.*;
import java.util.*;
import java.lang.*;
import static java.lang.Math.*;
public class Codeforces {
    static int MAX = Integer.MAX_VALUE,MIN = Integer.MIN_VALUE,MOD2=998244353;
    static long MAXL = Long.MAX_VALUE,MINL = Long.MIN_VALUE,MOD = (int)1e9+7;
    static void solve() {
        int n = fs.nInt();
        int[]ar = new int[n];
        for(int i=0;i<n;i++)ar[i] = fs.nInt()-1; // Convert to 0-based indexing
        int[]occupied = new int[n];
        occupied[ar[0]] = 1; // First passenger sits anywhere
        for(int i=1;i<n;i++){
            int x = ar[i];
            int taken = 0;
            // Check if left neighbor is occupied
            if(x-1>=0 && occupied[x-1]==1){
               taken++;
            }
            // Check if right neighbor is occupied
            if(x+1<n&&occupied[x+1]==1){
                taken++;
            }
            occupied[x] = 1; // Mark current seat as occupied
            if(taken == 0){
                out.println("NO");
                return;
            }
        }
        out.println("YES");
    }
    static class Triplet<T,U,V>{
        T a;
        U b;
        V c;
        Triplet(T a,U b,V c){
            this.a = a;
            this.b = b;
            this.c = c;
        }
    }
    static class Pair<A, B>{
        A fst;
        B snd;
        Pair(A fst,B snd){
            this.fst = fst;
            this.snd = snd;
        }
    }
    static boolean multipleTestCase = true;static FastScanner fs;static PrintWriter out;
    public static void main(String[]args){
        try{
            out = new PrintWriter(System.out);
            fs = new FastScanner();
            int tc = multipleTestCase?fs.nInt():1;
            while (tc-->0)solve();
            out.flush();
            out.close();
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    static class FastScanner extends PrintWriter {
        private InputStream stream;
        private byte[] buf = new byte[1<<16];
        private int curChar, numChars;
        public FastScanner() { this(System.in,System.out); }
        public FastScanner(InputStream i, OutputStream o) {
            super(o);
            stream = i;
        }
        public FastScanner(String i, String o) throws IOException {
            super(new FileWriter(o));
            stream = new FileInputStream(i);
        }
        private int nextByte() {
            if (numChars == -1) throw new InputMismatchException();
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (numChars == -1) return -1; 
            }
            return buf[curChar++];
        }
        public String next() {
            int c; do { c = nextByte(); } while (c <= ' ');
            StringBuilder res = new StringBuilder();
            do { res.appendCodePoint(c); c = nextByte(); } while (c > ' ');
            return res.toString();
        }
        public int nInt() { 
            int c; do { c = nextByte(); } while (c <= ' ');
            int sgn = 1; if (c == '-') { sgn = -1; c = nextByte(); }
            int res = 0;
            do {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res = 10*res+c-'0';
                c = nextByte();
            } while (c > ' ');
            return res * sgn;
        }
        public long nLong(){return Long.parseLong(next());}
        public double nextDouble() { return Double.parseDouble(next()); }
    }
    public static void sort(int[] arr){
        ArrayList<Integer> ls = new ArrayList<>();
        for(int x: arr)
            ls.add(x);
        Collections.sort(ls);
        for(int i=0; i < arr.length; i++)
            arr[i] = ls.get(i);
    }
    public static void sortR(int[] arr){
        ArrayList<Integer> ls = new ArrayList<>();
        for(int x: arr)
            ls.add(x);
        Collections.sort(ls,Collections.reverseOrder());
        for(int i=0; i < arr.length; i++)
            arr[i] = ls.get(i);
    }
    public static void sort(long[] arr){
        ArrayList<Long> ls = new ArrayList<>();
        for(long x: arr)
            ls.add(x);
        Collections.sort(ls);
        for(int i=0; i < arr.length; i++)
            arr[i] = ls.get(i);
    }
    public static void sortR(long[] arr){
        ArrayList<Long> ls = new ArrayList<>();
        for(long x: arr)
            ls.add(x);
        Collections.sort(ls,Collections.reverseOrder());
        for(int i=0; i < arr.length; i++)
            arr[i] = ls.get(i);
    }
}


// https://github.com/VaHiX/CodeForces/