using namespace std;
#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <utility>
/* Solution to program 3
* @param n: the number of panels
* @param k: maximum number of positions in a forward jump
* @param costs: the landing costs of the panels
* @return a tuple containing the minimum total energy cost and the indices of the visited panels in increasing order(1-indexed, including n and excluding 0)
*/

std::tuple<long long, std::vector<int>> program3(int n, int k, std::vector<int>& costs){
    if (n == 0) {
        vector<int> noPath;
        return make_tuple(0, noPath);
    }

    vector<int> cheapestPath;
    long long minCost = LLONG_MAX;  

    // Test every jump size from 1 to k to jump to panel n
    for (int i = 1; i <= k; i++) {
        if (i > n) {
            break;
        }
        // Find the cheapest route to panel n-i
        auto [routeCost, routePath] = program3(n - i, k, costs);
        if (routeCost < minCost) {
            minCost = routeCost;
            cheapestPath = move(routePath);
        }
    }
    
    minCost = minCost + costs[n - 1];
    cheapestPath.push_back(n);

    return make_tuple(minCost, move(cheapestPath));
}

int main(){
    int n, k;
    std::cin >> n >> k;
    std::vector<int> costs(n);
    for(int i = 0; i < n; i++){
        std::cin >> costs[i];
    }
    auto result = program3(n, k, costs);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result).size() << std::endl;
    for(int i = 0; i < std::get<1>(result).size(); i++){
        std::cout << std::get<1>(result)[i] << std::endl;
    }
    return 0; 
}       