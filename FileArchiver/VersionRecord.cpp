
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

#include <streambuf>
#include <istream>
#include <ctime> 

#include "CompressUtils.h"
#include "FileLib.h"

using namespace std;

//this struct is copied from this forum post:
// http://stackoverflow.com/a/7782037
struct membuf : std::streambuf
{
	membuf(char* begin, char* end)
	{
		this->setg(begin, begin, end);
	}
};

// Constructor, prepares for use
VersionRecord::VersionRecord()
{
	Init();
}

// Destructor, sets poit for connection to null
VersionRecord::~VersionRecord()
{
	dbcon = NULL;
}

// Constructor, tries to retrieve a record from the db  
VersionRecord::VersionRecord(std::string filename, unsigned int versionNumber)
{
	Init();
	RetrieveVersionRecordFromDB(filename, versionNumber);
}

// Sets class members to initial values
void VersionRecord::Init()
{
	dbcon = DBConnector::GetConnection();
	VersionID = 0;
	VersionNumber = 0;
	Size = 0;
	Time = 0;
	FileModificationTime = 0;
	Hash = 0;
	bIsValid = false;
}

// Tries to retrieve a version record from the database
bool VersionRecord::RetrieveVersionRecordFromDB(std::string inFilename, unsigned int versionNumber)
{
	// Prepare for failure
	bIsValid = false;
	
	// Setup statement
	sql::PreparedStatement *pstmt = dbcon->prepareStatement("select * from Version where filename=? and version=?");
	sql::ResultSet *rs;
	
	// Try to run Query
	try
	{
		pstmt->setString(1,inFilename);
		pstmt->setInt(2,versionNumber);
		rs = pstmt->executeQuery();

		// Output Results
		while(rs->next())
		{
			//count = rs->getUInt(1);
			VersionID = rs->getUInt("id");
			Filename = rs->getString("filename");
			VersionNumber = rs->getUInt("version");
			//TODO: change to getInt64?
			Size = rs->getUInt("size");
			Time = rs->getUInt("time");
			FileModificationTime = rs->getUInt("filemodtime");
			Comment = rs->getString("comment");
			Hash = rs->getUInt("hash");
			bIsValid = true;
		}


	}
	catch (sql::SQLException &e)
	{
		log("ERROR: ");
		log(e.what());
		log(e.getErrorCode());
		log(e.getSQLState());
	}
	
	// Clean up
	delete rs;
	delete pstmt;
	rs = NULL;
	pstmt = NULL;
	
	// Return result
	return bIsValid;
}

// Updates a version record in the db
bool VersionRecord::UpdateRecordInDB()
{
	sql::Statement *stmt = dbcon->createStatement();
	bool bSuccess = true;
	
	if(stmt == NULL)
	{
		//failed to get a connection to the database
		bSuccess = false;
	}

	if(IsValid() == false)
	{
		bSuccess = false;
	}
		
	try
	{   
		//create file record
		if(bSuccess)
		{
			//beginning of statement
			string sqlstatement = "update Version set ";
			//curhash
			sqlstatement += "filename = \"" + Filename + "\", ";
			sqlstatement += "size = " + boost::lexical_cast<string>(Size) + ", ";
			sqlstatement += "time = " + boost::lexical_cast<string>(Time) + ", ";
			sqlstatement += "filemodtime = " + boost::lexical_cast<string>(FileModificationTime) + ", ";
			sqlstatement += "comment = \"" + Comment + "\", ";
			sqlstatement += "version = " + boost::lexical_cast<string>(VersionNumber) + ", ";
			sqlstatement += "hash = " + boost::lexical_cast<string>(Hash);
			//end of statement
			sqlstatement += " where id = " + boost::lexical_cast<string>(VersionID) + ";";
			
			log(sqlstatement);
			
			bSuccess = stmt->executeUpdate(sqlstatement);
		}
	}
	catch (sql::SQLException &e)
	{
		log("ERROR: ");
		log(e.what());
		log(e.getErrorCode());
		log(e.getSQLState());
	}
	
	delete stmt;
	return bSuccess;
}

unsigned int VersionRecord::GetVersionId()
{
	return VersionID;
}

unsigned int VersionRecord::GetVersionNumber()
{
	return VersionNumber;
}

