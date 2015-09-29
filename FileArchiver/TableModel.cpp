
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include "TableModel.h"
#include "FileArchiver.h"
#include "FileLib.h"

using namespace std;

TableModel::TableModel(QObject* parent)
        :QAbstractTableModel(parent)
{
}

int TableModel::rowCount(const QModelIndex& /* parent */) const
{
    return recordsCollection.size();
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
            return QString(recordsCollection.at(index.row()).versionNum.c_str());   
        }
        
        if(index.column() == 1)
        {
            return QString(recordsCollection.at(index.row()).versionDate.c_str());  
        }
        
        if(index.column() == 2)
        {
            return QString(recordsCollection.at(index.row()).versionSize.c_str());  
        }
    }
    
    return QVariant();
}

void TableModel::addRecord(FileRecord newone)
{
    vector<VersionRecord> versionRecs = newone.GetAllVersions();
    RecordData currRecord;
    
    for(vector<VersionRecord>::iterator it = versionRecs.begin(); it != versionRecs.end(); ++it)
    {
        currRecord.versionNum  = boost::lexical_cast<string>(it->GetVersionNumber());
        currRecord.versionDate = boost::lexical_cast<string>(FileLib::GetModifiedDate(newone.GetFilename()));
        currRecord.versionSize = boost::lexical_cast<string>(it->GetSize());

        recordsCollection.push_back(currRecord);
    }
}