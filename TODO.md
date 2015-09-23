# Core Changes
** _convert DB to use uints and bigints where appropriate_ - *DONE*
* Add purge old version logic
* Compress data stream
* Add support for different block sizes

# Versioning
** _Add version comment support_ - *DONE*

# Retrieval
** _Retrieve file from DB_ - **DONE**

# Improvements
* add logic for retrieving file modification time
* Possibly add another check in chunk creation logic to compare actual blobs in the event of a collision, and allow duplicate hash values. This could allow the speed of hash checking for the most part, but not corrupt data when a collision occurs. This will work as we have a dedicated PK column.

# Unit testing
** _add a function that can generate a file of specified size, with a specified seed for repeatable testing._ - *DONE*
** _add unit testing for retrieving versions_ - *DONE*
** _add unit testing for adding second version_ - *DONE*
** _add unit testing for generating random files and committing_ - *DONE*
* add a delete file statement into the first retrieval test case