create table File (
	filename varchar(255),
	curhash int(11),
	curversion int(11),
	numversions int(11),
	primary key (filename)
);

create table Version (
	id int(11),
	filename varchar(255),
	size int(11),
	time int(11),
	filemodtime int(11),
	comment mediumtext,
	version int(11),
	hash int(11),
	primary key (id),
	foreign key (filename) references File(filename)
);

create table VtoB (
	versionid int(11),
	blockid int(11),
	versionindex int(11),
	primary key (versionid, blockid),
	foreign key (versionid) references Version(id),
	foreign key (blockid) references Block(id)
);

create table Block (
	id int(11),
	hash1 int(11),
	hash2 int(11),
	data mediumblob,
	primary key (id)
);
