#ifndef PARSE_TREE_PARSE_NODE_HPP
#define PARSE_TREE_PARSE_NODE_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace ratl
{
	template<typename ResultType_ = int, typename IdentifierType_ = std::string>
	class parse_node
	{
		public:
			using ResultType	 = ResultType_;
			using IdentifierType = IdentifierType_;

			enum class type : char
			{
				LEAF,
				DELIMITER_START,
				DELIMITER_END,
				OPERATOR
			};

		protected:
			virtual ResultType compute_(const std::vector<ResultType>& results) = 0;

		private:
			std::vector<std::unique_ptr<parse_node<ResultType, IdentifierType>>> children;
			std::vector<ResultType>												 results;

			const IdentifierType identifier;
			const size_t		 priority;
			const size_t		 operands;
			const type			 type_;

		public:
			parse_node(IdentifierType id_, size_t priority_, size_t operands_, type t)
				: identifier(id_), priority(priority_), operands(operands_), type_(t)
			{
			}

			virtual ~parse_node() = default;

			ResultType& compute()
			{
				results.clear();
				results.reserve(children.size());

				std::transform(children.begin(),
							   children.end(),
							   std::back_inserter(results),
							   [](std::unique_ptr<parse_node<ResultType>>& child) -> ResultType
							   { return child->compute(); });

				return compute_(results);
			}

			inline IdentifierType get_identifier() const
			{
				return identifier;
			}

			inline size_t get_priority() const
			{
				return priority;
			}

			inline size_t get_operands() const
			{
				return operands;
			}

			inline type get_type() const
			{
				return type_;
			}

			inline void add_child(std::unique_ptr<parse_node<ResultType, IdentifierType>> child)
			{
				children.emplace_back(std::move(child));
			}
	};
}// namespace ratl

#endif// PARSE_TREE_PARSE_NODE_HPP
