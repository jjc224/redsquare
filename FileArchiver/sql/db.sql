create table File (
	filename varchar(767) not null,
	curhash int(11),
	curversion int(11),
	numversions int(11),
	primary key (filename)
);

create table Version (
	id int(11) not null auto_increment,
	filename varchar(767),
	size int(11),
	time int(11),
	filemodtime int(11),
	comment mediumtext,
	version int(11),
	hash int(11),
	primary key (id),
	foreign key (filename) references File(filename)
);


create table Block (
	id int(11) not null auto_increment,
	hash1 int(11) unsigned,
	hash2 int(11) unsigned,
	data mediumblob,
	primary key (id),
	index(hash1),
	index(hash2)
);


create table VtoB (
	id int(11) not null auto_increment,
	versionid int(11),
	blockid int(11),
	versionindex int(11),
	primary key (id),
	foreign key (versionid) references Version(id),
	foreign key (blockid) references Block(id)
);

alter table Version auto_increment = 1;
alter table Block auto_increment = 1;
alter table VtoB auto_increment = 1;


delete from VtoB;
delete from Block;
delete from Version;
delete from File;


drop table VtoB;
drop table Block;
drop table Version;
drop table File;


