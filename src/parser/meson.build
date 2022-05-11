parser_lib = static_library(
	'parser',
	[
		'./prebuilt/regex/root.cpp'
	],
	include_directories: '../'
)

parser = declare_dependency(
	link_with: [parser_lib],
	include_directories: '../'
)