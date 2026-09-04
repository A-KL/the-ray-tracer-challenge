#include <vector>
#include <sstream>
#include <iostream>

#include "../lib/Core/Polygon3D.h"

#include "ObjLoader.h"

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// Trim from the end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// String split
std::vector<std::string> split(std::string s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

void obj_parse_line(std::string line, Polygon3D& result)
{
  ltrim(line);

  if (line.empty()) {
    return;
  }

  auto tokens = split(line, " ");

  if (tokens[0] == "v") 
  {
    // std::cout << "Vertex: " << tokens[1] << ", " << tokens[2] << ", " << tokens[3] << std::endl;
    result.AddVertex(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
  } 
  else if (tokens[0] == "f") 
  {
    std::vector<int> face_indexes;
    std::vector<int> normal_indexes;

    for (auto i=1; i<tokens.size(); i++) 
    {
      auto d = split(tokens[i], "/");

      if (d.size() == 3) {
        face_indexes.push_back(std::stoi(d[0]));
        normal_indexes.push_back(std::stoi(d[2]));
      }
      else 
      {
        face_indexes.push_back(std::stoi(tokens[i]));
      }        
    }
    result.AddFace(face_indexes, normal_indexes);
  }
  else if (tokens[0] == "g") 
  {
    result.AddGroup(tokens[1].c_str());
  }
  else if (tokens[0] == "vn") 
  {
    // std::cout << "Normal: " << tokens[1] << ", " << tokens[2] << ", " << tokens[3] << std::endl;
    result.AddNormal(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
  }
}

void obj_load_from_string(const char* data, Polygon3D& result)
{
  std::istringstream f(data);
  std::string line;

  while (std::getline(f, line)) {
    obj_parse_line(line, result);
  }
}