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
#include"dlx.hpp"
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

        /**
         * @brief dancing links row data generator
         * 
         * @param coords cell coords
         * @param cellval cell value
         * @return pair<size_t,cell_value_t> <col index of dancing links row, value attached>
         */
        // pair<size_t,cell_value_t> dlx_row_generator(const coordinate & coords, const cell_value_t cellval)const noexcept;

        /**
         * @brief parse the dancing links solve result to the classic board cell coordinates and value
         * 
         * @param result_row one row of dancing links solve result data
         * @return pair<coordinate,cell_value_t>  <coords of cell,value of cell>
         */
        // pair<coordinate,cell_value_t> dlx_row_parser(result_row_t<cell_value_t> result_row)const noexcept;
    };
}

#endif