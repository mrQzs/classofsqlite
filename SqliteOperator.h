//
// Created by qzs on 2021/9/30.
//

#ifndef SQLITE3__SQLITEOPERATOR_H_
#define SQLITE3__SQLITEOPERATOR_H_

#include <QObject>
#include <memory>
#include <mutex>

#include "sqlite3.h"

class SqliteOperator : public QObject {
  Q_OBJECT
 public:
  SqliteOperator();
  ~SqliteOperator() override;

 public:
  static int open(const QString &str);
  static int close();
  static int exec(const QString &str, QString &errmgs);
  static void exec_with_tran(const QString &str);

  inline static SqliteOperator *GetInstance() {
    assert(s_instance != NULL);
    return s_instance;
  }

 private:
 private:
  static SqliteOperator *s_instance;
  std::mutex m_mutex;
  sqlite3 *pDb;
};

#endif  // SQLITE3__SQLITEOPERATOR_H_
