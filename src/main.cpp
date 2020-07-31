#include <iostream>
#include "dlx.hpp"
#include "sudoku.hpp"
#include "sample_sudoku.hpp"
#include "classic_board.hpp"
using namespace std;
using namespace wills;
using namespace wills::sudoku;
int main(int argc, char const *argv[])
{
    dlx::dancing_links<unsigned> dlx;
    cout << sizeof(int)<<','<<sizeof(short)<<endl;
    classic_board board;
    vector<wills::sudoku::cell_value_t> 
        v(sudoku1,sudoku1 + sizeof(sudoku1) /sizeof(unsigned));
    board.read(v);
    cout << board;

    rectangle_region rect;
    coordinate zero{0,0};
    coordinate one{1,1};
    coordinate two{2,2};
    auto cell11 = make_shared<square_cell>(one);
    auto cell22 = make_shared<square_cell>(two); 
    return 0;
}