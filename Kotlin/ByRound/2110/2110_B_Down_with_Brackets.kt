// Problem: CF 2110 B - Down with Brackets
// https://codeforces.com/contest/2110/problem/B

/*
B. Down with Brackets

Purpose:
This code determines whether a given balanced bracket sequence can become unbalanced by removing exactly one opening '(' and one closing ')' bracket.

Algorithm:
The approach checks if there exists any prefix of the string where the balance (count of '(' minus count of ')') becomes zero before reaching the end. If such a prefix exists, removing the last '(' of this prefix and the corresponding ')' from the rest of the string would break the balance.

Time Complexity: O(n) where n is the length of the input string.
Space Complexity: O(1) as no extra space is used except for variables.

Techniques:
- Prefix sum tracking of bracket balance.
- Early termination when a balanced prefix is found.
*/

import java.io.PrintWriter
import java.math.BigInteger
import java.util.*
import kotlin.collections.ArrayList
import kotlin.math.abs
import kotlin.math.pow

lateinit var dp: Array<Array<Array<IntArray>>>
const val MOD = 1000000000 + 7

fun solve(caseNumber: Int) {
    val s = readLn()
    var sumSofar = 0 // Tracks the balance of brackets as we traverse the string
    
    for ((ind, i) in s.withIndex()) {
        if (i == ')') {
            sumSofar-- // Decrease balance for closing bracket
        } else {
            sumSofar++ // Increase balance for opening bracket
        }
        
        // If balance becomes zero and it's not the last character,
        // this means we have a valid prefix that can be broken by removing one pair
        if (sumSofar == 0 && ind != s.length - 1) {
            println("YES")
            return
        }
    }
    
    // If no such prefix exists, removing any pair will keep the string balanced
    println("NO")
}

fun main(args: Array<String>) {
    var t = 1
    t = readInt()
    output {
        repeat(t) {
            solve(it)
        }
    }
}

@JvmField
val INPUT = System.`in`
@JvmField
val OUTPUT = System.out
@JvmField
val _reader = INPUT.bufferedReader()

fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!

@JvmField
var _tokenizer: StringTokenizer = StringTokenizer("")
@JvmField
val _writer = PrintWriter(OUTPUT, false)

inline fun output(block: PrintWriter.() -> Unit) {
    _writer.apply(block).flush()
}

fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}

private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().trim().split(" ") 
private fun readInts() = readStrings().map { it.toInt() } as ArrayList<Int>
private fun readLongs() = readStrings().map { it.toLong() } as ArrayList<Long>
private fun readDoubles() = readStrings().map { it.toDouble() } as ArrayList<Double> 


// https://github.com/VaHiX/CodeForces/