unsigned int VersionRecord::GetSize()
{
	return Size;
} 

unsigned int VersionRecord::GetHash()
{
	return Hash;
} 

unsigned int VersionRecord::GetModificationTime()
{
        return FileModificationTime;
}


string VersionRecord::GetFormattedModificationTime()
{
    char buffer[80];
    time_t fileTime = FileModificationTime;
    
    strftime(buffer, 80, "%F %T", localtime(&fileTime));
    return string(buffer);
}

bool VersionRecord::InsertVersionIntoDB(string keyFilename)
{
        // Prepare for sql statements
        bool bSuccess = false;
        const char* insertVersion = "insert into Version(filename, version, hash, filemodtime, size, time, comment) values (?, ?, ?, ?, ?, ?, ?)";
        const char* selectVersion = "select id from Version where hash=?"; 
        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet *rs = NULL;
        
        // Try to insert record and get the id
        try 
        {
                pstmt = dbcon->prepareStatement(insertVersion);
                pstmt->setString(1, keyFilename);
                pstmt->setInt64(2, VersionNumber);
                pstmt->setInt64(3, Hash);
                pstmt->setInt64(4, FileModificationTime);
                pstmt->setInt64(5, Size);
                pstmt->setInt64(6, Time);
                pstmt->setString(7, Comment);           
                
                bool bNewVersionMade = pstmt->executeUpdate();
                
                if (bNewVersionMade == false)
                {
                        return false;
                }
                
                // Run Query
                pstmt = dbcon->prepareStatement(selectVersion);
                pstmt->setInt64(1, Hash);
                rs = pstmt->executeQuery();

                // Output Results
                while(rs->next())
                {
                        VersionID = rs->getUInt(1);
                }
                bSuccess = true;
                
                if(bSuccess)
                {
                        RetrieveVersionRecordFromDB(keyFilename, VersionNumber);
                        if(!IsValid())
                        {
                                log("Failed to retrieve version record from database. This version was not created correctly");
                                bSuccess = false;
                        }
                }
        }
        catch (sql::SQLException &e)
        {
                log("ERROR: ");
                log(e.what());
                log(e.getErrorCode());
                log(e.getSQLState());
                log("Failed to create version in table Version");
                bSuccess = false;
        }

        pstmt->close();
        pstmt = NULL;
        delete rs;
        rs = NULL;
        return bSuccess;
}

bool VersionRecord::CreateVersion(string keyFilename, string pathFilename, unsigned int currentVersion, unsigned int newHash, string newComment)
{
	bool bSuccess = true;
	
	// Set all variables to instance of class
	FileModificationTime = FileLib::GetModifiedDate(pathFilename);
	Time = time(0);
	Size = RetrieveSizeFromDisk(pathFilename);
	Comment = newComment;
	VersionNumber = currentVersion;
	Hash = newHash;
	
	// Create a new version
	bSuccess = InsertVersionIntoDB(keyFilename);
	
	if(bSuccess)
	{	
		// Clean temp folder just incase
		zipRemoveZip();

		// Copy file to temp folder
		zipCopyContents(pathFilename);

		// Compress file in temp folder
		zipCompress();

		// Create Zip path
		string zipPath = "./temp/data.gz";

		// Create Blocks In Database
		bSuccess = InsertBlocks(zipPath);
		if(!bSuccess)
		{
			log("Failed to insert blocks for this version");
		}

		// Update
		UpdateRecordInDB();

		// Clean up temp folder
		zipRemoveZip();
	}
	else
	{
		log("Failed to create a record in the database for this version");
	}
	
	return bSuccess;
}

