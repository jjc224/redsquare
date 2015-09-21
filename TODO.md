# Core Changes
* convert DB to use uints and bigints where appropriate
* Add purge old version logic
* Compress data stream
* Add support for different block sizes

# Versioning
* Add version comment support

# Retrieval
* Retrieve file from DB

# Improvements
* add logic for retrieving file modification time
* Possibly add another check in chunk creation logic to compare actual blobs in the event of a collision, and allow duplicate hash values. This could allow the speed of hash checking for the most part, but not corrupt data when a collision occurs. This will work as we have a dedicated PK column.

# Unit testing
* add unit testing for retrieving versions
* add unit testing for adding second version
* add unit testing for generating random files and committing
* Check support for adding a second version works
* Check that added version matches extracted version (retrieve and then hash it)