// Copyright (c) 2010
// All rights reserved.

#ifndef MASS_MDSERVER_HH
#define MASS_MDSERVER_HH

#include <string>
#include "Config.hh"
#include "cata/MDService.hh"
#include "cppdb/frontend.h"
#include "json/json.hh"

namespace mass {

class Server : public cata::ServiceCallback {
 public:
  Server(int argc, char* argv[]);

  virtual ~Server();

  virtual void onRspMessage(const std::string& msg);

  virtual void onRtnMessage(const std::string& msg);

 protected:
  void subInstrus();

  void sqlString(const std::string& name,
                 json::Value& data,
                 std::string& create_sql,
                 std::string& insert_sql);


 private:
  std::unique_ptr<mass::Config> config_;

  std::unique_ptr<cata::MDService> md_service_;

  std::unique_ptr<cppdb::session> db_;
};

};  // namespace mass

#endif
