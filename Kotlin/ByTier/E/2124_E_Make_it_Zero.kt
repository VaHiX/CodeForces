// Problem: CF 2124 E - Make it Zero
// https://codeforces.com/contest/2124/problem/E

/*
 * Problem: E. Make it Zero
 * 
 * Purpose:
 *   This code solves a problem where we are given an array of positive integers,
 *   and we can perform operations that subtract a "balance" array b from a such that 
 *   the prefix sum equals the suffix sum. The goal is to make all elements in the array zero 
 *   with minimum number of operations.
 *   
 * Algorithm:
 *   - First check if it's possible to reach all zeros (sum must be even, and no element exceeds half).
 *   - Split the array into two segments where each segment sums to total_sum / 2.
 *   - Distribute elements to achieve balance between prefix and suffix.
 *   - Perform operations using balanced segments until all elements are zero.
 *   
 * Time Complexity: O(n) per test case, with preprocessing for each element.
 * Space Complexity: O(n) for storing intermediate arrays (segments and results).
 */

import java.util.*

fun main() {
    val input = Scanner(System.`in`)
    val T = input.nextInt()
    repeat(T) {
        val n = input.nextInt()
        val a = LongArray(n) { input.nextLong() }
        val S = a.sum()
        // If total sum is odd or max element exceeds half the sum, impossible
        if (S % 2 != 0L || a.maxOrNull()!! > S / 2) {
            println(-1)
            return@repeat
        }
        val m = S / 2
        var acc = 0L
        var accB = 0L
        // Segment list to hold non-zero elements with their positions
        val seg = mutableListOf<Pair<Int, Long>>()
        for (i in a.indices) {
            if (a[i] != 0L) {
                seg.add(Pair(i, a[i]))
            }
        }

        val r1 = mutableListOf<Pair<Int, Long>>() // First half of split
        val r2 = mutableListOf<Pair<Int, Long>>() // Second half of split

        var i = 0
        // Populate first segment (r1) with elements until sum reaches m
        while (i < seg.size && acc < m) {
            val (p, c) = seg[i]
            if (acc + c <= m) {
                r1.add(Pair(p, c))
                acc += c
                i++
            } else {
                val t = m - acc
                r1.add(Pair(p, t))
                seg[i] = Pair(p, seg[i].second - t)
                acc = m
                break
            }
        }

        // If first segment is full and there are remaining elements, add to second
        if (acc == m && i < seg.size) {
            val (p, c) = seg[i]
            val t = minOf(c, m - accB)
            r2.add(Pair(p, t))
            accB += t
            seg[i] = Pair(p, seg[i].second - t)
            if (seg[i].second == 0L) i++
        }

        var j = i
        // Fill second half (r2) with rest of elements
        while (j < seg.size && accB < m) {
            val (p, c) = seg[j]
            val t = minOf(c, m - accB)
            r2.add(Pair(p, t))
            accB += t
            seg[j] = Pair(p, seg[j].second - t)
            j++
        }

        // Find remainder for shifting parts when splitting is uneven
        val sh = a.maxOrNull()!! % m
        var rem = sh
        var cum = 0L
        var pr: Long = 0L 
        var pb = 0

        // Adjust first part of second list if needed for balance
        if (rem == 0L) {
            pr = r2[0].second
        } else {
            while (pb < r2.size) {
                if (cum + r2[pb].second > rem) {
                    val u = rem - cum
                    pr = r2[pb].second - u
                    break
                }
                cum += r2[pb].second
                pb++
            }
        }

        var pa = 0
        var pl = r1[pa].second // Current amount available in first list
        val res = mutableListOf<Triple<Int, Int, Long>>() // Stores (left, right, weight) triplets

        // Combine r1 and r2 to form pairs ensuring balance
        while (pa < r1.size) {
            val x = r1[pa].first
            val y = r2[pb].first
            val w = minOf(pl, pr)
            res.add(Triple(x, y, w))
            pl -= w
            pr -= w
            // Move pointer if current element is exhausted
            if (pl == 0L && ++pa < r1.size) {
                pl = r1[pa].second
            }
            if (pr == 0L) {
                pb = (pb + 1) % r2.size
                pr = r2[pb].second
            }
        }

        // Convert triplet result into intervals to be used in final splitting
        data class Interval(val l: Int, val r: Int, val w: Long)
        val iv = mutableListOf<Interval>()
        for (t in res) {
            val x = t.first
            val y = t.second
            val w = t.third
            val l = minOf(x, y)
            val r = maxOf(x, y) - 1
            iv.add(Interval(l, r, w))
        }

        val M = iv.size
        // Sort indices based on right bounds for proper partitioning
        val ord = iv.indices.sortedBy { iv[it].r } 
        val split = mutableListOf<Int>()
        val tag = IntArray(M) { -1 } // Tag each interval to a segment
        var cur = -1
        var last = -1
        
        // Group intervals by overlapping ranges (create segments for splitting)
        for (idx in ord) {
            if (last < iv[idx].l) {
                last = iv[idx].r
                split.add(last)
                cur++
            }
            tag[idx] = cur
        }

        println(split.size)
        for (op in split.indices) {
            val b = LongArray(n)
            for (k in 0 until M) {
                if (tag[k] == op) {
                    val (x, y, w) = res[k]
                    b[x] += w
                    b[y] += w
                }
            }
            println(b.joinToString(" "))
        }
    }
}


// https://github.com/VaHiX/CodeForces/