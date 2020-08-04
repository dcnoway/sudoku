/**
 * @file enumerator.hpp
 * @author Will Wu (willswu@outlook.com)
 * @brief A enumerator for sudoku cells
 * @version 0.1
 * @date 2020-08-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __WILLS_SUDOKU_ENUMERATOR
#define __WILLS_SUDOKU_ENUMERATOR
#include "classic_board.hpp"
#include "sudokucommon.hpp"
namespace wills::sudoku
{
    /**
     * @brief An interface class for all enumerators
     * 
     * Using before constract dlx rows.
     * Note that this interface support both single cell enumeration and multiple cell enumeration though region
     */
    class enumerator
    {
        public:
        /**
         * @brief Attach a board info to this enumerator
         * 
         * @param pboard 
         */
        virtual void attach(const std::shared_ptr<classic_board> &pboard) = 0;

        /**
         * @brief Enum all possible values for the given cell
         * 
         * @param coords cell coords
         * @return std::vector<sudoku_cell_t> 
         */
        virtual std::vector<sudoku_cell_t> enum_cell(const wills::sudoku::coordinate & coords) = 0;

        /**
         * @brief Get the enumerable region object
         * 
         * Some variant sudokus have computetional rules between multiple cells. i.e the value of two cells must difference 1.
         * Because dancing links can merge multiple inconflict cols into one row and solve it well, we can enum all valid value pair with this interface.
         * Usage:
         *      auto pairs = enumerator->get_enumerable_region();
         *      for(const auto &pair:pairs){
         *          auto all_possible_values_for_pair = enumerator->enum_region(pair);
         *          auto dlx_row = rulemgr.generate_dlx_row(all_possible_values_for_pair);
         *          dlx.append_row(dlx_row);
         *      }
         *      auto cells = board->cells();
         *      for(const auto &cell:cells){
         *          auto cellval = enum_cell_except(cell,region);
         *          auto dlx_row = rulemgr.generate_dlx_row(cellval);
         *          dlx.append_row(dlx_row);
         *      }
         *      dlx.solve();
         * @return std::vector<region_t> 
         */
        virtual std::vector<region_t> get_enumerable_region() = 0;

        /**
         * @brief enumerate all possible value set for the given region
         * 
         * @param reg the region need to enum
         * @return std::vector<std::vector<std::pair<coordinate,sudoku_cell_t>>> vector<cell values vector for one region<coords,cell>>
         */
        virtual std::vector<std::vector<std::pair<coordinate,sudoku_cell_t>>> enum_region(const region_t & reg) = 0;

        /**
         * @brief Enum all possible values for the given cell if cell NOT in the regions
         * 
         * @param coords 
         * @param regions 
         * @return std::vector<sudoku_cell_t> 
         */
        virtual std::vector<sudoku_cell_t> enum_cell_except(const wills::sudoku::coordinate & coords,const std::vector<region_t>& regions) = 0;
    };

} // namespace wills::sudoku

#endif