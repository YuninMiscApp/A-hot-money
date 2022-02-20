
#ifndef TABLE_WINDOW_H
#define TABLE_WINDOW_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtWidgets>
#include <QtCore>



//! [0]
class tableWindow : public QWidget
{
    Q_OBJECT

public:
    tableWindow();
    ~tableWindow();

    int show();
private:
    bool createConnection();
    void initializeModel(QSqlTableModel *model);
    QTableView *createView(QSqlTableModel *model, const QString &title);

    QSqlTableModel *model_;
    QTableView *view_;
};
//! [0]



#endif    //TABLE_WINDOW_H


