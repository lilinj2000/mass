// Copyright (c) 2010
// All rights reserved.

#include <fstream>
#include <iostream>
#include "boost/program_options.hpp"

#include "Config.hh"
#include "Log.hh"
#include "cata/MDService.hh"

namespace mass {

Options::Options():
    config_options_("MassConfigOptions") {
  namespace po = boost::program_options;

  config_options_.add_options()
      ("mass.connection_string", po::value<std::string>(&connection_string),
       "db connection string")
      ("mass.log_cfg", po::value<std::string>(&log_cfg),
       "log config file");

  return;
}

Options::~Options() {
}

po::options_description* Options::configOptions() {
  return &config_options_;
}

Config::Config(int argc, char* argv[]) {
  options_.reset(new Options());
  cata_md_options_.reset(cata::MDService::createOptions());

  std::unique_ptr<soil::Config> config(soil::Config::create());
  config->registerOptions(options_.get());
  config->registerOptions(cata_md_options_.get());

  config->configFile() = "mass.cfg";
  config->loadConfig(argc, argv);

  // init the log
  MASS_LOG_INIT(options_->log_cfg);

  return;
}

Config::~Config() {
}

};  // namespace mass
