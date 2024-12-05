#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>
#include <unordered_map>

std::tuple<int, int, int, int>& get_sol(int lin, int col, int result, std::vector<std::vector<std::vector<std::tuple<int, int, int, int>>>>& matrixsol, int lad_matx) {
    for (int i = 0; i < lad_matx; i++) {
        if (std::get<0>(matrixsol[lin][col][i]) == result) {
            return matrixsol[lin][col][i];
        }
    }
    static std::tuple<int, int, int, int> not_found = std::make_tuple(0, 0, 0, 0);
    return not_found;
}

std::vector<int> get_parents(int i, int j, int result, std::vector<std::vector<std::vector<std::tuple<int, int, int, int>>>>& matrixsol, int lad_max, std::vector<int>& vec) {
    if (j - i == 0) return vec;
    if (j - i == 1) {
        vec[2 * i]++;
        vec[(2 * j) + 1]++;
        return vec;
    }
    std::tuple<int, int, int, int> solution = get_sol(i, j, result, matrixsol, lad_max);
    int k = std::get<1>(solution);
    vec[2 * i]++;
    vec[(2 * j) + 1]++;
    vec = get_parents(i, i + k - 1, std::get<2>(solution), matrixsol, lad_max, vec);
    vec = get_parents(i + k, j, std::get<3>(solution), matrixsol, lad_max, vec);
    return vec;
}

int add_sol(int sol, int k, int sol_e, int sol_d, int lin, int col, std::vector<std::vector<std::vector<std::tuple<int, int, int, int>>>>& matrixsol, int lad_matx) {
    for (int i = 0; i < lad_matx; i++) {
        if (std::get<0>(matrixsol[lin][col][i]) == 0) {
            matrixsol[lin][col][i] = std::make_tuple(sol, k, sol_e, sol_d);
            return 1;
        }
        if (std::get<0>(matrixsol[lin][col][i]) == sol) {
            return 0;
        }
    }
    return -1;
}

std::string formatvec(const std::vector<int>& vec, const std::vector<int>& eq, int n_inpt) {
    std::string result;

    for (int i = 0; i < n_inpt; i++) {
        for (int j = 0; j < vec[i * 2]; j++) {
            result += "(";
        }
        result += std::to_string(eq[i]);

        for (int j = 0; j < vec[i * 2 + 1]; j++) {
            result += ")";
        }
        if (i != n_inpt - 1)
            result += " ";
    }
    return result;
}

int main() {
    std::ios::sync_with_stdio(0); // disable sync with c libs
    std::cin.tie(0); // discard cin buffer after each line of input

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

    if (n_inpt == 1) {
        if (eq[0] == n_resul) {
            std::cout << 1 << std::endl;
            std::cout << eq[0] << std::endl;
            return 0;
        } else {
            std::cout << 0 << std::endl;
            return 0;
        }
    }

    std::vector<std::vector<std::vector<std::tuple<int, int, int, int>>>> matrixsol(
        n_inpt,
        std::vector<std::vector<std::tuple<int, int, int, int>>>(
            n_inpt,
            std::vector<std::tuple<int, int, int, int>>(
                lad_matx,
                std::make_tuple(0, 0, 0, 0)
            )
        )
    );

    for (int i = 0; i < n_inpt; ++i) {
        matrixsol[i][i][0] = std::make_tuple(eq[i], 0, 0, 0);
    }

    for (int i = 0; i < n_inpt; i++) {
        int j = i + 1;
        if (j >= n_inpt) {
            break;
        }
        int sol_esq = eq[i] - 1;
        int sol_dir = eq[j] - 1;
        int sol = matrixeq[sol_esq][sol_dir];
        matrixsol[i][j][0] = std::make_tuple(sol, 1, sol_esq, sol_dir);
    }

    int counter = 2;
    while (counter <= n_inpt) {
        for (int i = 0; i < n_inpt - counter; i++) {
            int j = i + counter;
            int num_sols = 0;
            for (int k = counter; k > 0; k--) {
                std::vector<std::tuple<int, int, int, int>>& sol_e = matrixsol[i][i + k - 1];
                std::vector<std::tuple<int, int, int, int>>& sol_d = matrixsol[i + k][j];
                for (std::tuple<int, int, int, int>& vec_e : sol_e) {
                    if (std::get<0>(vec_e) == 0) {
                        break;
                    }
                    if(num_sols >= lad_matx) break;
                    for (std::tuple<int, int, int, int>& vec_d : sol_d) {
                        if (std::get<0>(vec_d) == 0) {
                            break;
                        }
                        int sol = matrixeq[std::get<0>(vec_e) - 1][std::get<0>(vec_d) - 1];
                        //printf("[%d %d] -> %d = %do%d, k = %d\n", i, j, sol, std::get<0>(vec_e), std::get<0>(vec_d), k);
                        num_sols += add_sol(sol, k, std::get<0>(vec_e), std::get<0>(vec_d), i, j, matrixsol, lad_matx);
                        if(num_sols >= lad_matx) break;
                    }
                }
            }
        }
        counter++;
    }


    int flag = 0;
    for(int i = 0; i < lad_matx; i++) {
        if(std::get<0>(matrixsol[0][n_inpt - 1][i]) == n_resul) {
            flag = 1;
            break;
        }
        
    }
    if(!flag) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::vector<int> vec(2 * n_inpt, 0);

    int i = 0;
    int j = n_inpt - 1;
    vec = get_parents(i, j, n_resul, matrixsol, lad_matx, vec);


    

    std::string result = formatvec(vec, eq, n_inpt);
    std::cout << 1 << std::endl;
    std::cout << result << std::endl;

    return 0;
}