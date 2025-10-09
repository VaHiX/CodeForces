// Problem: CF 2152 F - Triple Attack
// https://codeforces.com/contest/2152/problem/F

/*
F. Triple Attack

Purpose:
This code solves a problem where we are given a sorted array of attack timestamps and must find the maximum number of attacks that can be selected from any interval [l, r] such that no three selected attacks form a triplet within time z.

Algorithms/Techniques:
- Sliding window with preprocessing to compute parent relationships
- Binary lifting for ancestor queries in tree-like structure to support fast jump operations
- Segment tree or similar hierarchical structure over ranges to efficiently handle queries

Time Complexity: O(n log n + q log n)
Space Complexity: O(n log n)

*/
fun main() {
    val out = StringBuilder()
    repeat(readln().toInt()) {
        val (n, z) = readln().split(" ").map(String::toInt)
        val xs = listOf(0) + readln().split(" ").map(String::toInt)
        val parents = IntArray(n + 1)
        var k = 0
        for (j in 1..n) {
            while (xs[j] - xs[k + 1] > z) {
                k++
            }
            parents[j] = k // Build the parent array using sliding window technique
        }
        val ancestors = Array(n + 1) { IntArray(18) } // Binary lifting table for ancestors
        for (a in 1..n) {
            ancestors[a][0] = parents[a]
        }
        for (l in 1..17) {
            for (a in 1..n) {
                ancestors[a][l] = ancestors[ancestors[a][l - 1]][l - 1] // Preprocessing the binary lifting table
            }
        }
        val parent2 = IntArray(n + 1)
        val dist = IntArray(n + 1)
        for (j in 1..n) {
            var d = 0
            var a = j
            var b = j - 1
            for (e in 17 downTo 0) {
                if (ancestors[b][e] < ancestors[a][e] && ancestors[b][e] > parents[ancestors[a][e]]) {
                    d += 2 shl e // Fast jump with binary lifting
                    a = ancestors[a][e]
                    b = ancestors[b][e]
                }
            }
            while (a != b) {
                val na = b
                val nb = parents[a]
                d++
                a = na
                b = nb
            }
            dist[j] = d // Distance calculation for the path
            parent2[j] = a // Parent updated to reflect the current node
        }
        val ancestors2 = Array(n + 1) { IntArray(18) }
        val anDists = Array(n + 1) { IntArray(18) }
        for (a in 1..n) {
            ancestors2[a][0] = parent2[a]
            anDists[a][0] = dist[a]
        }
        for (l in 1..17) {
            for (a in 1..n) {
                ancestors2[a][l] = ancestors2[ancestors2[a][l - 1]][l - 1] // Preprocessing of second binary lifting table
                anDists[a][l] = anDists[a][l - 1] + anDists[ancestors2[a][l - 1]][l - 1]
            }
        }
        val q = readln().toInt()
        repeat(q) {
            val (l, r) = readln().split(" ").map(String::toInt)
            var a = r
            var d = 0
            for (e in 17 downTo 0) {
                if (ancestors2[a][e] >= l) { // Jump using binary lifting until node is less than l
                    d += anDists[a][e]
                    a = ancestors2[a][e]
                }
            }
            var b = a - 1
            for (e in 17 downTo 0) {
                if (ancestors[a][e] >= l) { // Continue jump up until less than l
                    d += 2 shl e
                    a = ancestors[a][e]
                    b = ancestors[b][e]
                }
            }
            d++
            if (b >= l) {
                d++ // Correct final count considering boundary nodes
            }
            out.appendLine(d)
        }
    }
    print(out)
}


// https://github.com/VaHiX/CodeForces/