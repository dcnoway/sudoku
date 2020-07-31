/**
 * @file base_sudoku.hpp
 * @author Will Wu (willswu@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-30
 * 
 * @copyright MIT License
 * 
 */
#ifndef __WILLS_SUDOKU_SUDOKU
#define __WILLS_SUDOKU_SUDOKU
#include <list>
#include <vector>
#include <memory>
#include "solver.hpp"
namespace wills::sudoku
{
    class parser
    {

    };


    /**
     * @brief facade class of all 
     * 
     */
    class sudoku
    {
        public:
        /**
         * @brief Get the solver object
         * 
         * @return solver 
         */
        virtual solver get_solver() = 0;
        /**
         * @brief Get the parser object
         * 
         * @return parser 
         */
        virtual parser get_parser() = 0;
    };

} // namespace wills

#endif