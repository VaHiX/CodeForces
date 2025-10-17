// Problem: CF 2116 C - Gellyfish and Flaming Peony
// https://codeforces.com/contest/2116/problem/C

/*
 * C. Gellyfish and Flaming Peony
 *
 * Problem Description:
 * Given an array of positive integers, we need to make all elements equal by repeatedly replacing
 * one element with gcd of itself and another element. The goal is to find the minimum number of operations.
 *
 * Algorithms/Techniques:
 * - BFS (Breadth-First Search) on GCD values
 * - Preprocessing unique elements and their frequencies
 * - Mathematical property: gcd(a, b) <= min(a, b), so gcds form a decreasing sequence towards the GCD of all numbers
 *
 * Time Complexity: O(n * sqrt(max_a) + max_a * log(max_a))
 * Space Complexity: O(max_a)
 */

import java.util.*

const val MAXA = 5001
const val INF = 1_000_000_000

fun gcd(a1: Int, b1: Int): Int {
    var a = a1
    var b = b1
    while (b != 0) {
        val t = b
        b = a % b
        a = t
    }
    return a
}

fun BFS(G: Int, vecH: List<Int>): Int {
    // kk[x] stores minimum operations to reach GCD x from any initial element
    val kk = IntArray(MAXA) { INF }
    val q: Queue<Int> = ArrayDeque()
    
    // Initialize queue with all unique values in input array
    for (v in vecH) {
        kk[v] = 0
        q.offer(v)
    }
    
    // BFS to compute minimum operations for each possible GCD value
    while (q.isNotEmpty()) {
        val v = q.poll()
        for (x in vecH) {
            val g = gcd(v, x)
            if (kk[g] > kk[v] + 1) {
                kk[g] = kk[v] + 1
                q.offer(g)
            }
        }
    }
    
    return kk[G]
}

fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()
    
    for (test in 1..t) {
        val n = scanner.nextInt()
        val a = IntArray(n) { scanner.nextInt() }
        
        // Compute overall GCD of all elements
        var G = 0
        for (x in a) {
            G = gcd(G, x)
        }
        
        // Count frequency of each element and collect unique ones
        var cnt = 0
        val res = BooleanArray(MAXA)
        val vecH = mutableListOf<Int>()
        for (x in a) {
            if (x == G) cnt++
            if (!res[x]) {
                res[x] = true
                vecH.add(x)
            }
        }
        
        // If all elements are already equal to G, no operations needed
        if (cnt > 0) {
            println(n - cnt)
        } else {
            // Otherwise, compute minimum steps using BFS and add n-1 for final convergence
            val ans = BFS(G, vecH)
            println(ans + n - 1)
        }
    }
}


// https://github.com/VaHiX/CodeForces/