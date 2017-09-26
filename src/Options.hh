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

  std::string dbconn_str;
  std::string exchange_id;
  std::string pub_addr;
};

}  // namespace mass
#endif
