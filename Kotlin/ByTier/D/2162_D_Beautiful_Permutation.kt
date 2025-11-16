// Problem: CF 2162 D - Beautiful Permutation
// https://codeforces.com/contest/2162/problem/D

import java.io.BufferedReader
import java.io.InputStreamReader
fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val t = reader.readLine().toInt()
    repeat(t) {
        val n = reader.readLine().toInt()
        fun ask(y: Int, l: Int, r: Int): Long {
            println("$y $l $r")
            System.out.flush()
            return reader.readLine().toLong()
        }
        val p = n.toLong() * (n + 1) / 2 // Sum of original permutation (1 to n)
        val a = ask(2, 1, n) // Sum of modified array
        val k = a - p // Number of increments applied to the array
        var l = n // Initialize left boundary of range
        var lo = 1 // Binary search low
        var hi = n // Binary search high
        while (lo <= hi) {
            val mid = lo + (hi - lo) / 2 // Midpoint for binary search
            val ap = ask(2, 1, mid) // Sum of modified array from 1 to mid
            val pp = ask(1, 1, mid) // Sum of original array from 1 to mid
            if (ap > pp) { // If modified sum is greater, the increment range starts at or before mid
                l = mid
                hi = mid - 1 // Search left half
            } else {
                lo = mid + 1 // Search right half
            }
        }
        val r = l.toLong() + k - 1 // Calculate right boundary
        println("! $l $r")
        System.out.flush()
    }
}


// https://github.com/VaHiX/CodeForces/