/* 
 * File:   TableModel.h
 * Author: io447
 *
 * Created on 28 September 2015, 7:03 PM
 */

#ifndef TABLEMODEL_H
#define	TABLEMODEL_H

#include <QAbstractTableModel>
#include <QtGui>
#include <vector>

using namespace std;
//class MyRecord;
//typedef MyRecord* RecordPtr;

class TableModel: public QAbstractTableModel {
    Q_OBJECT;
public:
    TableModel(QObject *parent);
    /*
    void addTheData(vector<RecordPtr> *data) {this->recordsCollection = data;}
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    void addRecord(RecordPtr newone);*/
private:
    //don't assume ownership, don't delete on destruct
    //vector<RecordPtr> *recordsCollection;
    //disallow value operations
    TableModel& operator=(const TableModel&);
    TableModel(const TableModel& orig);
};


#endif	/* TABLEMODEL_H */
