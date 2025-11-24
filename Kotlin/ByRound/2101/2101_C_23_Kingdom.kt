// Problem: CF 2101 C - 23 Kingdom
// https://codeforces.com/contest/2101/problem/C

/**
 * Problem: Maximum Beauty of Nice Arrays
 *
 * Purpose:
 * This code finds the maximum possible beauty of any "nice" array b derived from input array a,
 * where each element b[i] satisfies 1 <= b[i] <= a[i]. The beauty is defined as the sum of distances
 * d_x(c) for all distinct values x in the array c. d_x(c) is the largest gap between any two occurrences of x.
 *
 * Algorithm:
 * - For each test case, compute left and right positions for each element to maximize distance.
 * - Use a lazy segment tree to efficiently track and update intervals.
 * - Identify valid positions by querying and updating the segment tree.
 * - Calculate maximum beauty based on cumulative differences between left and right arrays.
 *
 * Time Complexity:
 * O(n log n) per test case due to operations involving the segment tree (update/query in O(log n))
 *
 * Space Complexity:
 * O(n) for storing the segment tree and auxiliary data structures.
 */

import kotlin.math.max
import kotlin.math.min

fun main() {
    repeat(readLine()!!.toInt()) {
        val n = readLine()!!.toInt()
        val xs = readLine()!!.split(" ").map(String::toInt)
        val lefts = identify(n, xs) // Compute optimal left positions
        val rights = identify(n, xs.reversed()).map { (n - 1) - it } // Compute optimal right positions
        var answer = 0L
        var curr = 0L
        for (j in 0 until min(lefts.size, rights.size)) {
            curr += (rights[j] - lefts[j]).toLong()
            answer = max(answer, curr)
        }
        println(answer)
    }
}

/**
 * Identify optimal positions for each element in the array to maximize beauty.
 * This function works by traversing the array and using a segment tree to detect
 * available positions where an element can be placed to maximize distance.
 */
fun identify(n: Int, xs: List<Int>): List<Int> {
    val segTree = LazySegmentTree(1, n)
    for (x in 1..n) {
        segTree.update(x, x, x.toLong()) // Initialize segment tree with individual elements
    }
    val result = mutableListOf<Int>()
    for ((j, x) in xs.withIndex()) {
        if (segTree[x, n] > 0L) { // If there's an available slot starting at position x
            segTree.update(x, n, -1L) // Mark that slot as used
            result.add(j) // Record the index where the element was placed
        }
    }
    return result
}

/**
 * LazySegmentTree supporting range updates and queries.
 * It uses lazy propagation to optimize multiple updates on segments.
 */
class LazySegmentTree(val treeFrom: Int, val treeTo: Int) {
    val value: LongArray
    val lazy: LongArray

    init {
        val length = treeTo - treeFrom + 1
        var e = 0
        while (1 shl e < length) {
            e++
        }
        value = LongArray(1 shl (e + 1)) // Allocate size for tree nodes
        lazy = LongArray(1 shl (e + 1)) // Allocate size for lazy values
    }

    fun update(from: Int, to: Int, delta: Long) {
        update(from, to, treeFrom, treeTo, 1, delta)
    }

    /**
     * Update range [from, to] by adding delta to all indices in that segment.
     */
    fun update(from: Int, to: Int, segFrom: Int, segTo: Int, node: Int, delta: Long): Long {
        if (from > segTo || to < segFrom) {
            // No overlap
        } else if (from <= segFrom && to >= segTo) {
            // Full overlap
            value[node] += delta
            lazy[node] += delta
        } else {
            // Partial overlap
            val mid = (segFrom + segTo) / 2
            value[node] = lazy[node] + min(
                update(from, to, segFrom, mid, 2 * node, delta),
                update(from, to, mid + 1, segTo, (2 * node) + 1, delta)
            )
        }
        return value[node]
    }

    operator fun get(from: Int, to: Int) = query(from, to, treeFrom, treeTo, 1)

    /**
     * Query the minimum value in range [from, to].
     */
    fun query(from: Int, to: Int, segFrom: Int, segTo: Int, node: Int): Long {
        if (from > segTo || to < segFrom) {
            // No overlap
            return Long.MAX_VALUE
        } else if (from <= segFrom && to >= segTo) {
            // Full overlap
            return value[node]
        } else {
            // Partial overlap
            val mid = (segFrom + segTo) / 2
            return lazy[node] + min(
                query(from, to, segFrom, mid, 2 * node),
                query(from, to, mid + 1, segTo, (2 * node) + 1)
            )
        }
    }
}


// https://github.com/VaHiX/CodeForces/