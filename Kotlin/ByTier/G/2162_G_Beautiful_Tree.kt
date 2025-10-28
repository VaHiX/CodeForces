// Problem: CF 2162 G - Beautiful Tree
// https://codeforces.com/contest/2162/problem/G

// Purpose: This code constructs a "beautiful tree" with n vertices, where the sum of products of vertex labels for all edges is a perfect square.
// Algorithm:
//   - For n = 2, it's impossible to form a beautiful tree, so we return -1.
//   - For other cases:
//     1. Try to find a vertex C such that the sum of products of edges from C to all others forms a perfect square.
//     2. If such C is found, construct a star graph with C as the center.
//     3. If not, try to find a perfect square close to (S - 1)^2, where S is the sum of 1 to n, to form a valid structure.
// Time Complexity: O(n * sqrt(n)) in worst case per test
// Space Complexity: O(1) excluding input/output

import kotlin.math.sqrt

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val n = readLine()!!.toInt() // Read number of vertices
        if (n == 2) {
            println(-1) // No beautiful tree exists with only 2 vertices
            return@repeat
        }
        val S = n.toLong() * (n + 1) / 2 // Sum of all vertex labels from 1 to n
        var C = -1
        // Try to find a candidate center vertex C such that sum of edges from C is a perfect square
        for (x in 1..n) {
            val s = x.toLong() * (S - x)
            val y = sqrt(s.toDouble())
            val r = (y + 0.5).toLong()
            if (r * r == s) {
                C = x
                break
            }
        }
        if (C != -1) {
            // If such C is found, create a star tree with C as center
            for (i in 1..n) {
                if (i != C) println("$C $i")
            }
            return@repeat
        }
        // If no such C is found, try another approach:
        var u = S - 1
        var yy = sqrt(u.toDouble())
        var m = yy.toLong()
        if (m * m < u) m++ // Ensure m^2 is at least u
        val M = S - 3 // Max allowed value for edge calculation
        while (true) {
            val target = m * m
            val d = target - u
            if (d == 1L || d == 2L || d > M) {
                m++ // Skip invalid d values
                continue
            }
            val v = mutableListOf<Int>()
            // Decompose d into sum of two or more parts based on constraints
            if (d in 3..n.toLong()) {
                v.add(d.toInt())
            } else if (d > n) {
                val r = d - n
                when (r) {
                    0L -> v.add(n)
                    1L -> {
                        v.add(n - 2)
                        v.add(3)
                    }
                    2L -> {
                        v.add(n - 1)
                        v.add(3)
                    }
                    else -> {
                        v.add(n)
                        v.add(r.toInt())
                    }
                }
            } else {
                m++ // Skip invalid d
                continue
            }
            val st = v.toSet()
            // Output edges from vertex 1 to all other vertices except those in v
            for (j in 2..n) {
                if (j !in st) println("1 $j")
            }
            // Output edges from vertex 2 to vertices in v
            for (y in v) println("2 $y")
            break
        }
    }
}


// https://github.com/VaHiX/CodeForces/