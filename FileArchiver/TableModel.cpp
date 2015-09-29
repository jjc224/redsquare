
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include "TableModel.h"
#include "FileArchiver.h"

using namespace std;

TableModel::TableModel(QObject* parent)
        :QAbstractTableModel(parent)
{
}

int TableModel::rowCount(const QModelIndex& /* parent */) const
{
    return recordsCollection->size();
}

int TableModel::columnCount(const QModelIndex& /* parent */) const
{
    return 3;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
                case 0:
                    return QString("Version #");
                    
                case 1:
                    return QString("Date");
                    
                case 2:
                    return QString("Size");
            }
        }
    }
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(index.column() == 0)
        {
            //return QString(recordsCollection->at(index.row())->get);   
        }
    }
}

void TableModel::addRecord(vector<VersionRecord> newone)
{
    string currRow[3];
    
    for(vector<VersionRecord>::iterator it = newone.begin(); it != newone.end(); ++it)
    {
        currRow[0] = boost::lexical_cast<string>(it->GetVersionNumber());   // ...
        currRow[1] = boost::lexical_cast<string>(FileLib::GetModifiedDate(it->GetVersionId()));
        currRow[2] = boost::lexical_cast<string>(it->GetSize());

        recordsCollection.push_back(currRow);
    }
}