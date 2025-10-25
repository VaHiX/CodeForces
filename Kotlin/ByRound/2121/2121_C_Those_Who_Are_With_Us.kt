// Problem: CF 2121 C - Those Who Are With Us
// https://codeforces.com/contest/2121/problem/C

/*
 * C. Those Who Are With Us
 *
 * Problem Description:
 * Given an n x m matrix of integers, perform exactly one operation where we choose a row r and column c,
 * and decrease all elements in row r and column c by 1. The goal is to minimize the maximum value in the matrix after this operation.
 *
 * Algorithms/Techniques:
 * - Greedy approach with preprocessing:
 *   1. Find the maximum element and count how many times it appears.
 *   2. For each row and column, count how many times the max element occurs.
 *   3. Try all possible rows and columns to see if applying the operation reduces the maximum value.
 *
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n + m) for auxiliary arrays
 */

import java.io.BufferedReader
import java.io.BufferedWriter
import java.io.InputStreamReader
import java.io.OutputStreamWriter

val MOD: Long = 1_000_000_007L

fun GCD(a: Long, b: Long): Long = if (b == 0L) a else GCD(b, a % b)

fun main() {
    BufferedReader(InputStreamReader(System.`in`)).use { reader ->
        BufferedWriter(OutputStreamWriter(System.out)).use { writer ->
            val t: Int = reader.readLine().toInt()
            repeat(t) {
                val (n, m) = reader.readLine().split(" ").map { it.toInt() }
                val mat: MutableList<MutableList<Int>> = mutableListOf()
                for (i in 0..<n) {
                    mat.add(reader.readLine().split(" ").map { it.toInt() }.toMutableList())
                }
                writer.write(C_2121(n, m, mat).toString())
                writer.newLine()
                writer.flush()
            }
        }
    }
}

fun C_2121(n: Int, m: Int, matrix: MutableList<MutableList<Int>>): Any {
    // Find the maximum element and its count
    var maxElem = Int.MIN_VALUE
    var maxCount = 0
    for (i in 0..<n) {
        for (j in 0..<m) {
            if (matrix[i][j] > maxElem) {
                maxElem = matrix[i][j]
                maxCount = 1
            } else if (matrix[i][j] == maxElem) {
                maxCount += 1
            }
        }
    }

    // Count how many times the maximum element appears in each row and column
    val maxElemCountRow: MutableList<Int> = MutableList(n) { 0 }
    val maxElemCountCol: MutableList<Int> = MutableList(m) { 0 }
    for (i in 0..<n) {
        for (j in 0..<m) {
            if (matrix[i][j] == maxElem) {
                maxElemCountRow[i] += 1
                maxElemCountCol[j] += 1
            }
        }
    }

    // Determine whether we can reduce the maximum element to maxElem - 1
    var X = 0
    for (i in 0..<n) {
        for (j in 0..<m) {
            var C = 0
            if (matrix[i][j] == maxElem) {
                C = 1
            }
            // If applying operation on row i and column j removes all occurrences of max element,
            // then the new maximum can be reduced by 1
            if ((maxElemCountRow[i] + maxElemCountCol[j]) - C == maxCount) {
                X = 1
                break
            }
        }
    }

    return maxElem - X
}


// https://github.com/VaHiX/CodeForces/