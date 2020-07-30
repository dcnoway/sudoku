#ifndef __WILLS_SUDOKU_BOARD
#define __WILLS_SUDOKU_BOARD
#include <vector>
#include <memory>
/**
 * @file board.hpp
 * @author Will Wu (willswu@outlook.com)
 * @brief sudoku board representation base class header file
 * @version 0.1
 * @date 2020-07-30
 * 
 * @copyright MIT License
 * 
 */

namespace wills::sudoku{
    /**
     * @brief the type of cell value
     * 
     * classic sudoku cell is just 1-digital, from 1 to 9.
     * Because int type is the fastest data type on the CPU and system bus,
     * and there is no obvious memory pressre for just board representing,
     * further more, we reserve 0(ZERO) as the blank cell,
     * reserve negative value for future use,
     * hereby int was choosed as the type of cell value.
     */
    using cell_value_t = int;

    /**
     * @brief the type of cell coordinate factor, ZERO is reserved for internal use
     * 
     */
    using axis_value_t = unsigned;

    /**
     * @brief coordinate of sudoku board cells
     * 
     */
    struct coordinate
    {
        axis_value_t col =0; //!< column 
        axis_value_t row =0; //!< row
    };

    /**
     * @brief interface region
     * 
     */
    class region_t
    {
        public:
        virtual bool contains(const coordinate & cell) const noexcept = 0;
        virtual std::vector<coordinate> cells() const noexcept= 0;
    };
    

    /**
     * @brief sudoku board representation base class
     * 
     */
    class board
    {
    private:
        /* data */
    public:
        board(){}
        ~board(){}
        virtual std::vector<region_t> regions() const noexcept = 0;
        // {
        //     return std::vector<region_t>();
        // }
        virtual std::shared_ptr<region_t> region(const coordinate & cords) const noexcept = 0;
        // {
        //     return std::nullopt;
        // }
    };
    
}
#endif