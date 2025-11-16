// Problem: CF 2160 C - Reverse XOR
// https://codeforces.com/contest/2160/problem/C

/*
C. Reverse XOR
Algorithms/Techniques: Bit manipulation, XOR properties, binary representation reversal

Time Complexity: O(log n) per test case
Space Complexity: O(1)

The problem asks to determine if there exists a positive integer x such that x XOR f(x) = n,
where f(x) is the integer formed by reversing the binary representation of x.

Key Observations:
- If n is 0, then x must equal f(x), which means x is a palindrome in binary.
- For non-zero n, we analyze bits of n and try to construct valid x such that:
    - x XOR reversed(x) = n
    - This can be done by checking possible bit patterns for x based on the trailing zeros in n.

Approach:
1. Special case: if n == 0, return YES (x=1 works since f(1)=1 => 1⊕1=0)
2. For n != 0:
   - Find number of trailing zeros in n
   - Try all possible shifts k from 0 to r (trailing zeros)
   - For each shift, get current number as n shifted right by k bits.
   - Check if the reversed number has even length and check palindromic property.
   - Return YES if any valid configuration found.
*/

import java.io.*;
import java.util.*;
public class q2{
    static PrintWriter out = new PrintWriter(System.out);
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st;
    static boolean flag=true;
    static final boolean DEBUG = true; 
   static void debug(Object... args) {
    if (!DEBUG) return;
    System.err.print("[DEBUG] ");
    for (Object o : args) {
        if (o == null) {
            System.err.print("null ");
        } else if (o instanceof int[]) {
            System.err.print(Arrays.toString((int[]) o) + " ");
        } else if (o instanceof boolean[]) {   
            System.err.print(Arrays.toString((boolean[]) o) + " ");
        } else if (o instanceof long[]) {
            System.err.print(Arrays.toString((long[]) o) + " ");
        } else if (o instanceof double[]) {
            System.err.print(Arrays.toString((double[]) o) + " ");
        } else if (o instanceof List) {
            System.err.print(((List<?>) o).toString() + " ");
        } else if (o instanceof Set) {
            System.err.print(((Set<?>) o).toString() + " ");
        } else if (o instanceof Map) {
            System.err.print(((Map<?, ?>) o).toString() + " ");
        } else if (o instanceof Queue) {
            System.err.print(((Queue<?>) o).toString() + " ");
        } else if (o instanceof Deque) {
            System.err.print(((Deque<?>) o).toString() + " ");
        } else if (o instanceof Stack) {
            System.err.print(((Stack<?>) o).toString() + " ");
        } else {
            System.err.print(o + " ");
        }
    }
    System.err.println();
}
    public static void main(String[] args) throws IOException {
        int t = nextInt();
        while (t-- > 0) {
            kulfi();
        }
        out.flush();
    }
    static void kulfi() throws IOException{
    long n=nextLong();
    if(n==0){
        out.println("YES");
        return;
    }
    int r=Long.numberOfTrailingZeros(n); // Count trailing zeros in n
    boolean f=false;
    for(int k=0; k<=r && !f;k++){
        long curr=n>>k; // Right shift to get current number 
        int len=64-Long.numberOfLeadingZeros(curr); // Get number of bits in current number
        if(check(curr,len)==false) continue; // Check palindromic property of reversed binary
       if(check2(curr,len)==false)continue; // Ensure odd-length bit pattern has central 1
        f=true;
    }
    if(f){
        out.println("Yes");
    }
    else{
        out.println("No");
    }
}
static boolean check2(long x,int len){
    boolean val=(len%2==1 && ((x>>(len/2))&1)==1); // For odd length, middle bit must be 1
    return !val; // Invert result to decide when to skip
}
static boolean check(long x,int len){
    int i=0,j=len-1;
    while(i<j){
        if (((x>>i)&1)!=((x>>j)&1)) return false; // Compare bits from two ends
        ++i;
        --j;
    }
    return true;
}
    public static int ceilDiv(int a, int b) {
    return (a + b - 1) / b;
}
    static class Pair {
        long x, y;
        Pair(long x, long y) {
            this.x = x;
            this.y = y;
        }
    }
    static long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    static long lcm(long a, long b) {
        return a / gcd(a, b) * b;
    }
    static int upperBound(int[] arr, int key) {
        int l = 0, r = arr.length;
        while (l < r) {
            int mid = (l + r) >>> 1;
            if (arr[mid] <= key) l = mid + 1;
            else r = mid;
        }
        return l;
    }
    static int lowerBound(int[] arr, int key) {
        int l = 0, r = arr.length;
        while (l < r) {
            int mid = (l + r) >>> 1;
            if (arr[mid] < key) l = mid + 1;
            else r = mid;
        }
        return l;
    }
    static long modPow(long a, long b, long mod) {
        long res = 1;
        a %= mod;
        while (b > 0) {
            if ((b & 1) == 1) res = (res * a) % mod;
            a = (a * a) % mod;
            b >>= 1;
        }
        return res;
    }
    static long inverseModulo(long a, long mod) {
        return modPow(a, mod - 2, mod);
    }
    static long[] fact, invFact;
    static void precomputeFactorials(int n, long mod) {
        fact = new long[n + 1];
        invFact = new long[n + 1];
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;
        invFact[n] = inverseModulo(fact[n], mod);
        for (int i = n - 1; i >= 0; i--) invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
    static long nCr(int n, int r, long mod) {
        if (r < 0 || r > n) return 0;
        return (((fact[n] * invFact[r]) % mod) * invFact[n - r]) % mod;
    }
    static boolean[] sieve(int n) {
        boolean[] isPrime = new boolean[n + 1];
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i <= n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        return isPrime;
    }
    static String next() throws IOException {
        while (st == null || !st.hasMoreTokens())
            st = new StringTokenizer(br.readLine());
        return st.nextToken();
    }
    static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
    static long nextLong() throws IOException {
        return Long.parseLong(next());
    }
    static String nextLine() throws IOException {
        return br.readLine();
    }
}


// https://github.com/VaHiX/CodeForces/