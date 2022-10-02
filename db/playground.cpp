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
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  assert(status.ok());
  db->Put(leveldb::WriteOptions(), "key", "1");
  std::string value;
  db->Get(leveldb::ReadOptions(), "key", &value);
  return 0;
}