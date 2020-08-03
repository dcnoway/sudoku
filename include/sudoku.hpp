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
#include "rule.hpp"
#include "sudokucommon.hpp"
namespace wills::sudoku
{


    /**
     * @brief facade class of all 
     * 
     */
    class sudoku
    {
        private:
        std::shared_ptr<classic_board> board;
        std::vector<std::shared_ptr<rule>> rules;
        public:
        bool load_cells(std::vector<sudoku_cell_t> cell_array);
        void add_rule(std::shared_ptr<rule> rule);
        std::vector<classic_board> solve();
    };

} // namespace wills

#endif