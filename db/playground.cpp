//
// Created by zcy on 22-9-29.
// It's a playground to explore leveldb features.
//
#include "leveldb/db.h"
#include <string>

int main() {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "./dumping", &db);
  assert(status.ok());
  for(int i = 0; i < 10000000; i ++) {
    db->Put(leveldb::WriteOptions(), std::to_string(i), std::to_string(i));
  }
  delete db;
  return 0;
}