test_main = static_library('test_main', sources: ['catch_main.cpp'], dependencies: [catch2])

parse_tree_test = executable(
	'parse_tree_test', 
	'parse_tree.cpp', 
	link_with: [test_main], 
	dependencies: [ratl, catch2]
)

test('Parse tree test', parse_tree_test)