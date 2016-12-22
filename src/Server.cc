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

  md_service_.reset(cata::MDService::createService(config_->cataMDOptions(), this));


  subInstrus();
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

  auto itr = doc.MemberBegin();
  std::string key = itr->name.GetString();
  json::Value& data = doc[key.data()];

  // OnRtnDepthMarketData
  if (key == "OnRtnDepthMarketData") {
    std::string t_name = "DepthMarketData";

    boost::regex re_field("^CThostFtdc(.*)Field$");
    for (auto itr = data.MemberBegin();
         itr != data.MemberEnd(); ++itr) {
      boost::smatch mat;
      std::string key = itr->name.GetString();
      if (boost::regex_match(key, mat, re_field)) {
        json::Value& f_data = data[key.data()];

        std::string create_sql;
        std::string insert_sql;
        sqlString(t_name, f_data, create_sql, insert_sql);
        MASS_DEBUG <<"create sql: " <<create_sql;
        MASS_DEBUG <<"insert sql: " <<insert_sql;

        try {
          (*db_) <<create_sql <<cppdb::exec;
          (*db_) <<insert_sql <<cppdb::exec;
        } catch (std::exception const &e) {
          MASS_ERROR <<e.what();
        }
      }
    }
  }

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

void Server::sqlString(const std::string& name,
                       json::Value& data,
                       std::string& create_sql,
                       std::string& insert_sql) {
  MASS_TRACE <<"Server::sqlString()";

  create_sql = "CREATE TABLE IF NOT EXISTS " + name + " (";

  insert_sql = "INSERT INTO " + name + " VALUES(";

  bool first = true;
  for (auto itr = data.MemberBegin();
       itr != data.MemberEnd(); ++itr) {
    if (!first) {
      create_sql += ", ";
      insert_sql += ", ";
    } else {
      first = false;
    }
    create_sql += itr->name.GetString();
    create_sql += " TEXT";

    insert_sql += "'";
    insert_sql += itr->value.GetString();
    insert_sql += "'";
  }
  create_sql += ");";
  insert_sql += ");";

  return;
}


};  // namespace mass
