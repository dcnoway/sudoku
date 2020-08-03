/**
 * @file rule.hpp
 * @author Will Wu (willswu@outlook.com)
 * @brief The base class of all rule
 * @version 0.1
 * @date 2020-08-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __WILLS_SUDOKU_RULE
#define __WILLS_SUDOKU_RULE
#include <vector>
#include <memory>
#include "sudokucommon.hpp"
#include "dlx.hpp"
#include "classic_board.hpp"
using namespace std;
using namespace wills;
using namespace wills::dlx;
namespace wills::sudoku
{
    /**
     * @brief Try Java style interface machinism
     * 
     */
    class rule
    {
        public:
        /**
         * @brief Get the human readable name for this rule
         * 
         * @return string rule name
         */
        virtual string getname() const = 0;
        /**
         * @brief attach this rule to the board,for other function
         * 
         * @param board the board will be attached to
         */
        virtual void attach(const std::shared_ptr<classic_board>& board) = 0;
        /**
         * @brief Parse the board, do some preparation
         * 
         * @return true the board is valid
         * @return false the board is invalid
         */
        virtual bool parse() = 0;
        /**
         * @brief the column amount of dancing links for this rule
         * 
         * @return size_t dancing links column amount
         */
        virtual size_t dlx_cols() const = 0;
        /**
         * @brief generate dlx(dancing links) input row data
         * 
         * @return std::vector<row_t<sudoku_cell_t>> row data for dlx
         */
        virtual std::vector<row_t<sudoku_cell_t>> generate_dlx_row() const = 0;
        /**
         * @brief parse dlx(dancing links) solve result data to answer
         * 
         * @param rslt dlx solve result data
         * @return std::vector<classic_board> 0 or more answer stored in board instance
         */
        virtual std::vector<classic_board> parse_dlx_result(const std::vector<row_t<sudoku_cell_t>> &rslt) const = 0;
        /**
         * @brief check a answer for the board
         * 
         * @param board answer stored in a board instance
         * @return true answer is valid
         * @return false answer is invalid
         */
        virtual bool check_answer(const std::shared_ptr<classic_board>& board) const = 0;
    };
} // namespace wills::sudoku
#endif