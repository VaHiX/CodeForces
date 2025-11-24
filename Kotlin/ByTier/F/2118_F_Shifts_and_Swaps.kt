// Problem: CF 2118 F - Shifts and Swaps
// https://codeforces.com/contest/2118/problem/F

/*
 * Problem: F. Shifts and Swaps
 * Purpose: Determine if array 'a' can be transformed into array 'b' using cyclic shifts and swaps of adjacent elements differing by at least 2.
 * 
 * Algorithms:
 * - Duval's algorithm for finding lexicographically minimal rotation (used in canon function)
 * - Graph-based DFS traversal to sort elements according to a specific ordering
 * 
 * Time Complexity: O(n * m + sum of n over all test cases)
 * Space Complexity: O(n + m)
 */

import java.util.*

fun main() {
    val scanner = Scanner(System.`in`)
    val tt = scanner.nextInt()
    
    // Duval's algorithm to find minimal rotation index (for canonical form)
    fun duval(n: Int, s: List<Int>): Int {
        assert(n >= 1)
        var i = 0
        var ans = 0
        while (i < n) {
            ans = i
            var j = i + 1
            var k = i
            // Loop to find the lexicographically smallest rotation via Duval's algorithm
            while (j < n + n && !(s[j % n] < s[k % n])) {
                if (s[k % n] < s[j % n]) {
                    k = i // Reset k if current character is larger
                } else {
                    k++ // Move forward in the candidate string
                }
                j++
            }
            // Advance i by incrementing it to avoid redundant checks
            while (i <= k) {
                i += j - k
            }
        }
        return ans
    }

    fun duval(s: List<Int>): Int = duval(s.size, s)

    repeat(tt) {
        val n = scanner.nextInt()
        val m = scanner.nextInt()
        
        // Function to compute canonical form of a sequence based on ordering rules
        fun canon(a: MutableList<Int>): List<Int> {
            // Group indices by value for efficient lookup
            val atA = Array(m) { mutableListOf<Int>() }
            for (i in 0 until n) {
                atA[a[i]].add(i)
            }

            // Build a graph where each node points to its next greater element
            val g = Array(n) { mutableListOf<Int>() }
            for (i in 0 until n) {
                if (a[i] < m - 1) {
                    val v = atA[a[i] + 1]
                    val it = v.binarySearch(i).let { if (it < 0) -it - 1 else it }
                    val next = if (it == v.size) v[0] else v[it]
                    g[next].add(i)
                }
            }

            // Apply rotations to keep graph consistent with position ordering
            for (i in 0 until n) {
                g[i].sort()
                val it = g[i].binarySearch(i).let { if (it < 0) -it -1 else it }
                Collections.rotate(g[i], -it)
            }

            // Perform DFS to build canonical sequence
            val b = mutableListOf<Int>()
            fun dfs(v: Int) {
                for (u in g[v]) {
                    dfs(u)
                }
                b.add(a[v])
            }

            // Start DFS from nodes with maximum value elements
            for (i in 0 until n) {
                if (a[i] == m - 1) {
                    dfs(i)
                }
            }
            assert(b.size == n)
            
            // Rotate canonical form to minimum rotation and return
            val d = duval(b)
            Collections.rotate(b, -d)
            return b
        }

        // Read arrays a and b, convert to 0-based indexing
        val a = MutableList(n) { scanner.nextInt() - 1 }
        val b = MutableList(n) { scanner.nextInt() - 1 }
        
        // Compare canonical forms of both arrays
        println(if (canon(a) == canon(b)) "YES" else "NO")
    }
}


// https://github.com/VaHiX/CodeForces/