// Problem: CF 2101 D - Mani and Segments
// https://codeforces.com/contest/2101/problem/D

// Flowerbox with problem description, algorithms, and complexity
/*
Problem: Count cute subarrays in a permutation
A subarray is "cute" if LIS + LDS = length + 1
Algorithm:
1. For each position, compute leftExtreme and rightExtreme arrays:
   - leftExtreme[j]: minimum position where subarray starting at j can extend left
   - rightExtreme[j]: maximum position where subarray starting at j can extend right
2. Use sliding window with Lazy Segment Tree to efficiently count valid subarrays
3. For each left pointer, expand right pointer until window is invalid
4. Count valid ranges using lazy propagation

Time Complexity: O(n log n) per test case
Space Complexity: O(n) for segment trees and auxiliary arrays
*/

import kotlin.math.max
import kotlin.math.min

fun main() {
    repeat(readLine()!!.toInt()) {
        val n = readLine()!!.toInt()
        val p = listOf(0) + readLine()!!.split(" ").map(String::toInt)
        val maxSegTree = MaxSegmentTree(1, n)
        val leftExtreme = IntArray(n + 1)
        for (j in 1..n) {
            val k = p[j]
            val lesser = maxSegTree[1, k]  // Get max index <= k
            val greater = maxSegTree[k, n] // Get max index >= k
            leftExtreme[j] = min(lesser, greater) + 1 // Compute left boundary
            maxSegTree[k] = j // Update segment tree
        }
        val minSegTree = MinSegmentTree(1, n)
        minSegTree.value.fill(n + 1)
        val rightExtreme = IntArray(n + 1)
        for (j in n downTo 1) {
            val k = p[j]
            val lesser = minSegTree[1, k]  // Get min index <= k
            val greater = minSegTree[k, n] // Get min index >= k
            rightExtreme[j] = max(lesser, greater) - 1 // Compute right boundary
            minSegTree[k] = j // Update segment tree
        }
        val lazySegTree = LazySegmentTree(1, n)
        var r = 0
        var answer = 0L
        for (l in 1..n) {
            while (r <= n && lazySegTree[1, n] == r - l + 1) {
                r++
                if (r <= n) {
                    lazySegTree.update(leftExtreme[r], rightExtreme[r], 1) // Expand window
                }
            }
            answer += (r - l).toLong() // Count valid subarrays
            lazySegTree.update(leftExtreme[l], rightExtreme[l], -1) // Shrink window
        }
        println(answer)
    }
}

class MinSegmentTree(val treeFrom: Int, treeTo: Int) {
    val value: IntArray
    val length: Int
    init {
        var e = 0
        while (1 shl e < treeTo - treeFrom + 1) {
            e++
        }
        value = IntArray(1 shl (e + 1))
        length = 1 shl e
    }
    operator fun set(index: Int, delta: Int) {
        var node = index - treeFrom + length
        value[node] = delta
        node = node shr 1
        while (node > 0) {
            value[node] = min(value[node shl 1], value[(node shl 1) + 1])
            node = node shr 1
        }
    }
    operator fun get(index: Int) = value[index - treeFrom + length]
    operator fun get(fromIndex: Int, toIndex: Int): Int {
        if (toIndex < fromIndex) {
            return Int.MAX_VALUE
        }
        var from = fromIndex + length - treeFrom
        var to = toIndex + length - treeFrom + 1
        var res: Int = Int.MAX_VALUE
        while (from + (from and -from) <= to) {
            res = min(res, value[from / (from and -from)])
            from += from and -from
        }
        while (to - (to and -to) >= from) {
            res = min(res, value[(to - (to and -to)) / (to and -to)])
            to -= to and -to
        }
        return res
    }
}

class MaxSegmentTree(val treeFrom: Int, treeTo: Int) {
    val value: IntArray
    val length: Int
    init {
        var e = 0
        while (1 shl e < treeTo - treeFrom + 1) {
            e++
        }
        value = IntArray(1 shl (e + 1))
        length = 1 shl e
    }
    operator fun set(index: Int, delta: Int) {
        var node = index - treeFrom + length
        value[node] = delta
        node = node shr 1
        while (node > 0) {
            value[node] = max(value[node shl 1], value[(node shl 1) + 1])
            node = node shr 1
        }
    }
    operator fun get(index: Int) = value[index - treeFrom + length]
    operator fun get(fromIndex: Int, toIndex: Int): Int {
        if (toIndex < fromIndex) {
            return Int.MIN_VALUE
        }
        var from = fromIndex + length - treeFrom
        var to = toIndex + length - treeFrom + 1
        var res: Int = Int.MIN_VALUE
        while (from + (from and -from) <= to) {
            res = max(res, value[from / (from and -from)])
            from += from and -from
        }
        while (to - (to and -to) >= from) {
            res = max(res, value[(to - (to and -to)) / (to and -to)])
            to -= to and -to
        }
        return res
    }
}

class LazySegmentTree(val treeFrom: Int, val treeTo: Int) {
    val value: IntArray
    val lazy: IntArray
    init {
        val length = treeTo - treeFrom + 1
        var e = 0
        while (1 shl e < length) {
            e++
        }
        value = IntArray(1 shl (e + 1))
        lazy = IntArray(1 shl (e + 1))
    }
    fun update(from: Int, to: Int, delta: Int) {
        update(from, to, treeFrom, treeTo, 1, delta)
    }
    fun update(from: Int, to: Int, segFrom: Int, segTo: Int, node: Int, delta: Int): Int {
        if (from > segTo || to < segFrom) {
        } else if (from <= segFrom && to >= segTo) {
            value[node] += delta
            lazy[node] += delta
        } else {
            val mid = (segFrom + segTo) / 2
            value[node] = lazy[node] + max(
                update(from, to, segFrom, mid, 2 * node, delta),
                update(from, to, mid + 1, segTo, (2 * node) + 1, delta)
            )
        }
        return value[node]
    }
    operator fun get(from: Int, to: Int) = query(from, to, treeFrom, treeTo, 1)
    fun query(from: Int, to: Int, segFrom: Int, segTo: Int, node: Int): Int {
        if (from > segTo || to < segFrom) {
            return Int.MIN_VALUE
        } else if (from <= segFrom && to >= segTo) {
            return value[node]
        } else {
            val mid = (segFrom + segTo) / 2
            return lazy[node] + max(
                query(from, to, segFrom, mid, 2 * node),
                query(from, to, mid + 1, segTo, (2 * node) + 1)
            )
        }
    }
}


// https://github.com/VaHiX/CodeForces/