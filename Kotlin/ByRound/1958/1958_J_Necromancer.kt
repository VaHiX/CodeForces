// Problem: CF 1958 J - Necromancer
// https://codeforces.com/contest/1958/problem/J

/*
 * Problem: J. Necromancer
 * 
 * Purpose:
 * The game simulates a battle where monsters are killed and revived as zombies.
 * For each query segment [l, r], we calculate the total number of moves required to kill all monsters in that range,
 * considering zombies attack the first alive monster in sequence.
 * 
 * Key Concepts:
 * - Monocarp starts by killing the first monster in segment [l,r], reviving it as a zombie
 * - Then each move, zombies (from current alive) reduce the health of the first live monster by total zombie strength
 * - If that monster dies, it is revived again as a zombie with same strength
 * 
 * Algorithm Technique:
 * - Brute-force for small inputs (n < 4)
 * - Optimized segment-based calculation using Fenwick Tree to maintain counts
 * - Binary search and prefix sums to efficiently compute thresholds
 * 
 * Time Complexity: O(n * K + q * M + n * log n) where K = 10, M = 1000
 * Space Complexity: O(n)
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val (n, q) = readInts(br)
    val a = readInts(br).toIntArray()
    val b = readInts(br).toIntArray()
    val l = IntArray(q)
    val r = IntArray(q)
    repeat(q) {
        val (x, y) = readInts(br)
        l[it] = x - 1
        r[it] = y - 1
    }

    // Handle small cases directly with brute-force simulation
    if (n < 4) {
        val result = IntArray(q)
        repeat(q) { i ->
            var res = 0
            var str = b[l[i]]
            for (j in l[i] + 1..r[i]) {
                res += modceil(a[j], str)
                str += b[j]
            }
            result[i] = res
        }
        result.forEach { println(it) }
        return
    }

    // Precompute prefix sums of strength arrays for efficient searching
    val acc = IntArray(n + 1)
    for (i in 1..n) {
        acc[i] = acc[i - 1] + b[i - 1]
    }

    // Array to store indices that contribute to range updates in Fenwick Tree
    val toadd = Array(n) { mutableListOf<Int>() }
    for (i in 0 until n) {
        for (j in 1 until K) {
            // For each strength (j), find the smallest index such that prefix sum > value
            val x = acc[i] - modceil(a[i], j)
            val pos = bsearch(acc, x, 0, i)
            if (pos < i) {
                toadd[pos].add(i)
            }
        }
    }

    // For each query start index, store which queries begin there
    val qr = Array(n) { mutableListOf<Int>() }
    for (i in 0 until q) {
        qr[l[i]].add(i)
    }

    // Create Fenwick Tree to perform range updates and queries efficiently
    val tree = FenwickTree(IntArray(n) { 1 })
    val res = IntArray(q)
    val firstm = IntArray(M)

    for (i in 0 until n) {
        // Add all new index updates related to current monster
        for (j in toadd[i]) {
            tree.add(j, 1)
        }

        // If no queries start at position i then skip
        if (qr[i].isEmpty()) {
            continue
        }

        // Reset strength sum starting from position i
        var str = b[i]
        for (j in 1 until minOf(M, n - i)) {
            firstm[j] = firstm[j - 1] + modceil(a[i + j], str)
            str += b[i + j]
        }

        // Process queries starting at position i
        for (j in qr[i]) {
            val right = r[j]
            res[j] = if (right - i < M) firstm[right - i] else firstm.last() + tree.range(i + M, right)
        }
    }

    res.forEach { println(it) }
}

// Helper function to compute ceiling division
fun modceil(n: Int, k: Int): Int = (n + k - 1) / k

// Binary search on prefix sum array
fun bsearch(acc: IntArray, x: Int, l: Int, r: Int): Int {
    var low = l
    var high = r
    var res = r
    while (low <= high) {
        val mid = (low + high) / 2
        if (acc[mid] > x) {
            res = mid
            high = mid - 1
        } else {
            low = mid + 1
        }
    }
    return res
}

const val M = 1000
const val K = 10

// Fenwick Tree implementation with range update functionality
class FenwickTree(private val a: IntArray) {
    private val tree = IntArray(a.size + 1)

    init {
        for (i in a.indices) {
            add(i, a[i])
        }
    }

    fun add(i: Int, added: Int) {
        var idx = i + 1
        while (idx < tree.size) {
            tree[idx] += added
            idx += idx and -idx
        }
    }

    // Return sum from index i to j inclusive
    fun range(i: Int, j: Int): Int = sum(j + 1) - sum(i)

    private fun sum(i: Int): Int {
        var res = 0
        var idx = i
        while (idx > 0) {
            res += tree[idx]
            idx -= idx and -idx
        }
        return res
    }
}

fun readInts(br: BufferedReader): List<Int> {
    val tokenizer = StringTokenizer(br.readLine())
    return List(tokenizer.countTokens()) { tokenizer.nextToken().toInt() }
}


// https://github.com/VaHiX/codeForces/