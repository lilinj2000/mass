// Copyright (c) 2010
// All rights reserved.

#include "Server.hh"
#include "Log.hh"
#include "boost/regex.hpp"

namespace mass {

Server::Server(int argc, char* argv[]) {
  MASS_TRACE <<"Server::Server()";

  config_.reset(new Config(argc, argv));

  db_.reset(new cppdb::session(config_->options()->connection_string));

  pub_service_.reset(zod::PubService::create(config_->options()->pub_addr));

  md_service_.reset(cata::MDService::createService(config_->cataMDOptions(), this));


  subInstrus();
}

Server::~Server() {
  MASS_TRACE <<"Server::~Server()";
}

void Server::onRspMessage(const std::string& msg) {
  MASS_TRACE <<"Server::onRspMessage()";

  MASS_DEBUG <<msg;
}

void Server::onRtnMessage(const std::string& msg) {
  MASS_TRACE <<"Server::onRtnMessage()";

  MASS_DEBUG <<msg;

  pub_service_->sendMsg(msg);
}

void Server::subInstrus() {
  MASS_TRACE <<"Server::subInstrus()";

  try {
    std::string sql = "SELECT DISTINCT InstrumentID FROM Instrument";
    if (!config_->options()->exchange_id.empty()) {
      sql += " WHERE ExchangeID = '"
          + config_->options()->exchange_id + "'";
    }
    MASS_DEBUG <<sql;

    cppdb::result res = (*db_) <<sql;

    cata::InstrumentSet instrus;
    while(res.next()) {
      std::string instru;
      res >> instru;
      instrus.insert(instru);
    }

    md_service_->subMarketData(instrus);
  } catch (std::exception const &e) {
    MASS_ERROR << "ERROR: " << e.what() << std::endl;
  }
}

};  // namespace mass
