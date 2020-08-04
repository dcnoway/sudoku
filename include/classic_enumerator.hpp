/**
 * @file classic_enumerator.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-08-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __WILLS_SUDOKU_CLASSIC_ENUMERATOR
#define __WILLS_SUDOKU_CLASSIC_ENUMERATOR
#include "enumerator.hpp"
#include "classic_board.hpp"
namespace wills::sudoku
{
    class classic_enumerator: public enumerator
    {
        protected:
        std::shared_ptr<classic_board> board;
        public:
        classic_enumerator()=default;
        ~classic_enumerator()= default;
        void attach(const std::shared_ptr<classic_board> &pboard) override;
        std::vector<sudoku_cell_t> enum_cell(const coordinate & coords) override;
        std::vector<region_t> get_enumerable_region() override;
        std::vector<std::vector<std::pair<coordinate,sudoku_cell_t>>> enum_region(const region_t & reg)override;
        std::vector<sudoku_cell_t> enum_cell_except(const coordinate & coords,const std::vector<region_t>& regions)override;
    };
} // namespace wills::sudoku

#endif