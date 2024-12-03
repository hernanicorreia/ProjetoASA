#include <iostream>
#include <vector>


int main(){
    int lad_matx, n_inpt, n_resul, num;
    std::string line;
    std::getline(std::cin, line);
    std::sscanf(line, %d %d, &lad_matx, &n_inpt);

    std::vector<std::vector<int>> matrixeq(lad_matx, std::vector<int>(lad_matx, 0));

    // Print the matrix
    for (int i = 0; i < lad_matx; ++i) {
        std::getline(std::cin, line);
        std::stringstream ss(line);
        for (int j = 0; j < lad_matx; ++j) {
            ss >> matrixeq[i][j];
        }
    }

    std::vector<std::vector<std::vector<std::vector<int>>>> matrixsol(n_inpt, std::vector<std::vector<int>>(n_inpt, std::vector<int>(lad_matx, std::vector<int>(4, 0))));
    
    
}


