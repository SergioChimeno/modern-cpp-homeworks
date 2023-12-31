// Copyright Igor Bogoslavskyi, year 2018.
// In case of any problems with the code please contact me.
// Email: igor.bogoslavskyi@uni-bonn.de.

#pragma once

#include <string>

#include <png++/png.hpp>

#include "io_strategies/strategy.h"

namespace igg {

class PpmIoStrategy : public IoStrategy {
 public:
  bool Write(const std::string& file_name,
             const ImageData& data) const override;
  ImageData Read(const std::string& file_name) const override;
};

}  // namespace igg
