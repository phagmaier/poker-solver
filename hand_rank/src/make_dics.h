#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <string>
#include <vector>

std::vector<unsigned int> parse_line_combo(std::string &str);
std::pair<unsigned int, unsigned int> parse_line(std::string &str);
std::unordered_map<unsigned int, unsigned int>make_pairs();
std::unordered_map<unsigned int, unsigned int>make_straights();
std::vector<std::vector<unsigned int>> make_combos();
std::unordered_map<unsigned int, unsigned int>make_flushes();
