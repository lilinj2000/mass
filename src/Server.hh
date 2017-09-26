// Copyright (c) 2010
// All rights reserved.

#ifndef MASS_SERVER_HH
#define MASS_SERVER_HH

#include <string>
#include "Options.hh"
#include "cata/MDService.hh"
#include "cppdb/frontend.h"
#include "zod/PubService.hh"
#include "soil/json.hh"
#include "soil/Log.hh"

namespace mass {

class Server :
      public cata::MDCallback {
 public:
  explicit Server(
      const rapidjson::Document& doc);

  virtual ~Server();

  virtual void onRtnDepthMarketData(
      const std::string& theDepthMarketData);

 protected:
  void subInstrus();

 private:
  std::unique_ptr<Options> options_;
  std::unique_ptr<zod::PubService> pub_service_;
  std::unique_ptr<cppdb::session> db_;
  std::unique_ptr<cata::MDService> md_service_;
};

};  // namespace mass

#endif
