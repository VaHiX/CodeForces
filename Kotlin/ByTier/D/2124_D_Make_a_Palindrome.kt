// Problem: CF 2124 D - Make a Palindrome
// https://codeforces.com/contest/2124/problem/D

/*
 * Problem: D. Make a Palindrome
 * Algorithm: Two-pointer with Fenwick Tree (Binary Indexed Tree)
 * Time Complexity: O(n log n) per test case due to sorting and BIT operations
 * Space Complexity: O(n) for the BIT and auxiliary arrays
 *
 * Approach:
 * 1. Normalize values by mapping them to ranks using sorted distinct elements.
 * 2. Use a Fenwick Tree (BIT) to efficiently count elements <= x in current array.
 * 3. Two pointers technique from both ends of the array.
 * 4. At each step, decide which end to remove based on whether k-th smallest element
 *    in remaining subarray allows us to maintain palindrome property.
 * 5. If we can't satisfy condition at both ends, return "NO".
 */

import java.util.*

class Fenwick(private val n: Int) {
    private val t = IntArray(n + 1)
    
    // Update BIT at index i by adding delta
    fun update(i: Int, delta: Int) {
        var idx = i
        while (idx <= n) {
            t[idx] += delta
            idx += idx and (-idx) // Move to parent node in BIT
        }
    }
    
    // Query prefix sum up to index i
    fun query(i: Int): Int {
        var idx = i
        var s = 0
        while (idx > 0) {
            s += t[idx]
            idx -= idx and (-idx) // Move to parent node in BIT
        }
        return s
    }
    
    // Query number of elements <= x
    fun leq(x: Int) = query(x)
}

fun solve(n: Int, k: Int, aInput: IntArray): String {
    val vals = aInput.toList().distinct().sorted() // Get unique sorted values for coordinate compression
    val a = aInput.map { x -> 
        vals.binarySearch(x).let { if (it < 0) -it - 1 else it } + 1 
    }.toIntArray() // Compress values to range [1, m]
    
    val m = vals.size
    val fw = Fenwick(m) // Initialize BIT
    
    // Populate BIT with all initial elements
    for (x in a) fw.update(x, +1)
    
    var l = 0
    var r = n - 1
    
    while (l < r) {
        if (a[l] == a[r]) {
            // Both ends are same; move inward without updating BIT
            l++
            r--
            continue
        }
        
        val lv = a[l]
        val rv = a[r]
        
        // Check if we can delete from left or right based on k-th smallest element
        val canL = fw.leq(lv) >= k // Can remove left element?
        val canR = fw.leq(rv) >= k // Can remove right element?

        if (!canL && !canR)
            return "NO" // Cannot proceed, impossible to make palindrome
        
        if (canL && (!canR || lv > rv)) {
            // Prefer removing from left or when left value is larger
            fw.update(lv, -1) // Remove element from BIT
            l++
        } else {
            // Otherwise remove from right
            fw.update(rv, -1)
            r--
        }
    }
    
    return "YES"
}

fun main() {
    val scanner = Scanner(System.`in`)
    val T = scanner.nextInt()
    repeat(T) {
        val n = scanner.nextInt()
        val k = scanner.nextInt()
        val a = IntArray(n) { scanner.nextInt() }
        println(solve(n, k, a))
    }
}


// https://github.com/VaHiX/CodeForces/