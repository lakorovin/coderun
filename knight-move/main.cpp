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
    std::vector<std::vector<int>> arr(N, std::vector<int>(M, 0));
    arr[0][0] = 1;
    
	for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            {
                int x = j + 2;
                int y = i + 1;
                if (x < M && y < N) {
                    arr[y][x] += arr[i][j];
                }
            }
            {
                int x = j + 1;
                int y = i + 2;
                if (x < M && y < N) {
                    arr[y][x] += arr[i][j];
                }
            }
        }
    }
    std::cout << arr[N-1][M-1] << std::endl;
	return 0;
}
