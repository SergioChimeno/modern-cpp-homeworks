// Copyright Igor Bogoslavskyi, year 2018.
// In case of any problems with the code please contact me.
// Email: igor.bogoslavskyi@uni-bonn.de.

#include "io_strategies/ppm_strategy.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream> 

namespace igg {

bool PpmIoStrategy::Write(const std::string& file_name,
                          const ImageData& data) const {
  std::ofstream out(file_name);
  if (!out) {
    return false;
  }

  out << "P3" << std::endl
      << data.rows << " " << data.cols << std::endl
      << static_cast<int>(data.max_val) << std::endl;

  for (int r = 0; r < data.rows; ++r) {
    for (int c = 0; c < data.cols; ++c) {
      out << static_cast<int>(data.data[0][r * data.cols + c]) << " ";
      out << static_cast<int>(data.data[1][r * data.cols + c]) << " ";
      out << static_cast<int>(data.data[2][r * data.cols + c]) << " ";
    }
    out << std::endl;
  }
  return true;
}

ImageData PpmIoStrategy::Read(const std::string& file_name) const {
  std::ifstream in(file_name, std::ios_base::in);
  if (!in) {
    return {0, 0, 0, {}};
  }

  // Read integers, if we read chars, we get 1 digit instead of the whole number
  std::string type;
  int rows = 0;
  int cols = 0;
  int max_val = 0;
  std::vector<std::vector<int>> data;
  in >> type; 

  bool read_rows = false, read_cols = false, read_max_val = false;
  
  while (!in.eof() && (!read_rows || !read_cols || !read_max_val))
  {
    std::string line; 
    std::getline(in, line);

    if(line[0] == '#') continue; // Skip comments
    std::stringstream ss(line);
    if(!read_rows && ss >> rows) read_rows = true;
    if(!read_cols && ss >> cols) read_cols = true;
    if(!read_max_val && ss >> max_val) read_max_val = true;
  }

  std::vector<int> red(rows * cols, 0);
  std::vector<int> green(rows * cols, 0);
  std::vector<int> blue(rows * cols, 0);

  if(type == "P2"){
    int byte = 0;
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        in >> byte;
        red[r * cols + c] = byte;
        green[r * cols + c] = byte;
        blue[r * cols + c] = byte;
      }
    }
  }else if(type == "P3"){
    int redPx = 0;
    int greenPx = 0;
    int bluePx = 0;
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        in >> redPx;
        in >> greenPx;
        in >> bluePx;
        red[r * cols + c] = redPx;
        green[r * cols + c] = greenPx;
        blue[r * cols + c] = bluePx;      }
    }
  }

  return {rows, cols, max_val, {red,green,blue}};
}

}  // namespace igg