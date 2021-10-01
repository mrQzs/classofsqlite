#include <QApplication>
#include <QDebug>

#include "SqliteOperator.h"

int main(int argc, char *argv[]) {
  // create logger
  SqliteOperator sqlite_operator;
  Q_UNUSED(sqlite_operator)

  int ret = SqliteOperator::open("/home/qzs/testdb.db");
  SQLITE_OK == ret ? qDebug() << "Ok" : qDebug() << "Wrong";

  auto sql =
      "CREATE TABLE COMPANY("
      "ID INT PRIMARY KEY     NOT NULL,"
      "NAME           TEXT    NOT NULL,"
      "AGE            INT     NOT NULL,"
      "ADDRESS        CHAR(50),"
      "SALARY         REAL );";

  ret = SqliteOperator::close();
  SQLITE_OK == ret ? qDebug() << "Ok" : qDebug() << "Wrong";
  QApplication a(argc, argv);
  return QApplication::exec();
}
