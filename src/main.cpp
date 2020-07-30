#include <iostream>
#include "dlx.hpp"
#include "sudoku.hpp"
#include "sample_sudoku.hpp"
#include "classic_board.hpp"
using namespace std;
using namespace wills;
int main(int argc, char const *argv[])
{
    dlx::dancing_links<unsigned> dlx;
    cout << sizeof(int)<<','<<sizeof(short)<<endl;
    sudoku::classic_board board;

    return 0;
}