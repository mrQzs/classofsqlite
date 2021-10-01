//
// Created by qzs on 2021/9/30.
//

#include "SqliteOperator.h"

SqliteOperator *SqliteOperator::s_instance = nullptr;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  return 0;
}

SqliteOperator::SqliteOperator() {
  assert(s_instance == nullptr);
  s_instance = this;
}

SqliteOperator::~SqliteOperator() {
  assert(s_instance == this);
  s_instance = nullptr;
}

int SqliteOperator::open(const QString &str) {
  if (!str.isEmpty()) {
    assert(s_instance != nullptr);
    std::lock_guard<std::mutex> lock(s_instance->m_mutex);
    Q_UNUSED(lock)

    auto byte = str.toUtf8();
    auto size = byte.size();
    std::shared_ptr<char> sql(new char[size + 1],
                              std::default_delete<char[]>{});
    strcpy(sql.get(), byte.data());

    return sqlite3_open(sql.get(), &s_instance->pDb);
  }
  return false;
}

int SqliteOperator::close() {
  assert(s_instance != nullptr);
  std::lock_guard<std::mutex> lock(s_instance->m_mutex);
  Q_UNUSED(lock)
  return sqlite3_close(s_instance->pDb);
}

int SqliteOperator::exec(const QString &str, QString &errmgs) {
  assert(s_instance != nullptr);
  std::lock_guard<std::mutex> lock(s_instance->m_mutex);
  Q_UNUSED(lock)
  char *msg;
  auto byte = str.toUtf8();
  auto size = byte.size();
  std::shared_ptr<char> sql(new char[size + 1], std::default_delete<char[]>{});
  strcpy(sql.get(), byte.data());
  int ret = sqlite3_exec(s_instance->pDb, sql.get(), callback, 0, &msg);
  errmgs = msg;
  return ret;
}

void SqliteOperator::exec_with_tran(const QString &str) {
  assert(s_instance != nullptr);

  std::lock_guard<std::mutex> lock(s_instance->m_mutex);
  Q_UNUSED(lock)

  char *msg;
  auto byte = str.toUtf8();
  auto size = byte.size();
  std::shared_ptr<char> sql(new char[size + 1], std::default_delete<char[]>{});
  sqlite3_exec(s_instance->pDb, "BEGIN;", nullptr, 0, &msg);
  strcpy(sql.get(), byte.data());

  int ret = sqlite3_exec(s_instance->pDb, sql.get(), callback, 0, &msg);

  if (SQLITE_OK != ret)
    sqlite3_exec(s_instance->pDb, "ROLLBACK;", nullptr, 0, &msg);
  else
    sqlite3_exec(s_instance->pDb, "COMMIT;;", nullptr, 0, &msg);

}

