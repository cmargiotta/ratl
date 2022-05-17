test_main = static_library('test_main', sources: ['catch_main.cpp'], dependencies: [catch2])

parse_tree_test = executable(
	'parse_tree_test', 
	'parse_tree.cpp', 
	link_with: [test_main], 
	dependencies: [ratl, catch2]
)

traits_test = executable(
	'traits_test', 
	'traits.cpp', 
	link_with: [test_main], 
	dependencies: [ratl, catch2]
)

utils_test = executable(
	'utils_test', 
	'utils.cpp', 
	link_with: [test_main], 
	dependencies: [ratl, catch2]
)

math_test = executable(
	'math_test', 
	'math.cpp', 
	link_with: [test_main], 
	dependencies: [ratl, catch2]
)

test('Parse tree test', parse_tree_test)
test('Type traits test', traits_test)
test('Utils test', utils_test)
test('Math test', math_test)