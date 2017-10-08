// Copyright (c) 2010
// All rights reserved.

#ifndef MASS_OPTIONS_HH
#define MASS_OPTIONS_HH

#include <string>
#include <memory>
#include "soil/json.hh"

namespace mass {

class Options {
 public:
  explicit Options(
      const rapidjson::Document& doc);

  std::string pub_addr;
  std::string pull_addr;
};

}  // namespace mass
#endif