bool VersionRecord::InsertBlocks(string zipPath)
{
	bool bSuccess = true;
	
	// Open File
	ifstream ins(zipPath.c_str());	
	if (!ins.good())
	{
		log("Failed to open file. Cannot create version");
		bSuccess = false;
	}
	
	sql::Statement *stmt = dbcon->createStatement();
	if(bSuccess)
	{
		ins.seekg(0,ios::end);
		int bytesRemaining = ins.tellg();
		ins.seekg(0,ios::beg);
		
		try
		{
			unsigned int versionIndex = 0;
			char block[BLOCK_SIZE];
			while (!ins.eof() && bytesRemaining > 0)
			{
				// Get Block
				int blockSize = 0;
				if(bytesRemaining > BLOCK_SIZE)
				{
					blockSize = BLOCK_SIZE;
				}
				else
				{
					blockSize = bytesRemaining;
				}
				bytesRemaining -= blockSize;
				ins.read((char*)block, blockSize);
				log("block size is " + boost::lexical_cast<string>(blockSize));
				if (blockSize == 0)
				{
					break;
				}

				// Hash 1
				unsigned int hash1 = 0;
				MurmurHash3_x86_32(block, blockSize, MURMUR_SEED_1 , &hash1);

				// Hash 2
				unsigned int hash2 = 0;
				MurmurHash3_x86_32(block, blockSize, MURMUR_SEED_2 , &hash2);

				// Query DB Hash 1 in table Blocks
				unsigned int blockId = 0;

				// Run Query
				sql::ResultSet *rs = stmt->executeQuery("select id from Block where hash1 = " + boost::lexical_cast<string>(hash1));

				// Output Results
				while(rs->next())
				{
					blockId = rs->getUInt(1);
				}

				delete rs;

				// If hash 1 already exists
				if (blockId != 0)
				{
					log("Hash is not equal to zero");
					// Query DB Hash 2 in table Blocks
					unsigned int result;

					// Run Query
					sql::ResultSet *rs = stmt->executeQuery("select id from Block where hash2 = " + boost::lexical_cast<string>(hash2) + " and id = " + boost::lexical_cast<string>(blockId));

					// Output Results
					while(rs->next())
					{
						result = rs->getUInt(1);
					}

					delete rs;

					// If hash 2 matches the same id as 
					if (result != 0)
					{
						// Use existing block
						bSuccess = stmt->executeUpdate("insert into VtoB(versionid, blockid, versionindex) values (" + boost::lexical_cast<string>(this->VersionID) + ", " + boost::lexical_cast<string>(blockId) + ", " + boost::lexical_cast<string>(versionIndex++) + ")");
					}
					else
					{
						// Create a new block
						sql::PreparedStatement *pstmt = dbcon->prepareStatement("insert into Block(hash1, hash2, data) values (?,?,?)");
						pstmt->setUInt(1,hash1);
						pstmt->setUInt(2,hash2);
						membuf sbuf(block, block + blockSize);
						istream in(&sbuf);
						pstmt->setBlob(3, &in);
						bSuccess = pstmt->executeUpdate();
						delete pstmt;
						bSuccess = stmt->executeUpdate("commit");

						// Link block with VtoB
						bSuccess = stmt->executeUpdate("insert into VtoB(versionid, blockid, versionindex) values (" + boost::lexical_cast<string>(VersionID) + ", " + boost::lexical_cast<string>(blockId) + ", " + boost::lexical_cast<string>(versionIndex++) + ")");
						dbcon->commit();
					}
				}
				else 
				{
					log("Hash equals zero ");
					// Create a new block
					sql::PreparedStatement *pstmt = dbcon->prepareStatement("insert into Block(hash1, hash2, data) values (?,?,?)");
					pstmt->setUInt(1,hash1);
					pstmt->setUInt(2,hash2);
					membuf sbuf(block, block + blockSize);
					istream in(&sbuf);
					pstmt->setBlob(3, &in);
					bSuccess = pstmt->executeUpdate();
					delete pstmt;                  

					// Run Query
					dbcon->commit();
					int i = 0;
					bool bFound = false;
					while (bFound == false && i < 100)
					{
						i++;
						string sqlstatement = "select id from Block where hash1 = " + boost::lexical_cast<string>(hash1) + " and hash2 = " + boost::lexical_cast<string>(hash2);
						log(sqlstatement);
						sql::ResultSet *rs1 = stmt->executeQuery(sqlstatement);

						if(rs1->next() == false)
						{
							log("Failed to find block that was just committed");
							bSuccess = false;
						}
						else
						{
							bSuccess = true;
							bFound = true;
							blockId = rs1->getUInt(1);
						}
						delete rs1;
					}
					
					if(bSuccess)
					{
						log("blockId = " + boost::lexical_cast<string>(blockId));


						// Link block with VtoB
						string sqlstatement = "insert into VtoB(versionid, blockid, versionindex) values (" + boost::lexical_cast<string>(VersionID) + ", " + boost::lexical_cast<string>(blockId) + ", " + boost::lexical_cast<string>(versionIndex++) + ")";
						log(sqlstatement);
						bSuccess = stmt->executeUpdate(sqlstatement);
						dbcon->commit();
					}
				}
			}
		}
		catch (sql::SQLException &e)
		{
			log("ERROR: ");
			log(e.what());
			log(e.getErrorCode());
			log(e.getSQLState());
			bSuccess = false;
		}
	}
	
	ins.close();
	
	delete stmt;
	stmt = NULL;
	
	return bSuccess;
}


