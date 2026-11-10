
#include <iostream>
#include <vector>
#include <tuple>
#include <deque>
#include <algorithm>

/* Solution to program 5
* @param n: the number of panels
* @param k: maximum number of positions in a forward jump
* @param costs: the landing costs of the panels
* @return a tuple containing the minimum total energy cost and the indices of the
visited panels in increasing order(1-indexed, including n and excluding 0)
*/


std::vector<long long> M;
std::vector<long long> c;
std::vector<int> parent;

std::tuple<long long, std::vector<int>> program5(int n, int k, std::vector<int> costs) {

    //Indexing is c[1...n]
    c = std::vector<long long>(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        c[i] = costs[i - 1];
    }

    M = std::vector<long long>(n + 1, 0);

    //Base case
    M[0] = 0;
    parent = std::vector<int>(n + 1, -1);

  
    std::deque<int> Deque;
    Deque.push_back(0);

    //Bottom-up dynamic programming
    for (int i = 1; i <= n; i++) {

       
        while (!Deque.empty() && Deque.front() < i - k) {
            Deque.pop_front();
        }

        
        int prev = Deque.front();

        //Bellman equation: 
        //M[i] = c[i] + min { M[j] : max(0, i - k) <= j <= i - 1 }

        M[i] = c[i] + M[prev];
        parent[i] = prev;

      
        while (!Deque.empty() && M[Deque.back()] >= M[i]) {
            Deque.pop_back();
        }

        Deque.push_back(i);
    }

  
    std::vector<int> route;
    int i = n;

    while (i != 0) {
        route.push_back(i);
        i = parent[i];
    }

    std::reverse(route.begin(), route.end());

    return std::make_tuple(M[n], route);
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> costs(n);
    for (int i = 0; i < n; i++) {
        std::cin >> costs[i];
    }
    auto result = program5(n, k, costs);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result).size() << std::endl;
    for (int i = 0; i < std::get<1>(result).size(); i++) {
        std::cout << std::get<1>(result)[i] << std::endl;
    }
    return 0;
}
      