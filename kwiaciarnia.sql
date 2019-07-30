use kwiaciarnia;

drop table zamowienia;
drop table klient;
drop table logowanie;

CREATE TABLE LOGOWANIE
(
	ID_KLIENTA		  	int				not null auto_increment,
	LOGIN 				varchar(50) 	not null,
    HASLO 				varchar(50)		not null,
    TYP_KONTA			varchar(20)		not null,
    
    PRIMARY KEY(ID_KLIENTA)
);

create table KLIENT
(
	ID_KLIENTA			int				not null auto_increment,
	IMIE				varchar(50)		null,
    NAZWISKO			varchar(50)		not null,
    MIASTO				varchar(50)		null,
    ADRES				varchar(50)		null,
    KOD_POCZTOWY		varchar(7)		null,
    NR_TELEFONU			varchar(15)		null,
    MAIL				varchar(100)	null,
    
   PRIMARY KEY (ID_KLIENTA),
   foreign key (ID_KLIENTA)
		references LOGOWANIE(ID_KLIENTA)
);

create table ZAMOWIENIA
(
   NR_ZAMOWIENIA		int				not null	AUTO_INCREMENT,
   ID_KLIENTA			int				not null,
   STAT_ZAMOWIENIA		varchar(30)		not null,
   OPIS					varchar(1000)   null,
   CENA					VARCHAR(5)		null,

   PRIMARY KEY(NR_ZAMOWIENIA),
   foreign key(ID_KLIENTA)
		references KLIENT(ID_KLIENTA)
);


INSERT INTO LOGOWANIE (LOGIN, HASLO, TYP_KONTA) VALUE ("admin", "521", "administrator");