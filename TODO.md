* Add version comment support
* Add support for different block sizes
* Retrieve file from DB
* Compress data stream
* convert DB to use uints and bigints where appropriate
* Check support for adding a second version works
* Add purge old version logic
* add unit testing for retrieving versions
* add unit testing for adding second version
* add unit testing for generating random files and committing
* add logic for retrieving file modification time
* Possibly add another check in chunk creation logic to compare actual blobs in the event of a collision, and allow duplicate hash values. This could allow the speed of hash checking for the most part, but not corrupt data when a collision occurs. This will work as we have a dedicated PK column.