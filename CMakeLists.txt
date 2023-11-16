cmake_minimum_required(VERSION 3.5)
project(leetcode)

include_directories(include)

add_library(list lib/list.c)
add_library(bin_tree lib/bin_tree.c)
add_library(queue lib/queue.c)

link_libraries(list bin_tree queue)

# bin tree related
add_executable(104 tree/max_depth_104.c)
add_executable(199 tree/rightSideView_199.c)
add_executable(530 tree/getMiniDifference_530.c)
add_executable(101 tree/isSymmetric_101.c)
add_executable(105 tree/buildTree_105.c)
add_executable(106 tree/buildTree_106.c)
add_executable(117 tree/connect_117.c)
add_executable(114 tree/flatten_114.c)
add_executable(112 tree/hasPathSum_112.c)
add_executable(129 tree/sumNumbers_129.c)
add_executable(124 tree/_maxPathSum_124.c)
add_executable(173 tree/bSTIteratorFree_173.c)
add_executable(222 tree/countNodes_222.c)
add_executable(236 tree/_lowestCommonAncestor_236.c)

add_executable(228 summary_range_228.c)
add_executable(36 is_valid_sudoku_36.c)
add_executable(383 canConstruct_383.c)
add_executable(20 is_valid_20.c)
add_executable(141 hasCycle_141.c)

add_executable(130 solve_130.c)
add_executable(909 snake_ladder_909.c)
add_executable(445 addTwoNumbers_445.c)
add_executable(2 addTwoNumbers_2.c)
add_executable(matrix_test matrix_test.c)
