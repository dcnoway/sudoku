/**
 * @file test_dlx_prot.cpp
 * @author Will Wu (willswu@outlook.com)
 * @brief A helpper unit test file to test protected member of dlx::dancing_links
 * @version 0.1
 * @date 2020-07-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "dlx.hpp"

using namespace wills;

// TEST_CASE( "dlx::dancing_links::cover()", "[dlx]" ) {
//     dlx::dancing_links<unsigned> dlx;
//     dlx.init_cols(10);

//     dlx::value_t<unsigned> values1[5]{{1,11},{3,33},{5,55},{7,77},{9,99}};
//     dlx::value_t<unsigned> values2[5]{{2,22},{4,44},{6,66},{8,88},{10,1010}};

//     dlx.append_row(values1,5);
//     dlx.append_row(values2,5);
//     REQUIRE(dlx.col_size() == 10);
//     REQUIRE(dlx.row_size() == 2);
//     REQUIRE(dlx.node_size() == 10);
//     dlx::cheader<unsigned> * ph = dlx.headers[0].get();
//     REQUIRE_NOTHROW(dlx.cover(ph));
//     REQUIRE(dlx.col_size() == 9);
//     REQUIRE(dlx.row_size() ==1 );
//     REQUIRE(dlx.node_size() == 5);

//     ph = dlx.headers[1].get();
//     REQUIRE_NOTHROW(dlx.cover(ph));
//     REQUIRE(dlx.col_size() == 8);
//     REQUIRE(dlx.row_size() == 0);
//     REQUIRE(dlx.node_size() == 0);

//     REQUIRE_NOTHROW(dlx.uncover(dlx.headers[1].get()));
//     REQUIRE(dlx.col_size() == 9);
//     REQUIRE(dlx.row_size() ==1 );
//     REQUIRE(dlx.node_size() == 5);

//     REQUIRE_NOTHROW(dlx.uncover(dlx.headers[0].get()));
//     REQUIRE(dlx.col_size() == 10);
//     REQUIRE(dlx.row_size() == 2);
//     REQUIRE(dlx.node_size() == 10);

// }