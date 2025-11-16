// Problem: CF 2147 G - Modular Tetration
// https://codeforces.com/contest/2147/problem/G

// Problem: Modular Tetration
// Task: Calculate the density of m-tetrative integers, where a positive integer a is m-tetrative
//       if the sequence b_n = a^(b_(n-1)) stabilizes to 1 modulo m.
// Algorithm:
//   1. Factorize m into prime factors.
//   2. For each prime p in factorization of m, compute the contribution to density.
//   3. Use Euler's totient function and modular inverse to compute final result.
// Time Complexity: O(LIM * log(log(LIM)) + T * log(LIM))
// Space Complexity: O(LIM)
import java.util.*;
public class Main {
    static final int MOD = 998244353;
    static final int LIM = 1_000_000;
    static int[] spf = new int[LIM + 1]; // smallest prime factor for each number up to LIM
    static int[] invv = new int[LIM + 1]; // modular inverse of numbers from 1 to LIM
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        buildSPF();      // Precompute smallest prime factors
        buildInverse();  // Precompute modular inverses
        int T = sc.nextInt();
        while (T-- > 0) {
            int x = sc.nextInt();
            int y = sc.nextInt();
            int z = sc.nextInt();
            HashMap<Integer, Integer> cnt = new HashMap<>();
            factorizeInt(x, cnt);   // Factorize x and update prime count
            factorizeInt(y, cnt);   // Factorize y and update prime count
            factorizeInt(z, cnt);   // Factorize z and update prime count
            long ans = 1;
            ArrayList<Integer> primes_m = new ArrayList<>();
            for (Map.Entry<Integer, Integer> kv : cnt.entrySet()) {
                int p = kv.getKey();
                int k = kv.getValue();
                primes_m.add(p);
                // Multiply by (p - 1) and divide by p^k to get the contribution of prime p
                ans = ans * (p - 1) % MOD;
                ans = ans * modPow(invv[p], k) % MOD;
            }
            HashMap<Integer, Integer> E = new HashMap<>();
            for (int p : primes_m) {
                int t = p - 1;   // Euler's totient function component
                factorizeInt(t, E); // Factorize t and add to E
            }
            HashSet<Integer> Pset = new HashSet<>(primes_m);
            for (Map.Entry<Integer, Integer> kv : E.entrySet()) {
                int r = kv.getKey();
                int e = kv.getValue();
                if (Pset.contains(r)) {
                    // If r is a prime factor of m, multiply by inverse of r^e
                    ans = ans * modPow(invv[r], e) % MOD;
                } else {
                    // Otherwise compute: invr + (1 - invr) * invr^e
                    long invr = invv[r];
                    long invrE = modPow(invr, e);
                    long term = (invr + ((1 - invr + MOD) % MOD) * invrE) % MOD;
                    ans = ans * term % MOD;
                }
            }
            System.out.println(ans);
        }
    }
    // Build SPF table using sieve of Eratosthenes
    static void buildSPF() {
        Arrays.fill(spf, 0);
        spf[1] = 1;
        ArrayList<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= LIM; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.add(i);
            }
            for (int p : primes) {
                if ((long)p * i > LIM) break;
                spf[p * i] = p;
                if (p == spf[i]) break;
            }
        }
    }
    // Build modular inverse table using extended Euclidean algorithm
    static void buildInverse() {
        invv[1] = 1;
        for (int i = 2; i <= LIM; i++) {
            invv[i] = (int)((long)(MOD - MOD / i) * invv[MOD % i] % MOD);
        }
    }
    // Fast modular exponentiation
    static long modPow(long a, long e) {
        long r = 1 % MOD;
        while (e > 0) {
            if ((e & 1) != 0) r = r * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return r;
    }
    // Factorize integer n into prime factors and store counts in cnt
    static void factorizeInt(int n, HashMap<Integer, Integer> cnt) {
        if (n <= 1) return;
        while (n > 1) {
            int p = spf[n];
            int c = 0;
            while (n % p == 0) {
                n /= p;
                c++;
            }
            cnt.put(p, cnt.getOrDefault(p, 0) + c);
        }
    }
}


// https://github.com/VaHiX/CodeForces/