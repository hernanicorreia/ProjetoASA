#include <iostream>
#include <vector>
#include <sstream>






std::vector<int> get_sol(int lin, int col, int result, std::vector<std::vector<std::vector<std::vector<int>>>> matrixsol, int lad_matx){
        for(int i = 0; i < lad_matx; i++){
            if(matrixsol[lin][col][i][0] == result){
                return matrixsol[lin][col][i];
            }
        }
        return {-1, -1, -1, -1};
    }


std::vector<int> get_parents(int i, int j, int result, std::vector<std::vector<std::vector<std::vector<int>>>> matrixsol, int lad_max, std::vector<int> vec){
    if (j-1 == 0) return vec;
    if (j-1 == 1){
        vec[2*i]++;
        vec[2*i+1]++;
        return vec;
    }
    std::vector<int>solution = get_sol(i, j, result, matrixsol, lad_max);
    int k = solution[1];
    vec[2*i]++;
    vec[2*i+1]++;
    get_parents(i, k-1, solution[2], matrixsol, lad_max, vec);
    get_parents(k, j, solution[3], matrixsol, lad_max, vec);
    return vec;
}
    
    



int add_sol(int sol, int k, int sol_e, int sol_d, int col, int lin, std::vector<std::vector<std::vector<std::vector<int>>>> matrixsol, int lad_matx){
        for(int i = 0; i < lad_matx; i++){
            if(matrixsol[lin][col][i][0]==0){
                matrixsol[lin][col][i][0] = sol;
                matrixsol[lin][col][i][1] = k;
                matrixsol[lin][col][i][2] = sol_e;
                matrixsol[lin][col][i][3] = sol_d;
                return 1;
            }
            if(matrixsol[lin][col][i][0] == sol)
                return 0;
        }
        return -1;
    }


std::string formatvec(std::vector<int> vec, std::vector<int> eq){
    std::string result;
    int size = vec.size();
    for(int i = 0; i < size; i++){
        for(int j = 0; j < vec[i*2]; j++){
            result += eq[i] + "(";
        }
        result += eq[i];
        
        for(int j = 0; j < vec[i*2+1]; j++){
            result += ")";
        }
        result += " + ";
    }
    return result;
}



int main() {
    int lad_matx, n_inpt, n_resul;
    std::string line;
    std::getline(std::cin, line);
    std::sscanf(line.c_str(), "%d %d", &lad_matx, &n_inpt);
    

    std::vector<std::vector<int>> matrixeq(lad_matx, std::vector<int>(lad_matx, 0));

    




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
                        int sol = matrixeq[vec_e[0]-1][vec_d[0]-1];
                        add_sol(sol, k, vec_e[0], vec_d[0], i, j, matrixsol, lad_matx);
 
                    }
                }
            }
        }
        counter++;
    }

    
    std::vector<int> vec(2 * n_inpt, 0);    

    int i = 0;
    int j = n_inpt-1;
    vec = get_parents(i, j, n_resul, matrixsol, lad_matx, vec);

    std::string result = formatvec(vec, eq);
    std::cout << result << std::endl;
    

}