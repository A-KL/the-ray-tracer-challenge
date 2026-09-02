#pragma once

void obj_parse_line(std::string line, Polygon3D& result);

void obj_load_from_string(const char* data, Polygon3D& result);