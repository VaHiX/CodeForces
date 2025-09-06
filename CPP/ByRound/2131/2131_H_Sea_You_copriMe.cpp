/**
 * Problem: CF2131H - Sea You copriMe
 * 
 * This program solves a problem involving finding a set of indices in an array
 * such that the corresponding elements satisfy certain coprimality conditions.
 * 
 * Approach:
 * 1. Use a sieve to precompute smallest prime factors for efficient factorization
 * 2. For each test case, process the array to find valid index sets
 * 3. Use inclusion-exclusion principle to count valid pairs
 * 4. Check for the required conditions to find the solution
 * 
 * Time Complexity: O(T * (n^2 + u log log u)) where n is array size and u is the maximum value
 * Space Complexity: O(u + n) for sieve and auxiliary arrays
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
using ll = long long;

const int MAX_VALUE = 1 << 20;  // Maximum value for sieve
vector<int> primes;             // List of prime numbers
vector<int> smallest_prime;     // smallest_prime[x] = smallest prime factor of x
int count_multiples[MAX_VALUE]; // count_multiples[d] = count of multiples of d in the array

/**
 * Sieve of Eratosthenes to precompute smallest prime factors
 */
void compute_primes() {
    smallest_prime.assign(MAX_VALUE, 0);
    for (int i = 2; i < MAX_VALUE; i++) {
        if (smallest_prime[i] == 0) {
            smallest_prime[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > smallest_prime[i] || 1LL * i * p >= MAX_VALUE) {
                break;
            }
            smallest_prime[i * p] = p;
        }
    }
}

/**
 * Get all square-free divisors of a number using its prime factorization
 */
vector<int> get_square_free_divisors(int x) {
    vector<int> divisors = {1};
    while (x > 1) {
        int p = smallest_prime[x];
        int current_size = divisors.size();
        for (int i = 0; i < current_size; i++) {
            divisors.push_back(divisors[i] * p);
        }
        while (x % p == 0) {
            x /= p;
        }
    }
    return divisors;
}

void solve_test_case() {
    int n, max_value;
    cin >> n >> max_value;
    
    // Reset and read input
    fill(count_multiples, count_multiples + max_value + 1, 0);
    vector<int> numbers(n);
    for (int &num : numbers) {
        cin >> num;
        count_multiples[num]++;
    }
    
    // Count multiples using sieve-like approach
    for (int p : primes) {
        if (p > max_value) break;
        for (int i = max_value / p; i >= 1; i--) {
            count_multiples[i] += count_multiples[i * p];
        }
    }
    
    // Calculate degrees for each number
    vector<int> degree(n, 0);
    for (int i = 0; i < n; i++) {
        if (numbers[i] == 1) {
            degree[i] = n - 1;  // 1 is coprime with everything
            continue;
        }
        
        auto divisors = get_square_free_divisors(numbers[i]);
        int coprime_count = 0;
        
        // Inclusion-exclusion to count coprime elements
        for (size_t mask = 0; mask < divisors.size(); mask++) {
            int d = divisors[mask];
            int sign = (__builtin_popcount(mask) & 1) ? -1 : 1;
            coprime_count += sign * count_multiples[d];
        }
        
        degree[i] = coprime_count - 1;  // Exclude self
    }
    
    ll total_degree = accumulate(degree.begin(), degree.end(), 0LL);
    int max_degree = *max_element(degree.begin(), degree.end());
    
    // Check if solution is possible
    if (total_degree < 4 || max_degree * 2 == total_degree) {
        cout << "0\n";
        return;
    }
    
    // Try to find a valid pair (x, y)
    int x = -1, y = -1;
    for (int i = 0; i < n && x == -1; i++) {
        if (degree[i] == 0) continue;
        
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            
            if (gcd(numbers[i], numbers[j]) == 1 && 
                (degree[i] + degree[j] - 1) * 2 != total_degree) {
                x = i + 1;
                y = j + 1;
                break;
            }
        }
    }
    
    if (x == -1) {
        cout << "0\n";
        return;
    }
    
    // Try to find a valid pair (i, j) to complete the solution
    for (int i = 0; i < n; i++) {
        if (i == x - 1 || i == y - 1) continue;
        
        int remaining_degree = degree[i];
        remaining_degree -= (gcd(numbers[x-1], numbers[i]) == 1);
        remaining_degree -= (gcd(numbers[y-1], numbers[i]) == 1);
        
        if (remaining_degree <= 0) continue;
        
        for (int j = 0; j < n; j++) {
            if (j == x - 1 || j == y - 1 || j == i) continue;
            
            if (gcd(numbers[i], numbers[j]) == 1) {
                cout << x << " " << y << " " << i + 1 << " " << j + 1 << "\n";
                return;
            }
        }
    }
    
    cout << "0\n";
}

int main() {
    // Optimize I/O operations
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Precompute primes and smallest prime factors
    compute_primes();
    
    int test_cases;
    cin >> test_cases;
    
    while (test_cases--) {
        solve_test_case();
    }
    
    return 0;
}
