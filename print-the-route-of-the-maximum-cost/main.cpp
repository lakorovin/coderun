#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>

int main() 
{
	
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> directions(N, std::vector<int>(M, 0));
    std::vector<int> ans(M+1, 0);
    ans[0] = -1;
    
	for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int x;
            std::cin >> x;
            if (ans[j+1] > ans[j]) {
                directions[i][j] = 1;
            }
            ans[j+1] = std::max(ans[j+1], ans[j]) + x;
        }
    }
    std::cout << ans[M] << std::endl;
    int x = M - 1;
    int y = N - 1;
    std::vector<int> path;
    while (x+y > 0) {
        path.push_back(directions[y][x]);
        if (directions[y][x]) {
            --y;
        } else {
            --x;
        }
    }
    for (size_t count = path.size(); count > 0; --count) {
        if (path[count-1] == 1) {
            std::cout << "D ";
        } else {
            std::cout << "R ";
        }
    }
    std::cout << std::endl;

	return 0;
}
