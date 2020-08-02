#include "classic_board.hpp"
#include <optional>
#include <vector>
using namespace std;
namespace wills::sudoku
{

    inline coordinate classic_board::coords2region(const axis_value_t col, const axis_value_t row) const noexcept
    {
        for(const auto & reg:_regions){
            if(reg->contains(square_cell(coordinate{col,row}))){
                //TODO: need impl
                return coordinate{0,0};        
            }
        }
        return coordinate{0,0};
    }

    cell_value_t classic_board::get(const axis_value_t col, const axis_value_t row) const
    {
        if(_shape.check_coords(col,row))
            return _cells[_shape.coords2index(col, row)];
        else return CELL_COORDS_ERROR;
    }

    cell_value_t classic_board::get(const coordinate &cords) const
    {
        return get(cords.col,cords.row);
    }

    void classic_board::set(const coordinate & cords,const cell_value_t val)
    {
        if(!_shape.check_coords(cords.col,cords.row))
            throw range_error("set value to a cell with a coordinate out of range");
        else
        {
            _cells[_shape.coords2index(cords.col,cords.row)] = val;
        }
    }

    size_t classic_board::read(const std::vector<cell_value_t> &arr)
    {
        axis_value_t region_col_len = 0;
        axis_value_t region_row_len = 0;
        axis_value_t col_size = 0, row_size = 0;
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
        _cells = arr;

        /// Begin process rectangle regions
        _shape.set({1,1},{col_size,row_size});
        size_t region_col_cnt = col_size / region_col_len;
        size_t region_row_cnt = row_size / region_row_len;

        for(size_t rx = 1; rx <= region_col_cnt;++rx)
            for(size_t ry = 1; ry <= region_row_cnt;++ry){
                coordinate lt,rd;
                lt.col = (rx -1)*region_col_len + 1;
                lt.row = (ry -1)*region_row_len + 1;
                rd.col = lt.col + region_col_len - 1;
                rd.row = lt.row + region_row_len - 1;
                _regions.emplace_back(make_shared<rectangle_region>(lt,rd));
            }
        /// End
        return arr.size();
    }

    vector<std::shared_ptr<region_t>> classic_board::regions() const noexcept
    {
        vector<std::shared_ptr<region_t>> result;
        for(auto rect: _regions){
            result.push_back(rect);
        }
        return result;
    }

    vector<std::shared_ptr<rectangle_region>> classic_board::rect_regions() const noexcept
    {
        return _regions;
    }

    std::shared_ptr<region_t> classic_board::region(const shared_ptr<cell> & pcell) const noexcept
    {
        square_cell * psc = dynamic_cast<square_cell *>(pcell.get());
        return region( * psc);
    }

    shared_ptr<rectangle_region> classic_board::region(const square_cell &cell) const noexcept
    {
        for(auto & reg : _regions){
            if(reg->contains(cell))return reg;
        }
        return nullptr;
    }


    std::shared_ptr<region_t> classic_board::create_subregion() const noexcept 
    {
        std::cerr << "Not implemented yet!" << std::endl;
        auto result = std::make_shared<rectangle_region>();
        return result;
    }

    std::vector<std::shared_ptr<cell>> classic_board::cells() const noexcept
    {
        cerr << "Not implemented yet" <<endl;
        return vector<shared_ptr<cell>>();
    }

    const std::shared_ptr<region_t> classic_board::get_shape() const noexcept
    {
        return make_shared<rectangle_region>(_shape);
    }

    rectangle_region classic_board::shape() const noexcept
    {
        return _shape;
    }

    ostream &operator<<(ostream &os, const classic_board &v)
    {
        for(int i = 0; i< v._cells.size(); ++i){
            os << v._cells[i] ;
            if( (i % v.shape().cells_per_row()) 
                == (v.shape().cells_per_row() -1))
                os << endl;
            else os << ',';
        }
        return os;
    }

} // namespace wills::sudoku