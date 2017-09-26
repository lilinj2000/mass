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

  pub_service_.reset(
      zod::PubService::create(
          options_->pub_addr));

  db_.reset(new cppdb::session(
      options_->dbconn_str));

  md_service_.reset(
      cata::MDService::create(
          doc, this));

  subInstrus();
}

Server::~Server() {
  SOIL_FUNC_TRACE;
}


void Server::onRtnDepthMarketData(
    const std::string& theDepthMarketData) {
  SOIL_FUNC_TRACE;

  pub_service_->sendMsg(theDepthMarketData);
}

void Server::subInstrus() {
  SOIL_FUNC_TRACE;

  try {
    std::string sql = "SELECT DISTINCT InstrumentID FROM Instrument";
    if (!options_->exchange_id.empty()) {
      sql = fmt::format("SELECT DISTINCT InstrumentID "
                        "FROM Instrument "
                        "WHERE ExchangeID = '{}'",
                        options_->exchange_id);
    }
    SOIL_DEBUG_PRINT(sql);

    cppdb::result res = (*db_) <<sql;

    while (res.next()) {
      std::string instru;
      res >> instru;

      SOIL_DEBUG_PRINT(instru);
      char *c_instru =
          const_cast<char*>(instru.data());
      md_service_->subMarketData(&c_instru, 1);
    }
  } catch (std::exception const &e) {
    SOIL_ERROR("ERROR: {}", e.what());
  }
}

};  // namespace mass
