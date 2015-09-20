
#include <iostream>
#include <fstream>

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


#include "VersionRecord.h"
#include "ProjectConstants.h"
#include "DBConnector.h"
#include "MurmurHash3.h"
#include "boost/lexical_cast.hpp"

using namespace std;

VersionRecord::VersionRecord()
{
    dbcon = DBConnector::GetConnection();
}
VersionRecord::~VersionRecord()
{
    dbcon->close();
}

unsigned int VersionRecord::GetVersionId()
{

}

unsigned int VersionRecord::GetVersionNumber()
{

}

unsigned int VersionRecord::GetSize()
{

} 

unsigned int VersionRecord::GetHash()
{

} 

bool VersionRecord::CreateVersion(string pathFilename, unsigned int currentVersion, unsigned int newHash)
{
    
    // Create a new version
    sql::Statement *stmt = dbcon->createStatement();
    try 
    {
        bool bNewVersionMade = stmt->executeUpdate("insert into redsquare.Version(filename, version, hash) values ('" + boost::lexical_cast<string>(pathFilename) + "', " + boost::lexical_cast<string>(currentVersion) + ", " + boost::lexical_cast<string>(newHash) + ")");
        if (bNewVersionMade == false)
            return false;
        
        // Run Query
        sql::Statement *stmt = dbcon->createStatement();
        sql::ResultSet *rs = stmt->executeQuery("select id from redsquare.Version where hash = " + boost::lexical_cast<string>(newHash));

        // Output Results
        while(rs->next())
            this->VersionId = rs->getInt(1);
        
        delete rs;
        delete stmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "ERROR: " << endl;
        cout << e.what() << endl;
        cout << e.getErrorCode() << endl;
        cout << e.getSQLState() << endl;
        return false;
    } 
    delete stmt;
    

    
//    id int(11) not null auto_increment,
//    filename varchar(255),
//    size int(11),
//    time int(11),
//    filemodtime int(11),
//    //comment mediumtext,
//    version int(11),
//    hash int(11),
//    
 
           
            
    // Open File
    ifstream ins(pathFilename.c_str());
    
    if (!ins.good())
    {
        return false;
    }
    
    try
    {
        unsigned int versionIndex = 0;
        char block[8000];
        while (ins.good())
        {
            
            // Get Block
            ins.read((char*)block, 8000);
            if (!ins.good())
                break;
            
            // Hash 1
            unsigned int hash1 = 0;
            MurmurHash3_x86_32(block, 8000, MURMUR_SEED_1 , &hash1);

            // Hash 2
            unsigned int hash2 = 0;
            MurmurHash3_x86_32(block, 8000, MURMUR_SEED_2 , &hash2);

            // Query DB Hash 1 in table Blocks
            unsigned int blockId = 0;

            // Run Query
            sql::Statement *stmt = dbcon->createStatement();
            sql::ResultSet *rs = stmt->executeQuery("select id from redsquare.Block where hash1 = " + boost::lexical_cast<string>(hash1));

            // Output Results
            while(rs->next())
                blockId = rs->getInt(1);

            delete rs;
            delete stmt;

            // If hash 1 already exists
            if (blockId != 0)
            {
                cout << "Hash is not equal to zero" << endl;
                // Query DB Hash 2 in table Blocks
                unsigned int result;
                
                // Run Query
                sql::Statement *stmt = dbcon->createStatement();
                sql::ResultSet *rs = stmt->executeQuery("select id from redsquare.Block where hash2 = " + boost::lexical_cast<string>(hash2) + " and id = " + boost::lexical_cast<string>(blockId));

                // Output Results
                while(rs->next())
                    result = rs->getInt(1);

                delete rs;
                delete stmt;

                // If hash 2 matches the same id as 
                if (result != 0)
                {
                    // Use existing block
                    sql::Statement *stmt = dbcon->createStatement();
                    bool bSuccess = stmt->executeUpdate("insert into redsquare.VtoB(versionid, blockid, versionindex) values (" + boost::lexical_cast<string>(this->VersionId) + ", " + boost::lexical_cast<string>(blockId) + ", " + boost::lexical_cast<string>(versionIndex++) + ")");
                    delete stmt;
                }
                else
                {
                    // Create a new block
                    sql::PreparedStatement *pstmt = dbcon->prepareStatement("insert into redsquare.Block(hash1, hash2, data) values (?,?,?)");
                    pstmt->setInt(1,hash1);
                    pstmt->setInt(2,hash2);
                    pstmt->setString(3,block);
                    //sql::Statement *stmt = dbcon->createStatement();
                    //bool bSuccess = stmt->executeUpdate("insert into redsquare.Block(hash1, hash2, data) values (" + boost::lexical_cast<string>(hash1) + ", " + boost::lexical_cast<string>(hash2) + ", " + boost::lexical_cast<string>(block) + ")");
                    delete pstmt;                  
                    
                    // Link block with VtoB
                    sql::Statement *stmt = dbcon->createStatement();
                    bool bSuccess = stmt->executeUpdate("insert into redsquare.VtoB(versionid, blockid, versionindex) values (" + boost::lexical_cast<string>(this->VersionId) + ", " + boost::lexical_cast<string>(blockId) + ", " + boost::lexical_cast<string>(versionIndex++) + ")");
                    bSuccess = stmt->executeUpdate("commit");
                    delete stmt;
                }
            }
            else 
            {
                cout << "Hash equals zero " << endl;
                // Create a new block
                sql::PreparedStatement *pstmt = dbcon->prepareStatement("insert into redsquare.Block(hash1, hash2, data) values (?,?,?)");
                pstmt->setInt(1,hash1);
                pstmt->setInt(2,hash2);
                pstmt->setString(3,block);
                pstmt->execute();
                delete pstmt;                  

                // Run Query
                sql::Statement *stmt1 = dbcon->createStatement();
                stmt1->executeQuery("commit");
                sql::ResultSet *rs1 = stmt1->executeQuery("select id from redsquare.Block where hash1 = " + boost::lexical_cast<string>(hash1));

                // Output Results
                while(rs1->next())
                    blockId = rs1->getInt(1);

                cout << "blockId = " << blockId << endl;
                delete rs1;
                delete stmt1;
                
                
                // Link block with VtoB
                sql::Statement *stmt = dbcon->createStatement();
                cout << "insert into redsquare.VtoB(versionid, blockid, versionindex) values (" + boost::lexical_cast<string>(this->VersionId) + ", " + boost::lexical_cast<string>(blockId) + ", " + boost::lexical_cast<string>(versionIndex++) + ")" << endl;
                bool bSuccess = stmt->executeUpdate("insert into redsquare.VtoB(versionid, blockid, versionindex) values (" + boost::lexical_cast<string>(this->VersionId) + ", " + boost::lexical_cast<string>(blockId) + ", " + boost::lexical_cast<string>(versionIndex++) + ")");
                bSuccess = stmt->executeUpdate("commit");
                delete stmt;
                
                
                
            }
        }
    }
    catch (sql::SQLException &e)
    {
        cout << "ERROR: " << endl;
        cout << e.what() << endl;
        cout << e.getErrorCode() << endl;
        cout << e.getSQLState() << endl;
    }
    
}

unsigned int VersionRecord::GetBlockHash()
{
    
}
std::string VersionRecord::GetComment()
{

}

bool VersionRecord::IsValid()
{
    
}

bool VersionRecord::GetFileData(std::string fileOutPath)
{
    if(IsValid())
    {
        //TODO: do logic here
    }
    return false;
}
