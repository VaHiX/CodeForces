// Problem: CF 1910 G - Pool Records
// https://codeforces.com/contest/1910/problem/G

/*
 * Problem: G. Pool Records
 * Purpose: Determine if a given sequence of meeting times between two swimmers in a pool is valid.
 * Algorithm: 
 *   - Simulate the pattern of meetings based on their speeds.
 *   - Assume they move at speeds vA and vB (vA != vB), and compute when they meet.
 *   - At each meeting time, there are 2 possible positions where Alice and Bob could be:
 *     One is the start point (0) or end point (50). The other position depends on the ratio of speeds.
 *   - The meeting times occur in a predictable sequence that can be validated with dynamic check.
 * Time Complexity: O(n) for each test case, where n is the size of input array
 * Space Complexity: O(n) for storing the input data
 */

fun readString(): String {
    var s = StringBuilder()
    var c: Int
    var any = false
    while (true) {
        c = System.`in`.read() // Read next character from input stream
        if (!(c != 32 && c != 10 && c != 9 && c != 13 && c >= 0)) { // Check if it's a whitespace or end of file
            if (c >= 0 && !any) continue // Skip leading whitespaces, but not if we have already started
            break // Stop reading on encountering non-whitespace after data
        }
        s.append(c.toChar()) // Add character to string builder
        any = true // Mark that we have read at least one non-whitespace char
    }
    return s.toString()
}

fun readInt(): Int {
    return Integer.parseInt(readString()) // Convert string to integer
}

fun print(x: Any?) {
    System.out.println(x) // Print result with newline
}

fun stringToCharArray(x: String): CharArray {
    var ans = CharArray(x.length)
    var i = 0
    while (i < x.length) ans[i] = x[i] // Copy characters to char array
    return ans
}

fun charArrayToString(x: CharArray): String {
    var ans = StringBuilder()
    for (i in x) ans.append(i) // Append each character to string builder
    return ans.toString()
}

// Checks whether the given array is valid according to logic of swim speeds
fun check(data: IntArray): Boolean {
    var k1 = data[0]             // The first element in the array
    var k1_next = k1 + k1        // Twice the value for comparison purposes later
    
    var k2 = 0                   // Stores second possible meeting point value (if needed)
    var k2_next = 0              // Next expected value based on k2

    var i = 0                    // Initialize index 
    while (data.size > ++i) {    // Loop through all elements except first
        var ok = false           // Flag to indicate if current element matches any valid sequence
        if (data[i] == k1_next) {
            k1_next += k1        // Update next expected value for sequence based on k1
            ok = true
        } else if (data[i] > k1_next) return false // If current exceeds expected, invalid

        else if (k2 == 0) {       // If k2 hasn't been initialized yet:
            k2 = data[i]          // Set k2 as current value
            k2_next = k2          // Initialize next expected value for k2 sequence
        }

        if (data[i] == k2_next) {
            k2_next += k2         // Update next expected value for k2 sequence
            ok = true
        } else if (k2 != 0 && data[i] > k2_next) return false // If exceeds and k2 initialized, return false

        if (!ok) return false    // If none match, invalid array
    }
    return true                    // Valid pattern found
}

fun main(x: Array<String>) {
    var T = readInt()              // Number of test cases
    while (T-- > 0) {
        var n = readInt()          // Size of input array for this test case
        var data = IntArray(n)     // Initialize array with size n
        var i = -1                 // Index initialization
        while (n > ++i) data[i] = readInt() // Fill the array from input
        if (check(data)) print("VALID") else print("INVALID")
    }
}


// https://github.com/VaHiX/codeForces/