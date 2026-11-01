#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
/* Solution to program 4B
* @param n: the number of panels
* @param k: maximum number of positions in a forward jump
* @param costs: the landing costs of the panels
* @return a tuple containing the minimum total energy cost and the indices of the visited panels in increasing order(1-indexed, including n and excluding 0)
*/

std::vector <long long> M;
std::vector<long long> c;

std::vector<int> findSolution(int i, int k) {
    // Base case
    if (i == 0) {
        std::vector<int> empty;
        return empty;
    }

    int start = i - k;
    if (start < 0) {
        start = 0;
    }
    
    int prev = 0;
    for (int j = start; j <= i; j++) {
        if (M[j] + c[i] == M[i]) {
            prev = j;
        }
    }

    // Recursive step
    std::vector<int> route = findSolution(prev, k);
    route.push_back(i);
    return route;
}

std::tuple<long long, std::vector<int>> program4B(int n, int k, std::vector<int> costs){
    // Indexing is c[1...n]
    c = std::vector <long long>(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        c[i] = costs[i - 1];
    }

    M = std::vector<long long>(n + 1, 0);

    // Bellman equation: 
    // M[i] = c[i] + min { M[j] : max(0, i - k) <= j <= i - 1 }

    for (int i = 1; i <= n; i++) {
        long long best = LLONG_MAX;

        int start = i - k;
        if (start < 0) {
            start = 0;
        }

        // Look at the previously computed values to find best
        for (int j = start; j <= i - 1; j++) {
            if (M[j] < best) {
                best = M[j];
            }
        }
        M[i] = c[i] + best;
    }

    std::vector<int> route = findSolution(n, k);
    return std::make_tuple(M[n], route);
}
int main(){
    int n, k;
    std::cin >> n >> k;
    std::vector<int> costs(n);
    for(int i = 0; i < n; i++){
        std::cin >> costs[i];
    }
    auto result = program4B(n, k, costs);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result).size() << std::endl;
    for(int i = 0; i < std::get<1>(result).size(); i++){
        std::cout << std::get<1>(result)[i] << std::endl;
    }
    return 0; 
}       