/**
 * @file classic_enumerator.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-08-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "classic_enumerator.hpp"

using namespace std;
namespace wills::sudoku
{
    void classic_enumerator::attach(const std::shared_ptr<classic_board> &pboard)
    {
        this->board = pboard;
    }

    std::vector<sudoku_cell_t> classic_enumerator::enum_cell(const coordinate &coords)
    {
        std::vector<sudoku_cell_t> result;
        //Only enumerate UNKNOW cells
        if(board->get(coords) == 0){
            sudoku_cell_t _max_val = static_cast<sudoku_cell_t>(std::max(board->shape().cells_per_row(),board->shape().cells_per_col()));
            for(sudoku_cell_t i = 1; i<= _max_val; ++i)
                result.push_back(i);
        }
        else result.push_back(board->get(coords));
        return result;
    }
    std::vector<region_t> classic_enumerator::get_enumerable_region(){
        std::vector<region_t> result;
        return result;
    }
    std::vector<std::vector<std::pair<coordinate,sudoku_cell_t>>> classic_enumerator::enum_region(const region_t & reg){
        std::vector<std::vector<std::pair<coordinate,sudoku_cell_t>>> result;
        return result;
    }
    std::vector<sudoku_cell_t> classic_enumerator::enum_cell_except(const coordinate & coords,const std::vector<region_t>& regions)
    {
        std::vector<sudoku_cell_t> result;
        for(const auto & r:regions){
            // if(r.contains())
        }
        return result;
    }


} // namespace wills::sudoku
