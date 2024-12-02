#include <iostream>
#include <vector>

void manage_data(int lad_matx, int n_impt) {
    std::vector<std::vector<int>> matrix(lad_matx, std::vector<int>(lad_matx, 0));

    // Print the matrix
    for (int i = 0; i < lad_matx; ++i) {
        for (int j = 0; j < lad_matx; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(){}

