// Copyright (c) 2010
// All rights reserved.

#include "Server.hh"
#include "Log.hh"
#include "json/json.hh"

namespace mass {

Server::Server(int argc, char* argv[]) {
  MASS_TRACE <<"Server::Server()";

  config_.reset(new Config(argc, argv));

  db_.reset(new cppdb::session(config_->options()->connection_string));

  md_service_.reset(cata::MDService::createService(config_->cataMDOptions(), this));

  // cata::InstrumentSet instrus;
  // instrus.insert(instru);
  // md_service_->subMarketData(instrus);
}

Server::~Server() {
  MASS_TRACE <<"Server::~Server()";
}

void Server::onRspMessage(const std::string& msg) {
  MASS_TRACE <<"Server::onRspMessage()";

  MASS_INFO <<msg;
}

void Server::onRtnMessage(const std::string& msg) {
  MASS_TRACE <<"Server::onRtnMessage()";

  MASS_INFO <<msg;
  json::Document doc;
  json::fromString(msg, &doc);

}

};  // namespace mass