// Returns the size of a file passed to it
unsigned int VersionRecord::RetrieveSizeFromDisk(string path)
{
	ifstream ins(path.c_str());
	
	if (!ins.good())
	{
		log("Failed to open file. Cannot get file size.");
	}
	
	int fileSize = 0;
	if(ins.good())
	{
		ins.seekg (0, ios::end);
		fileSize = ins.tellg();
		ins.seekg (0, ios::beg);
	}
	
	return fileSize;
}

std::string VersionRecord::GetComment()
{
	return Comment;
}

bool VersionRecord::IsValid()
{
	return bIsValid;
}

bool VersionRecord::GetFileData(std::string fileOutPath)
{
	bool bSuccess = IsValid();
	sql::Statement *stmt = dbcon->createStatement();
	
	if(stmt == NULL)
	{
		//failed to get a connection to the database
		bSuccess = false;
	}
	
	ofstream outFile("./temp/data.gz");
	
	if(outFile.is_open() == false)
	{
		log("Unable to open file to write on disk");
		bSuccess = false;
	}
	
	try
	{   
		//create file record
		if(bSuccess)
		{
			string sqlstatement = "select blockid from VtoB where versionid = " + boost::lexical_cast<string>(VersionID) + " order by versionindex ASC";
			
			log(sqlstatement);
			
			sql::ResultSet *rs = stmt->executeQuery(sqlstatement);
			
			int blocksRetrieved = 0;
			while(rs->next() && bSuccess)
			{
				blocksRetrieved++;
				log("retrieved block");
				
				unsigned int blockid = rs->getUInt("blockid");
				
				//for all block records, fetch block, write to disk
				string blockretsql = "select data from Block where id = " + boost::lexical_cast<string>(blockid);
				sql::ResultSet *rs2 = stmt->executeQuery(blockretsql);
				
				if(rs2->next())
				{
					istream* data = rs2->getBlob("data");
					char outbuf[BLOCK_SIZE];
					int blobsize = data->readsome(outbuf, BLOCK_SIZE);
					outFile.write(outbuf, blobsize);
				}
				else
				{
					bSuccess = false;
				}
				
				delete rs2;
				rs2 = NULL;
			}
			
			if(blocksRetrieved == 0)
			{
				bSuccess = false;
			}
			
			delete rs;
			rs = NULL;
		}
		
		
	}
	catch (sql::SQLException &e)
	{
		log("ERROR: ");
		log(e.what());
		log(e.getErrorCode());
		log(e.getSQLState());
		bSuccess = false;
	}
	
	outFile.close();
	
	zipUncompressTo(fileOutPath);
	
	delete stmt;
	stmt = NULL;
	return bSuccess;
}

void VersionRecord::PurgeVersion()
{
    // Catch invalid version
    if (!bIsValid)
        return;
 
    sql::Statement *stmt = dbcon->createStatement();
   
    try
    {
        // Delete records from VtoB
        stmt->executeUpdate("delete from VtoB where versionid = " + boost::lexical_cast<string>(VersionID));
        
        // Clean data Blocks up
        // This will show which blocks need to be deleted "select id from Block where id not in (select b.id from Block b join VtoB v on b.id = v.blockid);"
        stmt->executeUpdate("delete b from Block b left join VtoB v on v.blockid = b.id where v.blockid is null");
    
        // Remove the version record
        stmt->executeUpdate("delete from Version where id = " + boost::lexical_cast<string>(VersionID));
        
    }
    catch (sql::SQLException e)
    {
        log("ERROR: ");
        log(e.what());
        log(e.getErrorCode());
        log(e.getSQLState());     
    }
    
    delete stmt;
    
    // Record no longer exists, it becomes invalid
    bIsValid = false;
}
