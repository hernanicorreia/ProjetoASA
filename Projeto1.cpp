#include <iostream>
#include <vector>
#include <sstream>




int main() {
    int lad_matx, n_inpt, n_resul, num;
    std::string line;
    std::getline(std::cin, line);
    std::sscanf(line.c_str(), "%d %d", &lad_matx, &n_inpt);
    

    std::vector<std::vector<int>> matrixeq(lad_matx, std::vector<int>(lad_matx, 0));

    int add_sol(int sol, int k, int sol_e, int sol_d, int col, int lin){
        for(i = 0; i < lad_matx; i++){
            if(matrixsol[lin][col][i][0]==0){
                matrixsol[lin][col][i][0] = sol;
                matrixsol[lin][col][i][1] = k;
                matrixsol[lin][col][i][2] = sol_e;
                matrixsol[lin][col][i][3] = sol_d;
                return 1
            }
            if(matrixsol[lin][col][i][0] == sol)
                return 0;
        }
        return -1
    }

    


    // Input the matrix
    for (int i = 0; i < lad_matx; ++i) {
        std::getline(std::cin, line);
        std::stringstream ss(line);
        for (int j = 0; j < lad_matx; ++j) {
            ss >> matrixeq[i][j];
        }
    }

    

    std::vector<int> eq(n_inpt, 0);
    std::getline(std::cin, line);
    std::stringstream ss_eq(line);
    for (int i = 0; i < n_inpt; ++i) {
        ss_eq >> eq[i];
    }


    std::getline(std::cin, line);
    std::sscanf(line.c_str(), "%d", &n_resul);

    if(n_inpt == 1){
        if(eq[0] == n_resul){
            std::cout << 1 << std::endl;
            std::cout << eq[0] << std::endl;
            return 0;
        }
        else{
            std::cout << 0 << std::endl;
            return 0;
        }
    }


    std::vector<std::vector<std::vector<std::vector<int>>>> matrixsol(n_inpt, std::vector<std::vector<std::vector<int>>>(n_inpt, std::vector<std::vector<int>>(lad_matx, std::vector<int>(4, 0))));
    
    for (int i = 0; i < n_inpt; ++i) {
        if (i > 0) {
            matrixsol[i][i][0][0] = eq[i];
        }
    }

    for (int i = 0; i < n_inpt; i++) {
        int j = i+1;
        int sol_esq = eq[i]-1;
        int sol_dir = eq[j]-1;
        int sol = matrixeq[sol_esq][sol_dir];
        matrixsol[i][j][0][0] = sol;
        matrixsol[i][j][0][2] = sol_esq +1;
        matrixsol[i][j][0][3] = sol_dir +1;
        }
    int counter = 2;
    while(matrixsol[0][n_inpt-1][0][0] == 0){
        for (int i = 0; i < n_inpt; i++){
            int j = i + counter;
            if(j > n_inpt){
                break;
            }
            for(int k = counter; k < 0; k--){
                std::vector<std::vector<int>> sol_e = matrixsol[i][k-1];
                std::vector<std::vector<int>> sol_d = matrixsol[k][j];
                for(const std::vector<int>& vec_e : sol_e ){
                    for(const std::vector<int>& vec_d : sol_d){
                        int sol = eq[vec_e[0]-1][vec_d[0]-1];
                        add_sol(sol, k, vec_e[0], vec_d[0], i, j);
 
                    }
                }
            }
        }
        counter++;
    }
    
    

    

    std::vector<std::vector<std::string>> parentheses(n_inpt, std::vector<std::string>(n_inpt, ""));
    for (int i = 0; i < n_inpt; ++i) {
        parentheses[i][i] = std::to_string(eq[i]);
    }

    for (int length = 2; length <= n_inpt; ++length) {
        for (int i = 0; i <= n_inpt - length; ++i) {
            int j = i + length - 1;
            int k = matrixsol[i][j][0][1];
            parentheses[i][j] = "(" + parentheses[i][k] + " x " + parentheses[k + 1][j] + ")";
        }
    }

}