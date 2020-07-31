/**
 * @file classic_solver.hpp
 * @author Will Wu (willswu@outlook.com)
 * @brief classic sudoku solver(dancing link matrix builder and result parser)
 * @version 0.1
 * @date 2020-07-31
 * 
 * @copyright MIT License
 * 
 */

#ifndef __WILLS_SUDOKU_CLASSIC_SOLVER
#define __WILLS_SUDOKU_CLASSIC_SOLVER
#include<string>
#include<memory>
#include "solver.hpp"

using namespace std;
namespace wills::sudoku
{
    /**
     * @brief classic sudoku solver
     * 
     */
    class classic_solver:public solver
    {
        public:
        /**
         * @brief Get the name object
         * 
         * @return string 
         */
        string get_name() const noexcept override{
            return "classic";
        }

        /**
         * @brief sove sudoku
         * 
         * @param board An unsolved sudoku board
         * @return shared_ptr<board> solved sudoku board
         */
        shared_ptr<board> solve(shared_ptr<board> board)const override;
    };
}

#endif