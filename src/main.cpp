#include <iostream>
#include <memory>
#include "dlx.hpp"
#include "sudoku.hpp"
#include "sample_sudoku.hpp"
#include "classic_board.hpp"
#include "classic_solver.hpp"
using namespace std;
using namespace wills;
using namespace wills::sudoku;

int main(int argc, char const *argv[])
{
    // dlx::dancing_links<unsigned> dlx;
    auto p_board = std::make_shared<classic_board>();

    vector<wills::sudoku::cell_value_t> 
        v(sudoku1,sudoku1 + sizeof(sudoku1) /sizeof(unsigned));
    p_board->read(v);
    cout << *p_board;

    classic_solver solver;
    classic_board * p_answer = dynamic_cast<classic_board *>(solver.solve(p_board).get());
    if(p_answer != nullptr)
        cout << * p_answer;

    return 0;
}