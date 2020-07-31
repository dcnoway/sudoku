#include "classic_board.hpp"
#include <optional>
#include <vector>
using namespace std;
namespace wills::sudoku
{
    inline size_t classic_board::coords2index(const axis_value_t col, const axis_value_t row) const noexcept
    {
        return (row - 1) * row_size + col - 1;
    }

    inline coordinate classic_board::index2coords(const size_t cell_idx) const noexcept
    {
        axis_value_t col = cell_idx % row_size;
        axis_value_t row = cell_idx / row_size;
        return coordinate{col + 1, row + 1};
    }

    inline coordinate classic_board::coords2region(const axis_value_t col, const axis_value_t row) const noexcept
    {
        axis_value_t rcol = (col - 1) / col_size + 1;
        axis_value_t rrow = (row - 1) / row_size + 1;
        return coordinate{rcol, rrow};
    }

    cell_value_t classic_board::get(const axis_value_t col, const axis_value_t row) const
    {
        if(check_coords(col,row))
            return cells[coords2index(col, row)];
        else return CELL_COORDS_ERROR;
    }

    cell_value_t classic_board::get(const coordinate &cords) const
    {
        return get(cords.col,cords.row);
    }

    void classic_board::set(const coordinate & cords,const cell_value_t val)
    {
        if(!check_coords(cords.col,cords.row))
            throw range_error("set value to a cell with a coordinate out of range");
        else
        {
            cells[coords2index(cords.col,cords.row)] = val;
        }
    }

    size_t classic_board::read(const std::vector<cell_value_t> &arr)
    {
        size_t region_col_len = 0;
        size_t region_row_len = 0;
        size_t result = 0;
        switch (arr.size())
        {
        case 3 * 3:
            col_size = row_size = 3;
            break;
        case 4 * 4:
            col_size = row_size = 4;
            region_col_len = region_row_len = 2;
            break;
        case 5 * 5:
            col_size = row_size = 5;
            break;
        case 6 * 6:
            col_size = row_size = 6;
            break;
        case 7 * 7:
            col_size = row_size = 7;
            break;
        case 8 * 8:
            col_size = row_size = 8;
            break;
        case 9 * 9:
            col_size = row_size = 9;
            region_col_len = region_row_len = 3;
            break;
        default:
            return 0;
            break;
        }
        cells = arr;
        return arr.size();
    }

    vector<std::shared_ptr<region_t>> classic_board::regions() const noexcept
    {
        vector<std::shared_ptr<region_t>> result;
        auto rects = rect_regions();
        for(rectangle_region rect: rects){
            result.push_back(make_shared<rectangle_region>(rect));
        }
        return result;
    }

    vector<rectangle_region> classic_board::rect_regions() const noexcept
    {
        vector<rectangle_region> result;
        
        return result;
    }

    std::shared_ptr<region_t> classic_board::region(const cell& pcell) const noexcept
    {
        auto result = std::make_shared<rectangle_region>();
        return result;
    }

    std::shared_ptr<region_t> classic_board::create_region() const noexcept 
    {
        auto result = std::make_shared<rectangle_region>();
        return result;
    }

    ostream &operator <<(ostream& os, const classic_board & v)
    {
        for(int i = 0; i< v.cells.size(); ++i){
            os << v.cells[i] ;
            if( i % v.col_size == v.col_size -1)
                os << endl;
            else os << ',';
        }
        return os;
    }

} // namespace wills::sudoku