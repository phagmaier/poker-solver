#include "make_dics.h"

std::vector<unsigned int> parse_line_combo(std::string &str){
  std::string str1 = "";
  std::vector<unsigned int> result;
  for (char c : str){
    if (c == ' '){
      result.push_back(std::stoul(str1));
      str1 = "";
    } 
    else{
      str1 += c;
    }
  }
  result.push_back(std::stoul(str1));
  if (result.size() != 5){
    std::cout << "Inccorectly parsing combos\n";
  }
  return result;
}


std::pair<unsigned int, unsigned int> parse_line(std::string &str){
  std::string str1 = "";
  std::pair<unsigned int, unsigned int> result;
  for (char c : str){
    if (c == ' '){
      result.first = std::stoul(str1);
      str1 = "";
    } 
    else{
      str1 += c;
    }
  }
  result.second = std::stoul(str1);
  return result;
}

std::unordered_map<unsigned int, unsigned int>make_pairs(){
  std::unordered_map<unsigned int, unsigned int> dic;
  std::ifstream file("../data/all_pairs.txt");
  std::string str;
  unsigned int key;
  unsigned int val;
  while (getline(file, str)){
    std::tie(key,val) = parse_line(str); 
    dic[key] = val;
  }
  return dic;
}

std::unordered_map<unsigned int, unsigned int>make_straights(){
  std::unordered_map<unsigned int, unsigned int> dic;
  std::ifstream file("../data/straights.txt");
  std::string str;
  unsigned int key;
  unsigned int val;
  while (getline(file, str)){
    std::tie(key,val) = parse_line(str); 
    dic[key] = val;
  }
  return dic;
}

std::unordered_map<unsigned int, unsigned int>make_flushes(){
  std::unordered_map<unsigned int, unsigned int> dic;
  std::ifstream file("../data/flushes.txt");
  std::string str;
  unsigned int key;
  unsigned int val;
  while (getline(file, str)){
    std::tie(key,val) = parse_line(str); 
    dic[key] = val;
  }
  return dic;
}

std::vector<std::vector<unsigned int>> make_combos(){
  std::vector<std::vector<unsigned int>> vecs;
  std::ifstream file("../data/combos.txt");
  std::string str;
  unsigned int key;
  unsigned int val;
  while (getline(file, str)){
    vecs.push_back(parse_line_combo(str)); 
  }
  return vecs;
}

