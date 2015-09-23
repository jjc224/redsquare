
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

VersionRecord::VersionRecord()
{
	Init();
}
VersionRecord::~VersionRecord()
{
	dbcon->close();
}

// Constructor
VersionRecord::VersionRecord(std::string filename, unsigned int versionNumber)
{
	Init();
	RetrieveVersionRecordFromDB(filename, versionNumber);
}

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

bool VersionRecord::RetrieveVersionRecordFromDB(std::string inFilename, unsigned int versionNumber)
{
	bIsValid = false;
	try
	{
		// Run Query
		sql::Statement *stmt = dbcon->createStatement();
		string sqlstatement = "select * from Version where filename = '" + inFilename + "' and version=" + boost::lexical_cast<string>(versionNumber) + ";";
		sql::ResultSet *rs = stmt->executeQuery(sqlstatement);
		log(sqlstatement);

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

		delete rs;
		delete stmt;
	}
	catch (sql::SQLException &e)
	{
		log("ERROR: ");
		log(e.what());
		log(e.getErrorCode());
		log(e.getSQLState());
	}
	return bIsValid;
}

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

bool VersionRecord::CreateVersion(string pathFilename, unsigned int currentVersion, unsigned int newHash, string newComment)
{
	bool bSuccess = true;
	
	// Create a new version
	sql::Statement *stmt = dbcon->createStatement();
	try 
	{
		bool bNewVersionMade = stmt->executeUpdate("insert into Version(filename, version, hash) values ('" + boost::lexical_cast<string>(pathFilename) + "', " + boost::lexical_cast<string>(currentVersion) + ", " + boost::lexical_cast<string>(newHash) + ")");
		if (bNewVersionMade == false)
		{
			return false;
		}
		
		// Run Query
		sql::ResultSet *rs = stmt->executeQuery("select id from Version where hash = " + boost::lexical_cast<string>(newHash));

		// Output Results
		while(rs->next())
		{
			this->VersionID = rs->getUInt(1);
		}
		
		delete rs;
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
	
	if(bSuccess)
	{
		RetrieveVersionRecordFromDB(pathFilename, currentVersion);
		if(!IsValid())
		{
			log("Failed to retrieve version record from database. This version was not created correctly");
			bSuccess = false;
		}
	}
 
	// Open File
	ifstream ins(pathFilename.c_str());
	
	if (!ins.good())
	{
		log("Failed to open file. Cannot create version");
		bSuccess = false;
	}
	
	int fileSize = 0;
	if(bSuccess)
	{
		ins.seekg (0, ios::end);
		fileSize = ins.tellg();
		ins.seekg (0, ios::beg);
	}
	
	int bytesRemaining = fileSize;
	//store the length of this file in the version record itself
	Size = fileSize;
	
	if(bSuccess)
	{
		try
		{
			unsigned int versionIndex = 0;
			char block[8000];
			while (!ins.eof() && bytesRemaining > 0)
			{
				// Get Block
				int blockSize = 0;
				if(bytesRemaining > 8000)
				{
					blockSize = 8000;
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
						//sql::Statement *stmt = dbcon->createStatement();
						//bool bSuccess = stmt->executeUpdate("insert into Block(hash1, hash2, data) values (" + boost::lexical_cast<string>(hash1) + ", " + boost::lexical_cast<string>(hash2) + ", " + boost::lexical_cast<string>(block) + ")");
						delete pstmt;
						bSuccess = stmt->executeUpdate("commit");

						// Link block with VtoB
						bSuccess = stmt->executeUpdate("insert into VtoB(versionid, blockid, versionindex) values (" + boost::lexical_cast<string>(this->VersionID) + ", " + boost::lexical_cast<string>(blockId) + ", " + boost::lexical_cast<string>(versionIndex++) + ")");
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
					//bSuccess = stmt->executeUpdate("commit");
					int i = 0;
					bool bFound = false;
					while (bFound == false && i < 100)
					{
						i++;
						//TODO: Should this not check for hash2 as well?
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
						string sqlstatement = "insert into VtoB(versionid, blockid, versionindex) values (" + boost::lexical_cast<string>(this->VersionID) + ", " + boost::lexical_cast<string>(blockId) + ", " + boost::lexical_cast<string>(versionIndex++) + ")";
						log(sqlstatement);
						bSuccess = stmt->executeUpdate(sqlstatement);
						stmt->executeUpdate("commit");
						//dbcon->commit();
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
	
	if(bSuccess)
	{
		Comment = newComment;
		UpdateRecordInDB();
	}
	
	ins.close();
	
	delete stmt;
	stmt = NULL;
	
	return bSuccess;
}

unsigned int VersionRecord::GetBlockHash()
{
	//TODO: add logic
	
	//TODO: is this even needed?
	return 0;
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
	
	ofstream outFile(fileOutPath.c_str());
	
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
					char outbuf[9000];
					int blobsize = data->readsome(outbuf, 9000);
					outFile.write(outbuf, blobsize);
					//TODO: transfer from data istream to outFile ofstream
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
	
	delete stmt;
	stmt = NULL;
	return bSuccess;
}
