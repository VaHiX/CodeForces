// Problem: CF 2123 G - Modular Sorting
// https://codeforces.com/contest/2123/problem/G

/*
G. Modular Sorting
Algorithms/Techniques: 
    - Precomputing divisors of m to analyze modular constraints
    - Using a lazy update approach for point updates (query type 1)
    - Tracking bad pairs for each divisor of m to quickly answer queries (type 2)

Time Complexity:
    For each test case:
        - Preprocessing divisors: O(√m)
        - Initializing bad count array: O(d * n) where d is number of divisors
        - Each query operation:
            - Type 1 (update): O(d) due to iterating through all divisors
            - Type 2 (query): O(1)

    Total per test case: O(√m + d * n + q * d)
    Given constraints (sum of n, q <= 1e5), this complexity is acceptable.

Space Complexity:
    - O(d) for storing divisors and mapping
    - O(d) for bad array tracking
    - O(n) for input array
    - Total: O(d + n)

Note: d is the number of divisors of m, which is at most O(√m).
*/
import java.util.*
import kotlin.math.*
fun main() {
    val input = Scanner(System.`in`)
    val t = input.nextInt()
    repeat(t) {
        solve(input)
    }
}
fun solve(input: Scanner) {
    val n = input.nextInt()
    val m = input.nextInt()
    val q = input.nextInt()
    val a = IntArray(n) { input.nextInt() }
    // Compute all divisors of m and sort them
    val divisors = mutableListOf<Int>()
    var i = 1
    while (i.toLong() * i <= m) {
        if (m % i == 0) {
            divisors.add(i)
            if (i * i != m) {
                divisors.add(m / i)
            }
        }
        i++
    }
    divisors.sort()
    // Map each divisor to its index for fast lookup
    val gToIdx = divisors.withIndex().associate { it.value to it.index }
    val numDivisors = divisors.size
    // bad[gIdx] stores number of "bad" pairs for a given divisor g (i.e., where a[i] % g > a[i+1] % g)
    val bad = IntArray(numDivisors) { 0 }
    
    // Initialize bad counts for each divisor
    for ((idx, g) in divisors.withIndex()) {
        if (g == 1) continue
        var count = 0
        var prevMod = a[0] % g
        for (j in 1 until n) {
            val currMod = a[j] % g
            if (currMod < prevMod) count++
            prevMod = currMod
        }
        bad[idx] = count
    }
    
    repeat(q) {
        val type = input.nextInt()
        if (type == 1) {
            // Update query: change a[iIdx] to x 
            val iIdx = input.nextInt() - 1
            val x = input.nextInt()
            val oldVal = a[iIdx]
            if (oldVal == x) return@repeat
            
            // Adjust bad counts for all divisors based on change at position iIdx
            for ((gIdx, g) in divisors.withIndex()) {
                if (g == 1) continue
                
                // Handle left neighbor
                if (iIdx > 0) {
                    val leftMod = a[iIdx - 1] % g
                    val oldBad = oldVal % g < leftMod // Was this pair problematic?
                    val newBad = x % g < leftMod // Is it now problematic?
                    
                    when {
                        oldBad && !newBad -> bad[gIdx]-- // Reduced bad count
                        !oldBad && newBad -> bad[gIdx]++ // Increased bad count
                    }
                }

                // Handle right neighbor
                if (iIdx < n - 1) {
                    val rightMod = a[iIdx + 1] % g
                    val oldBad = rightMod < oldVal % g
                    val newBad = rightMod < x % g
                    
                    when {
                        oldBad && !newBad -> bad[gIdx]-- 
                        !oldBad && newBad -> bad[gIdx]++
                    }
                }
            }
            a[iIdx] = x
        } else {
            // Query: Check if we can sort array using modulo k operations
            val k = input.nextInt()
            val g = gcd(k, m) // Greatest common divisor of k and m determines equivalence class
            val gIdx = gToIdx[g]!! // Index of this gcd in the sorted divisors list
            val Sg = bad[gIdx].toLong() // Count of bad pairs for this division
            val lastMod = (a.last() % g).toLong() // Modulo of last element with current divisor
            
            // If total "bad" operations needed * divisor + modulo of last element < m,
            // then it's possible to make sorted array by adding multiples of g
            if (Sg * g + lastMod < m) {
                println("YES")
            } else {
                println("NO")
            }
        }
    }
}
fun gcd(a: Int, b: Int): Int {
    var x = a
    var y = b
    while (y != 0) {
        val temp = y
        y = x % y
        x = temp
    }
    return x
}


// https://github.com/VaHiX/CodeForces/