#include <iostream>
#include <vector>
#include <tuple>
/* Solution to program 2
* @param n: the number of panels
* @param k: maximum number of positions in a forward jump
* @param costs: the landing costs of the panels
* @return a tuple containing the minimum total energy cost and the indices of the visited panels
    in increasing order(1-indexed, including n and excluding 0)
*/
std::tuple<long long, std::vector<int>> program2(int n, int k, std::vector<int> costs){
    std::vector<long long> c(n + 1);
    std::vector<long long> leftCost(n + 1);
    std::vector<long long> rightCost(n + 1);
    std::vector<long long> cheapestLeft(n + 1);
    std::vector<int> cheapestLeftPosition(n + 1);
    std::vector<int> leftRoute(n + 1);
    std::vector<int> route;
    
    int i;
    int p;
    int l;
    int r;
    int leftMin;
    int position;
    int leftCount;
    long long total;
    long long bestTotal;
    int bestRightPosition;
    int bestLeftPosition;
    long long allCosts;
    long long currentCost;
    long long newCost;

    c[0] = 0;
    allCosts = 0;
    int j = 1;
    while (j <= n){
        c[j] = costs[j - 1];
        allCosts = allCosts + c[j];
        j = j + 1;
    }

    // Find the peak p
    p = 1;
    i = 2;
    while(i <= n){
        newCost = c[i];
        currentCost = c[p];
        if (newCost > currentCost){
            p = i;
        }
        i = i + 1;
    }

    // Left costs
    leftCost[0] = 0;
    l = 1;
    while (l <= p){
        if (l <= k) {
            leftCost[l] = c[l];
        }
        else {
            leftCost[l] = c[l] + leftCost[l - k];
        }
        l = l + 1;
    }

    // Right costs, follows Algorithm 1
    rightCost[n] = c[n];
    r = n - 1;
    while (r >= p + 1){
        if (r + k >= n){
            rightCost[r] = c[r] + c[n];
        }
        else {
            rightCost[r] = c[r] + rightCost[r + k];
        }
        r = r - 1;
    }

    // Cheapest left costs
    cheapestLeft[p] =  leftCost[p];
    cheapestLeftPosition[p] = p;
    l = p - 1;
    while (l >= 0) {
        newCost = leftCost[l];
        currentCost = cheapestLeft[l + 1];
        if (newCost < currentCost) {
            cheapestLeft[l] = newCost;
            cheapestLeftPosition[l] = l;
        }
        if (leftCost[l] >= cheapestLeft[l + 1]){
            cheapestLeft[l] = currentCost;
            cheapestLeftPosition[l] = cheapestLeftPosition[l + 1];
        }
        l = l - 1; 
    }

    // Panel to the right of the peak
    bestTotal = allCosts + 1;
    bestRightPosition = 0;
    bestLeftPosition = 0;
    r = p + 1;
    while (r <= p + k && r <= n) {
        if (r - k >= 0){
            leftMin = r - k;
        } else {
            leftMin = 0;
        }
        total = rightCost[r] + cheapestLeft[leftMin];
        if (total < bestTotal){
            bestTotal = total;
            bestRightPosition = r;
            bestLeftPosition = cheapestLeftPosition[leftMin];
        }
        r = r + 1;
    }

    // Create route
    leftCount = 0;
    position = bestLeftPosition;
    while (position > 0){
        leftRoute[leftCount] = position;
        leftCount = leftCount + 1;
        position = position - k;
    }
    i = leftCount - 1;
    while (i>=0){
        route.push_back(leftRoute[i]);
        i = i - 1;
    }
    position = bestRightPosition;
    route.push_back(position);
    while (position < n){
        if (position + k >= n) {
            position = n;
        } if (position + k < n) {
            position = position + k; 
        }
        route.push_back(position);
    }

   return std::make_tuple(bestTotal, route);
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