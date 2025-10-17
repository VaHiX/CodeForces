// Problem: CF 2120 E - Lanes of Cars
// https://codeforces.com/contest/2120/problem/E

/**
 * Problem: E. Lanes of Cars
 *
 * Purpose:
 *   Minimize total angriness of cars in toll plaza lanes when cars are allowed to switch lanes,
 *   with each lane change increasing angriness by k units. The angriness of a car is the number of seconds it waits.
 *   
 * Algorithm/Techniques:
 *   - Binary search on the target value (vecB) for optimal lane configuration
 *   - Segment tree or direct calculation to compute total angriness based on a given target
 *   - Mathematical optimization for sum of arithmetic sequences
 *
 * Time Complexity: O(n * log(max(a_i)) * log(max(a_i)))
 * Space Complexity: O(n)
 */

import java.util.*

fun main() {
    val sc = Scanner(System.`in`)
    val t = sc.nextInt()
    repeat(t) {
        val n = sc.nextLong()
        val k = sc.nextLong()
        val vecA = LongArray(n.toInt()) { sc.nextLong() }
        val tot = vecA.sum()
        val mx = vecA.max()!!  
        var lo = 1 - k
        var hi = mx
        var vecB = mx
        fun ok(m: Long): Long {
            var res = 0L
            for (x in vecA) {
                val ku = m + k
                if (ku >= 1) res += minOf(ku, x)
                if (m > x) res += m - x
            }
            return res
        }
        while (lo <= hi) {
            val mid = (lo + hi) / 2
            if (ok(mid) >= tot) {
                vecB = mid
                hi = mid - 1
            } else {
                lo = mid + 1
            }
        }
        class Segment(val vecB: Long, val k: Long) {
            fun calc(vecA: LongArray, tot: Long): Long {
                var t = 0L
                var sum = 0L
                for (x in vecA) {
                    val ku = minOf(maxOf(0L, vecB + k), x)
                    if (ku > 0) {
                        // Sum of arithmetic sequence from k+1 to ku: ku*(ku+1)/2 - k*ku
                        sum += ku * (ku + 1) / 2 - k * ku
                        t += ku
                    }
                    if (vecB > x) {
                        // Sum of arithmetic sequence from x+1 to vecB: vecB*(vecB+1)/2 - x*(x+1)/2
                        sum += vecB * (vecB + 1) / 2 - x * (x + 1) / 2
                        t += vecB - x
                    }
                }
                val Ans = t - tot // Difference between total cars after adjustment and original
                return sum - Ans * vecB + k * tot // Adjusted sum with cost of lane changes
            }
        }
        val segment = Segment(vecB, k)
        println(segment.calc(vecA, tot))
    }
}


// https://github.com/VaHiX/CodeForces/