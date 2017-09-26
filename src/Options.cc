// Copyright (c) 2010
// All rights reserved.

#include "Options.hh"

namespace mass {

using soil::json::get_item_value;

Options::Options(
    const rapidjson::Document& doc) {

  get_item_value(&dbconn_str, doc, "/mass/dbconn_str");
  get_item_value(&exchange_id, doc, "/mass/exchange_id", false);
  get_item_value(&pub_addr, doc, "/mass/pub_addr");
}

};  // namespace mass
