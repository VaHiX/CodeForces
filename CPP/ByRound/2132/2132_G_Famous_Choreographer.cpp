/**
 * Problem: CF2132G - Famous Choreographer
 * 
 * This program finds the minimum number of additional cells needed to extend a grid
 * such that the original grid and its 180-degree rotation are both present in the extended grid.
 * 
 * Approach:
 * 1. Uses 2D rolling hash with two different bases to minimize hash collisions
 * 2. Precomputes prefix hashes for both original and rotated grids
 * 3. Checks all possible shifts of the rotated grid against the original
 * 4. Uses inclusion-exclusion principle to compute rectangle hashes in O(1)
 * 
 * Time Complexity: O(T * n * m * (n + m))
 *   - T: Number of test cases
 *   - n, m: Dimensions of the grid
 *   - For each test case: O(nm) for preprocessing, O(nm) for checking all shifts
 * 
 * Space Complexity: O(n * m)
 *   - Storage for original grid, rotated grid, and hash tables
 */

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

int main() {
    // Optimize I/O operations
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Initialize random number generator for hash bases
    mt19937_64 rng((unsigned)chrono::high_resolution_clock::now()
                   .time_since_epoch().count());
    
    int testCases;
    if (!(cin >> testCases)) return 0;
    
    while (testCases--) {
        int rows, cols;
        cin >> rows >> cols;
        
        // Read grid
        vector<string> grid(rows);
        for (int i = 0; i < rows; i++) 
            cin >> grid[i];
        
        // Generate random bases for hashing (with odd numbers for better distribution)
        const ull baseRow1 = (ull)rng() | 1;
        const ull baseCol1 = (ull)rng() | 1;
        const ull baseRow2 = (ull)rng() | 1;
        const ull baseCol2 = (ull)rng() | 1;
        
        // Precompute powers of bases for hashing
        vector<ull> powRow1(rows + 1), powRow2(rows + 1), 
                   powCol1(cols + 1), powCol2(cols + 1);
        
        powRow1[0] = powRow2[0] = powCol1[0] = powCol2[0] = 1;
        
        for (int i = 1; i <= rows; i++) {
            powRow1[i] = powRow1[i - 1] * baseRow1;
            powRow2[i] = powRow2[i - 1] * baseRow2;
        }
        
        for (int j = 1; j <= cols; j++) {
            powCol1[j] = powCol1[j - 1] * baseCol1;
            powCol2[j] = powCol2[j - 1] * baseCol2;
        }
        
        // Compute 2D prefix hashes for original grid
        const int width = cols + 1;
        vector<ull> hash1((rows + 1) * width);
        vector<ull> hash2((rows + 1) * width);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                ull charVal = (grid[i][j] - 'a' + 1);
                
                // Compute hash using inclusion-exclusion principle
                ull topHash = hash1[i * width + (j + 1)];
                ull leftHash = hash1[(i + 1) * width + j];
                ull diagHash = hash1[i * width + j];
                
                ull newHash = topHash * baseRow1 + leftHash * baseCol1 - 
                             diagHash * baseRow1 * baseCol1 + charVal;
                hash1[(i + 1) * width + (j + 1)] = newHash;
                
                // Second hash for double hashing
                topHash = hash2[i * width + (j + 1)];
                leftHash = hash2[(i + 1) * width + j];
                diagHash = hash2[i * width + j];
                
                newHash = topHash * baseRow2 + leftHash * baseCol2 - 
                         diagHash * baseRow2 * baseCol2 + charVal;
                hash2[(i + 1) * width + (j + 1)] = newHash;
            }
        }
        
        // Create and hash the 180-degree rotated grid
        vector<string> rotatedGrid(rows, string(cols, 'a'));
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                rotatedGrid[i][j] = grid[rows - 1 - i][cols - 1 - j];
        
        vector<ull> rotatedHash1((rows + 1) * width);
        vector<ull> rotatedHash2((rows + 1) * width);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                ull charVal = (rotatedGrid[i][j] - 'a' + 1);
                
                // Compute hash for rotated grid
                ull topHash = rotatedHash1[i * width + (j + 1)];
                ull leftHash = rotatedHash1[(i + 1) * width + j];
                ull diagHash = rotatedHash1[i * width + j];
                
                ull newHash = topHash * baseRow1 + leftHash * baseCol1 - 
                             diagHash * baseRow1 * baseCol1 + charVal;
                rotatedHash1[(i + 1) * width + (j + 1)] = newHash;
                
                // Second hash for double hashing
                topHash = rotatedHash2[i * width + (j + 1)];
                leftHash = rotatedHash2[(i + 1) * width + j];
                diagHash = rotatedHash2[i * width + j];
                
                newHash = topHash * baseRow2 + leftHash * baseCol2 - 
                         diagHash * baseRow2 * baseCol2 + charVal;
                rotatedHash2[(i + 1) * width + (j + 1)] = newHash;
            }
        }
        
        // Lambda to compute hash of a subrectangle in O(1)
        auto getSubrectHash = [&](const vector<ull>& hashTable, 
                                 const vector<ull>& rowPows,
                                 const vector<ull>& colPows,
                                 int rowStart, int rowEnd, 
                                 int colStart, int colEnd) -> ull {
            int height = rowEnd - rowStart + 1;
            int width = colEnd - colStart + 1;
            
            ull bottomRight = hashTable[(rowEnd + 1) * (cols + 1) + (colEnd + 1)];
            ull topRight = hashTable[rowStart * (cols + 1) + (colEnd + 1)] * rowPows[height];
            ull bottomLeft = hashTable[(rowEnd + 1) * (cols + 1) + colStart] * colPows[width];
            ull topLeft = hashTable[rowStart * (cols + 1) + colStart] * rowPows[height] * colPows[width];
            
            return bottomRight - topRight - bottomLeft + topLeft;
        };
        
        long long minAdditionalCells = LLONG_MAX;
        
        // Check all possible shifts of the rotated grid
        for (int rowShift = -(rows - 1); rowShift <= (rows - 1); ++rowShift) {
            int overlapRows = rows - abs(rowShift);
            if (overlapRows <= 0) continue;
            
            // Calculate overlapping region in original grid
            int origRowStart = max(0, rowShift);
            int origRowEnd = origRowStart + overlapRows - 1;
            
            // Calculate corresponding region in rotated grid
            int rotatedRowStart = origRowStart - rowShift;
            int rotatedRowEnd = rotatedRowStart + overlapRows - 1;
            
            for (int colShift = -(cols - 1); colShift <= (cols - 1); ++colShift) {
                int overlapCols = cols - abs(colShift);
                if (overlapCols <= 0) continue;
                
                // Calculate overlapping region in original grid
                int origColStart = max(0, colShift);
                int origColEnd = origColStart + overlapCols - 1;
                
                // Calculate corresponding region in rotated grid
                int rotatedColStart = origColStart - colShift;
                int rotatedColEnd = rotatedColStart + overlapCols - 1;
                
                // Check if the overlapping regions match using double hashing
                ull origHash1 = getSubrectHash(hash1, powRow1, powCol1, 
                                             origRowStart, origRowEnd, 
                                             origColStart, origColEnd);
                ull rotatedHash1_val = getSubrectHash(rotatedHash1, powRow1, powCol1,
                                                    rotatedRowStart, rotatedRowEnd,
                                                    rotatedColStart, rotatedColEnd);
                if (origHash1 != rotatedHash1_val) continue;
                
                // Second hash check to minimize collision probability
                ull origHash2 = getSubrectHash(hash2, powRow2, powCol2,
                                             origRowStart, origRowEnd,
                                             origColStart, origColEnd);
                ull rotatedHash2_val = getSubrectHash(rotatedHash2, powRow2, powCol2,
                                                    rotatedRowStart, rotatedRowEnd,
                                                    rotatedColStart, rotatedColEnd);
                if (origHash2 != rotatedHash2_val) continue;
                
                // Calculate total grid size needed for this shift
                long long totalRows = rows + abs(rowShift);
                long long totalCols = cols + abs(colShift);
                long long additionalCells = totalRows * totalCols - 1LL * rows * cols;
                
                if (additionalCells < minAdditionalCells) {
                    minAdditionalCells = additionalCells;
                }
            }
        }
        
        cout << (minAdditionalCells == LLONG_MAX ? -1 : minAdditionalCells) << "\n";
    }
    
    return 0;
}