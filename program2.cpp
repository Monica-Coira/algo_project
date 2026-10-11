#include <iostream>
#include <vector>
#include <tuple>
/* Solution to program 2
* @param n: the number of panels
* @param k: maximum number of positions in a forward jump
* @param costs: the landing costs of the panels
* @return a tuple containing the minimum total energy cost and the indices of the visited panels in increasing order(1-indexed, including n and excluding 0)
*/
std::tuple<long long, std::vector<int>> program2(int n, int k, std::vector<int> costs){
    /************************
    * ADD YOUR CODE HERE *
    ***********************/
   return std::make_tuple(0, std::vector<int>(3)); // replace with your own result.
}
int main(){
    int n, k;
    std::cin >> n >> k;
    std::vector<int> costs(n);
    for(int i = 0; i < n; i++){
        std::cin >> costs[i];
    }
    auto result = program2(n, k, costs);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result).size() << std::endl;
    for(int i = 0; i < std::get<1>(result).size(); i++){
        std::cout << std::get<1>(result)[i] << std::endl;
    }
    return 0; 
}       