#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

int main() 
{
	
	int N, M;
	std::cin >> N >> M;
    std::vector<int> ans(M+1, std::numeric_limits<int>::max());
    ans[0] = 0;
    
	for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int x;
            std::cin >> x;
            ans[j+1] = std::min(ans[j+1], ans[j]) + x;
        }
        ans[0] = ans[1];
    }
    std::cout << ans[M] << std::endl;
    


	return 0;
}
