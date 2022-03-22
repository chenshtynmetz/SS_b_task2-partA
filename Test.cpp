/**
 * AUTHORS: <chen>
 * 
 * Date: 03/2022
 */

#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}

// tests with good cases.
TEST_CASE("read, write and erase functions") {
    ariel::Notebook my_notebook;
    my_notebook.write(2,5,3, Direction::Vertical, "hello world");
	CHECK(nospaces(my_notebook.read(2,5,3, Direction::Horizontal, 11)) == nospaces("hello world"));
    CHECK(nospaces(my_notebook.read(2,5,3, Direction::Vertical, 2)) == nospaces("h_"));
    CHECK(nospaces(my_notebook.read(2,5,2, Direction::Horizontal, 11)) == nospaces("_hello worl"));
    CHECK(nospaces(my_notebook.read(2,5,9, Direction::Horizontal, 1)) == nospaces("w"));
    CHECK(nospaces(my_notebook.read(2,4,3, Direction::Horizontal, 5)) == nospaces("_____"));
    CHECK(nospaces(my_notebook.read(2,3,3, Direction::Vertical, 5)) == nospaces("__h__"));
    CHECK(nospaces(my_notebook.read(2,5,5, Direction::Horizontal, 11)) == nospaces("llo world__"));
    CHECK(nospaces(my_notebook.read(2,5,5, Direction::Horizontal, 3)) == nospaces("llo"));
    CHECK(nospaces(my_notebook.read(3,5,3, Direction::Horizontal, 11)) == nospaces("___________"));
    my_notebook.erase(3,5,3,Direction::Horizontal, 4);
    CHECK(nospaces(my_notebook.read(3,5,3, Direction::Horizontal, 4)) == nospaces("~~~~"));
    my_notebook.erase(2,5,3,Direction::Horizontal, 1);
    CHECK(nospaces(my_notebook.read(2,5,3, Direction::Horizontal, 11)) == nospaces("~ello world"));
    my_notebook.erase(2,5,8, Direction::Horizontal, 2);
    CHECK(nospaces(my_notebook.read(2,5,3, Direction::Horizontal, 11)) == nospaces("~ello w~~ld"));
}

// tests with bad cases.
TEST_CASE("Bad input, write function") { 
    ariel::Notebook my_notebook;
    CHECK_THROWS(my_notebook.write(2,3,-6, Direction::Horizontal, "good morning")); //forbidden negative input
    CHECK_THROWS(my_notebook.write(-2,3,-6, Direction::Horizontal, "good morning"));
    CHECK_THROWS(my_notebook.write(5,3,358, Direction::Horizontal, "good morning"));
    CHECK_THROWS(my_notebook.write(5,3,358, Direction::Horizontal, "good morning")); //maximum of the cokmuns is 100
    CHECK_THROWS(my_notebook.write(5,-13,45, Direction::Horizontal, "good morning"));
    CHECK_THROWS(my_notebook.write(-5,-3,3, Direction::Horizontal, "good morning"));
}

TEST_CASE("Bad input, read function") {
    ariel::Notebook my_notebook;
    CHECK_THROWS(my_notebook.read(5,3,358, Direction::Horizontal, 5)); //maximum of the cokmuns is 100
    CHECK_THROWS(my_notebook.read(-15,23,2, Direction::Horizontal, 5)); //forbidden negative input
    CHECK_THROWS(my_notebook.read(5,3,38, Direction::Horizontal, -15));
    CHECK_THROWS(my_notebook.read(5,-3,358, Direction::Vertical, 5));
    CHECK_THROWS(my_notebook.read(-15,23,2, Direction::Horizontal, -5));
    CHECK_THROWS(my_notebook.read(5,3,-38, Direction::Vertical, -15));
}


TEST_CASE("Bad input, erase function") {
    ariel::Notebook my_notebook;
    CHECK_THROWS(my_notebook.erase(5,3,358, Direction::Horizontal, -5)); //forbidden negative input
    CHECK_THROWS(my_notebook.erase(5,-3,358, Direction::Horizontal, 25)); //maximum of the cokmuns is 100
    CHECK_THROWS(my_notebook.erase(5,3,23, Direction::Vertical, -5));
    CHECK_THROWS(my_notebook.erase(5,-3,358, Direction::Horizontal, 25));
    CHECK_THROWS(my_notebook.erase(-205,3,8, Direction::Horizontal, -5));
    CHECK_THROWS(my_notebook.erase(5,-3,8, Direction::Vertical, -25));
}