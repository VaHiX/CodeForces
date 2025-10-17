// Problem: CF 2160 C - Reverse XOR
// https://codeforces.com/contest/2160/problem/C

/*
C. Reverse XOR
Algorithms/Techniques: Bit manipulation, reverse binary representation, palindrome check

Time Complexity: O(log n) per test case, where log n is the number of bits in n
Space Complexity: O(log n), due to string representation of binary numbers

The problem asks whether there exists a positive integer x such that x XOR f(x) = n,
where f(x) is the result of reversing the binary representation of x (without leading zeros).
The approach checks if a valid x can be formed by:
1. Considering all possible ways to construct x based on bit properties
2. For a given n, simulate reverse XOR operations and validate palindromic conditions
3. The key insight is that the constructed reversed string must form a palindrome with specific constraints
*/

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readStrings() = readLn().split(" ") 
private fun readInts() = readStrings().map { it.toInt() } 
private fun readLongs() = readStrings().map { it.toLong() } 
private fun printInts(a:List<Int>) = run { a.forEach() { print("$it ")}; println() }
private fun printLongs(a:List<Long>) = run { a.forEach() { print("$it ")}; println() }

private fun main() {
    val t = readInt()
    for (itt in 1..t) {
        val n = readInt()
        var sb = n.toString(2) // Convert n to binary string representation
        var nz = 0 // Count trailing zeros in reversed binary
        var prefz = "" // Prefix zeros to be added later
        for (i in sb.length-1 downTo 0) { // Traverse from right to left to count trailing zeros
            if (sb[i] == '0') {
                prefz += '0'
                nz++
            } else {
                break
            }
        }
        val lnsb = sb.length + nz // Length of extended binary string
        sb = prefz + sb // Prepend zero prefix to form full binary string
        val mid = (lnsb) / 2 // Midpoint of the extended string
        var can = true // Flag to determine if a valid x exists
        for (i in 0 .. mid) { // Check palindrome property
            if (sb[i] != sb[lnsb-i-1]) {
                can = false
                break
            }
        }
        if (((lnsb % 2)==1) and (sb[mid]=='1')) { // Special case: odd length and middle char is '1'
            can = false
        }
        println(if (can) "YES" else "NO")
    }
}


// https://github.com/VaHiX/CodeForces/