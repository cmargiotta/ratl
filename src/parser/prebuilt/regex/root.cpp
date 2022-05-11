#include <parser/prebuilt/regex/alternation.hpp>
#include <parser/prebuilt/regex/root.hpp>
#include <parser/prebuilt/regex/round_par_open.hpp>

using ratl::regex::alternation;
using ratl::regex::root;
using ratl::regex::round_par_open;

void root::merge(std::unique_ptr<root>&& other)
{
    std::string           empty("");
    std::unique_ptr<root> this_ = std::make_unique<root>();
    std::unique_ptr<node> par1  = std::make_unique<round_par_open>(empty);
    std::unique_ptr<node> par2  = std::make_unique<round_par_open>(empty);
    std::unique_ptr<node> alt   = std::make_unique<alternation>(empty);

    while (!children.empty())
    {
        auto child = std::move(children.back());
        children.pop_back();

        this_->add_child(std::move(child));
    }

    par1->add_child(std::move(this_));
    par2->add_child(std::move(other));

    alt->add_child(std::move(par2));
    alt->add_child(std::move(par1));

    children.push_front(std::move(alt));
}