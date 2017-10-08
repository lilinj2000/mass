// Copyright (c) 2010
// All rights reserved.

#include "Options.hh"

namespace mass {

using soil::json::get_item_value;

Options::Options(
    const rapidjson::Document& doc) {
  get_item_value(&pub_addr, doc, "/mass/pub_addr");
  get_item_value(&pub_addr, doc, "/mass/pull_addr");
}

};  // namespace mass
