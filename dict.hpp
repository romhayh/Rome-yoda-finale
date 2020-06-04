#pragma once
#include "button.hpp"
#include <map>

using Key = sf::Keyboard::Key;
using String = std::string;

namespace dict {
	std::map<Key, String> kts{ ///kets to strings
		{Key::A, "a"},
		{Key::B, "b"},
		{Key::C, "c"},
		{Key::D, "d"},
		{Key::E, "e"},
		{Key::F, "f"},
		{Key::G, "g"},
		{Key::H, "h"},
		{Key::I, "i"},
		{Key::J, "j"},
		{Key::K, "k"},
		{Key::L, "l"},
		{Key::M, "m"},
		{Key::N, "n"},
		{Key::O, "o"},
		{Key::P, "p"},
		{Key::Q, "q"},
		{Key::R, "r"},
		{Key::S, "s"},
		{Key::T, "t"},
		{Key::U, "u"},
		{Key::V, "v"},
		{Key::W, "w"},
		{Key::X, "x"},
		{Key::Y, "y"},
		{Key::Z, "z"},
		{Key::Num0, "0"},
		{Key::Num1, "1"},
		{Key::Num2, "2"},
		{Key::Num3, "3"},
		{Key::Num4, "4"},
		{Key::Num5, "5"},
		{Key::Num6, "6"},
		{Key::Num7, "7"},
		{Key::Num8, "8"},
		{Key::Num9, "9"},
		{Key::Left, "<-"},
		{Key::Right, "->"},
		{Key::Up, "up"},
		{Key::Down, "down"},



	};

	std::map<String, Key> stk{ ///strings to keys
		{"a", Key::A},
		{"b", Key::B},
		{"c", Key::C},
		{"d", Key::D},
		{"e", Key::E},
		{"f", Key::F},
		{"g", Key::G},
		{"h", Key::H},
		{"i", Key::I},
		{"j", Key::J},
		{"k", Key::K},
		{"l", Key::L},
		{"m", Key::M},
		{"n", Key::N},
		{"o", Key::O},
		{"p", Key::P},
		{"q", Key::Q},
		{"r", Key::R},
		{"s", Key::S},
		{"t", Key::T},
		{"u", Key::U},
		{"v", Key::V},
		{"w", Key::W},
		{"x", Key::X},
		{"y", Key::Y},
		{"z", Key::Z},
		{"0", Key::Num0},
		{"1", Key::Num1},
		{"2", Key::Num2},
		{"3", Key::Num3},
		{"4", Key::Num4},
		{"5", Key::Num5},
		{"6", Key::Num6},
		{"7", Key::Num7},
		{"8", Key::Num8},
		{"9", Key::Num9},
		{"<-", Key::Left},
		{"->", Key::Right},
		{"up", Key::Up},
		{"down", Key::Down}
	};

	Key toKey(const String& string) {
		return stk[string];
	}
	String toString(const Key& key) {
		return kts[key];
	}
}