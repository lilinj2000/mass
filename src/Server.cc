// Copyright (c) 2010
// All rights reserved.

#include "Server.hh"
#include "soil/Log.hh"
#include "boost/regex.hpp"

namespace mass {

Server::Server(
    const rapidjson::Document& doc) {
  SOIL_FUNC_TRACE;

  options_.reset(new Options(doc));

  pull_service_.reset(
      zod::PullService::create(
          options_->pull_addr,
          this));

  pub_service_.reset(
      zod::PubService::create(
          options_->pub_addr));

  md_service_.reset(
      cata::MDService::create(
          doc, this));
}

Server::~Server() {
  SOIL_FUNC_TRACE;
}

void Server::onRtnDepthMarketData(
    const std::string& theDepthMarketData) {
  SOIL_FUNC_TRACE;

  SOIL_DEBUG_PRINT(theDepthMarketData);
  pub_service_->sendMsg(theDepthMarketData);
}

void Server::msgCallback(
    std::shared_ptr<zod::Msg> msg) {
  SOIL_FUNC_TRACE;

  rapidjson::Document doc;
  if (doc.Parse(
          reinterpret_cast<const char*>(msg->data()),
          msg->len()).HasParseError()) {
    SOIL_DEBUG_PRINT(
        soil::json::get_parse_error(doc));
    return;
  }

  std::string instru;
  soil::json::get_item_value(&instru, doc, "/instru");

  char *c_instru =
      const_cast<char*>(instru.data());
  md_service_->subMarketData(&c_instru, 1);
}

};  // namespace mass
