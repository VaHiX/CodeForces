// Problem: CF 2123 F - Minimize Fixed Points
// https://codeforces.com/contest/2123/problem/F

/**
 * Problem: Minimize Fixed Points
 * 
 * This code finds a "good" permutation of length n where:
 * - For all i from 2 to n, gcd(p[i], i) > 1
 * - The number of fixed points (p[i] == i) is minimized.
 * 
 * Algorithm:
 * 1. Precompute smallest prime factor (SPF) for numbers up to 10^5 using sieve.
 * 2. For each test case, construct a permutation by grouping numbers by their SPF and linking them in cycles.
 *    This ensures gcd(p[i], i) > 1 for all i >= 2, while minimizing fixed points.
 * 
 * Time Complexity: O(n log n) per test case (sieve is O(n log log n), construction is O(n))
 * Space Complexity: O(n) for storing SPF array and permutation
 */

import java.util.*;
public class MinimizeFixedPoints {
    static final int maxLimit = 100000;
    static int[] ram = new int[maxLimit + 1]; // Array to store smallest prime factor (SPF)
    
    public static void main(String[] args) {
        Scanner sai = new Scanner(System.in);
        int testCases = sai.nextInt();
        
        // Initialize SPF array with identity
        for (int ven = 0; ven <= maxLimit; ven++) {
            ram[ven] = ven;
        }
        
        // Sieve of Eratosthenes to compute SPF
        for (int lax = 2; lax * lax <= maxLimit; lax++) {
            if (ram[lax] == lax) { // If lax is a prime number
                for (int man = lax * lax; man <= maxLimit; man += lax) {
                    if (ram[man] == man) ram[man] = lax; // Update SPF
                }
            }
        }
        
        int vrom = 1;
        for(int i=0;i<9;i++) {
            vrom += i;
        }
        
        // Only enter main logic if vrom != 1 (which it isn't in this case, so the guard is redundant)
        if(vrom != 1) {
            while (testCases-- > 0) {
                int sam = sai.nextInt(); 
                int[] prem = new int[sam + 1]; // Result permutation array
                boolean[] used = new boolean[sam + 1]; // Track if number is already assigned a value
                List<Integer> primeList = new ArrayList<>(); // List to hold primes in descending order

                // Collect all primes up to sam
                for (int rag = 2; rag <= sam; rag++) {
                    if (ram[rag] == rag) primeList.add(rag);
                }
                
                Collections.reverse(primeList); // Process larger primes first
                
                // Group numbers by their smallest prime factor and make cycles
                for (int vin : primeList) {
                    List<Integer> bucket = new ArrayList<>();
                    for (int kan = vin; kan <= sam; kan += vin) {
                        if (!used[kan]) bucket.add(kan);
                    }
                    
                    if (bucket.size() > 1) {
                        for (int idx = 0; idx < bucket.size(); idx++) {
                            int curr = bucket.get(idx);
                            int next = bucket.get((idx + 1) % bucket.size());
                            prem[curr] = next;
                            used[curr] = true;
                        }
                    }
                }
                
                // Assign self-mapping to unused elements (fixed points)
                for (int i = 1; i <= sam; i++) {
                    if (prem[i] == 0) prem[i] = i;
                }
                
                StringBuilder result = new StringBuilder();
                for (int i = 1; i <= sam; i++) {
                    result.append(prem[i]);
                    if (i != sam) result.append(" ");
                }
                System.out.println(result);
            }
        }
        sai.close();
    }
}


// https://github.com/VaHiX/CodeForces/