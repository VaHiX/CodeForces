// Problem: CF 2107 A - LRC and VIP
// https://codeforces.com/contest/2107/problem/A

/*
 * Problem: A. LRC and VIP
 * Purpose: Given an array of integers, partition it into two non-empty sequences B and C such that the GCD of elements in B is not equal to the GCD of elements in C.
 * Algorithm:
 *   - Try all possible ways to assign one element to sequence B and the rest to C.
 *   - Also try all possible ways to assign one element to sequence C and the rest to B.
 *   - For each partition, compute GCDs of both sequences and check if they are different.
 *   - Return the first valid partition found, or "No" if none exists.
 *
 * Time Complexity: O(n^2 * log(max(a))) where n is array size and log(max(a)) accounts for GCD computation.
 * Space Complexity: O(n) for storing the assignment list and temporary arrays.
 */

import java.io.BufferedReader
import java.io.InputStreamReader

fun gcd(a: Int, b: Int): Int {
    return if (b == 0) a else gcd(b, a % b) // Compute GCD using Euclidean algorithm
}

fun arrayGcd(arr: List<Int>): Int {
    return arr.reduce { a, b -> gcd(a, b) } // Reduce array to single GCD value
}

fun solveTestCase(n: Int, a: List<Int>): Pair<String, List<Int>?> {
    // Try assigning each element to B and the rest to C
    for (i in 0 until n) {
        val b = mutableListOf<Int>()
        val c = mutableListOf<Int>()
        val assignment = MutableList(n) { 0 }
        c.add(a[i]) // Put i-th element in C
        assignment[i] = 2
        for (j in 0 until n) {
            if (j != i) {
                b.add(a[j]) // Put other elements in B
                assignment[j] = 1
            }
        }
        if (b.isNotEmpty() && c.isNotEmpty()) {
            val gcdB = arrayGcd(b)
            val gcdC = arrayGcd(c)
            if (gcdB != gcdC) { // If GCDs are different, we found a valid solution
                return Pair("Yes", assignment)
            }
        }
    }

    // Try assigning each element to C and the rest to B
    for (i in 0 until n) {
        val b = mutableListOf<Int>()
        val c = mutableListOf<Int>()
        val assignment = MutableList(n) { 0 }
        b.add(a[i]) // Put i-th element in B
        assignment[i] = 1
        for (j in 0 until n) {
            if (j != i) {
                c.add(a[j]) // Put other elements in C
                assignment[j] = 2
            }
        }
        if (b.isNotEmpty() && c.isNotEmpty()) {
            val gcdB = arrayGcd(b)
            val gcdC = arrayGcd(c)
            if (gcdB != gcdC) { // If GCDs are different, we found a valid solution
                return Pair("Yes", assignment)
            }
        }
    }
    
    return Pair("No", null) // No valid partition found
}

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val tLine = br.readLine() ?: return 
    val t = tLine.toIntOrNull() ?: return 
    repeat(t) {
        val nLine = br.readLine() ?: return@repeat 
        val n = nLine.toIntOrNull() ?: return@repeat 
        val aLine = br.readLine() ?: return@repeat 
        val a = aLine.split(" ").mapNotNull { it.toIntOrNull() }
        if (a.size != n) return@repeat 
        val (result, assignment) = solveTestCase(n, a)
        println(result)
        if (result == "Yes" && assignment != null) {
            println(assignment.joinToString(" "))
        }
    }
}


// https://github.com/VaHiX/CodeForces/