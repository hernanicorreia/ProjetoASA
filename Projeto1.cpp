#include <iostream>
#include <vector>


int main(){
    int lad_matx, n_inpt, n_resul;

    std::vector<std::vector<int>> matrix(lad_matx, std::vector<int>(lad_matx, 0));

    // Print the matrix
    for (int i = 0; i < lad_matx; ++i) {
        for (int j = 0; j < lad_matx; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    
}


