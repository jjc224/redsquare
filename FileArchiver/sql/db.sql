
create table filerec (
	filename varchar(255),
	curhash int(11),
	ovhash int(11),
	currentversion int(11),
	versions int(11),
	length int(11),
	mtnsec int(11),
	mtsec int(11),
	tempname varchar(45),
	blobtable_tempname varchar(45),

	primary key (filename)
);


create table comments (
	idcomments int(11),
	filerec varchar(255),
	commentnum int(11),
	commenttext mediumtext,
	primary key (idcomments),
	foreign key (filerec) references filerec(filename)
);

create table fileblkhashes (
	id int(11),
	filerec varchar(255),
	blknum int(11),
	hashval int(11),

	primary key (id),
	foreign key (filerec) references filerec(filename)
);



create table filerecblobtable (
	filerec varchar(255),
	tempname varchar(45),
	primary key (filerec, tempname),
	foreign key (filerec) references filerec(filename),
	foreign key (tempname) references blobtable(tempname)
);

create table blobtable (
	tempname varchar(45),
	filedata mediumblob,

	primary key (tempname),
	foreign key (filedata) references filerec(blobtable_tempname)
);

create table versionrec (
	id int(11),
	filerec varchar(255),
	versionnum int(11),
	length int(11),
	mtsec int(11),
	mtnsec int(11),
	ovhash int(11),

	primary key (id),
	foreign key (filerec) references filerec(filename)
);

create table blk (
	id int(11),
	version int(11),
	length int(11),
	blknum int(11),
	hash int(11),
	data mediumblob,

	primary key (id),
	foreign key (version) references versionrec(id)
);


