#!/usr/bin/env python

import json

sink1 = {
    "sink": {
        "type": "stdout_sink_mt",
        "level": "trace"
        }
    }

sink2 = {
    "sink": {
        "type": "rotating_file_sink_mt",
        "file_name": "logs/mass.log",
        "max_file_size": 5000000,
        "max_files": 10
        }
    }

log = {
    "level": "trace",
    "sinks": [sink1, sink2]
    }

cata_md = { 
    "flow_path": "mdflow/",

    # ctpfz
    # front_address = tcp://ctpfz1-front1.citicsf.com:51213
    # front_address = tcp://ctpfz1-front3.citicsf.com:51213
    # broker_id = 66666
    # user_id = 04452
    # password = 123456

    # simnow
    # front_address = tcp://180.168.146.187:10010"
    # front_address = tcp://180.168.146.187:10031" 7x24
    # user_id = 037135
    # password = y888888

    "front_address": "tcp://180.168.146.187:10010",
    "broker_id": "",
    "user_id": "",
    "password": "",

    # protocol: tcp, udp, or multi
    "protocol": "tcp"
    }

mass = {
    "dbconn_str": "sqlite3:db=qatar.db;@pool_size=16",
    "exchange_id": "CFFEX",
    "pub_addr": ">tcp://127.0.0.1:9990"
    }

cfg = {
    "mass": mass,
    "cata_md": cata_md,
    "log": log
    }

with open('mass.json', 'w') as f:
    json.dump(cfg, f, sort_keys=True, indent=4)
