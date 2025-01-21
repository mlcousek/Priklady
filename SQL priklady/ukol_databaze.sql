-- Active: 1665410689296@@database.inf.upol.cz@5432@mlcoji00@public

--UKOL1

DROP TABLE IF EXISTS hry;
CREATE TABLE hry
(id_hry INT PRIMARY KEY,
 nazev TEXT,
 id_vydavatele INT,
 cena INT);

DROP TABLE IF EXISTS hraci;
CREATE TABLE hraci
(id_hrace INT PRIMARY KEY,
 jmeno TEXT NOT NULL,
 prijmeni TEXT NOT NULL,
 prezdivka TEXT NOT NULL);

DROP TABLE IF EXISTS vlastni_hru;
CREATE TABLE vlastni_hru
(id_hrace INT,
 id_hry INT);

DROP TABLE IF EXISTS ma_kamarada;
CREATE TABLE ma_kamarada
(id_hrace INT,
 id_kamarada INT);

DROP TABLE IF EXISTS komentare;
CREATE TABLE komentare
(id_hrace INT,
 id_hry INT,
 komentar TEXT NOT NULL);

DROP TABLE IF EXISTS vydavatele;
CREATE TABLE vydavatele
(id_vydavatele INT PRIMARY KEY,
 nazev_vydavatele TEXT NOT NULL);

DROP TABLE IF EXISTS vydal_hru;
CREATE TABLE vydal_hru
(id_vydavatele INT,
 id_hry TEXT NOT NULL);

--hry
INSERT INTO hry VALUES (1,'FIFA23',1,1950);
INSERT INTO hry VALUES (2,'FIFA22',1,950);
INSERT INTO hry VALUES (3,'FIFA21',1,300);
INSERT INTO hry VALUES (4,'FIFA20',1,300);
INSERT INTO hry VALUES (5,'FIFA19',1,300);
INSERT INTO hry VALUES (6,'FIFA18',1,300);
INSERT INTO hry VALUES (7,'FIFA17',1,300);
INSERT INTO hry VALUES (8,'FIFA16',1,300);
INSERT INTO hry VALUES (9,'FIFA15',1,500);
INSERT INTO hry VALUES (10,'FIFA14',1,500);
INSERT INTO hry VALUES (11,'FIFA13',1,1000);
INSERT INTO hry VALUES (12,'FIFA12',1,5000);
INSERT INTO hry VALUES (13,'FIFA11',1,150);
INSERT INTO hry VALUES (14,'League of Legends',2,0);
INSERT INTO hry VALUES (15,'FIFA24',1,NULL);
INSERT INTO hry VALUES (16,'World of Warcrat',3,2500);
INSERT INTO hry VALUES (17,'Minecraft',4,800);





--hraci
INSERT INTO hraci VALUES (1,'Jiri', 'Mlcousek', 'JM6');
INSERT INTO hraci VALUES (2,'Patrik', 'Tarabik', 'CoolMex');
INSERT INTO hraci VALUES (3,'Vasek', 'Orsag', 'Dvojzarez2008');


--kdo ma jakou hru
INSERT INTO vlastni_hru VALUES (1,12);
INSERT INTO vlastni_hru VALUES (1,11);
INSERT INTO vlastni_hru VALUES (1,9);
INSERT INTO vlastni_hru VALUES (1,6);
INSERT INTO vlastni_hru VALUES (1,5);
INSERT INTO vlastni_hru VALUES (1,4);
INSERT INTO vlastni_hru VALUES (1,3);
INSERT INTO vlastni_hru VALUES (1,1);
INSERT INTO vlastni_hru VALUES (1,17);

INSERT INTO vlastni_hru VALUES (2,10);
INSERT INTO vlastni_hru VALUES (2,8);
INSERT INTO vlastni_hru VALUES (2,7);
INSERT INTO vlastni_hru VALUES (2,6);
INSERT INTO vlastni_hru VALUES (2,5);
INSERT INTO vlastni_hru VALUES (2,4);
INSERT INTO vlastni_hru VALUES (2,17);

INSERT INTO vlastni_hru VALUES (3,17);
INSERT INTO vlastni_hru VALUES (3,16);
INSERT INTO vlastni_hru VALUES (3,14);




--kdo je s kym kamos
INSERT INTO ma_kamarada VALUES (1,2);
INSERT INTO ma_kamarada VALUES (2,1);
INSERT INTO ma_kamarada VALUES (1,3);
INSERT INTO ma_kamarada VALUES (3,1);


--komentare
INSERT INTO komentare VALUES (1,9,'Nejlepsi FIFA vsech dob.');
INSERT INTO komentare VALUES (3,17,'Je to top na chill s kamosem.');
INSERT INTO komentare VALUES (1,12,'Nostalgie.');
INSERT INTO komentare VALUES (2,17,'Ja miluju majnkraft.');
INSERT INTO komentare VALUES (2,1,'Tuto hru bych si pral.');



--vydavatele
INSERT INTO vydavatele VALUES (1,'EASPORTS');
INSERT INTO vydavatele VALUES (2,'Riot Games');
INSERT INTO vydavatele VALUES (3,'Blizard');
INSERT INTO vydavatele VALUES (4,'Mojang');

--vydal hru
INSERT INTO vydal_hru VALUES (1,1);
INSERT INTO vydal_hru VALUES (1,2);
INSERT INTO vydal_hru VALUES (1,3);
INSERT INTO vydal_hru VALUES (1,4);
INSERT INTO vydal_hru VALUES (1,5);
INSERT INTO vydal_hru VALUES (1,6);
INSERT INTO vydal_hru VALUES (1,7);
INSERT INTO vydal_hru VALUES (1,8);
INSERT INTO vydal_hru VALUES (1,9);
INSERT INTO vydal_hru VALUES (1,10);
INSERT INTO vydal_hru VALUES (1,11);
INSERT INTO vydal_hru VALUES (1,12);
INSERT INTO vydal_hru VALUES (1,13);
INSERT INTO vydal_hru VALUES (1,15);
INSERT INTO vydal_hru VALUES (2,14);
INSERT INTO vydal_hru VALUES (3,16);
INSERT INTO vydal_hru VALUES (4,17);














--TABULKY
TABLE hry;
TABLE hraci;
TABLE vlastni_hru;
TABLE ma_kamarada;
TABLE komentare;


--SELECT vyrazy
-- Pro dva zvolené uživatele (pro ukázku si vyberte sami) chceme všechny hry, které si spolu mohou zahrát (tj ty, které vlastní oba dva).
SELECT nat_join.nazev FROM ((hry NATURAL JOIN vlastni_hru) NATURAL JOIN hraci) as nat_join,
	(vlastni_hru NATURAL JOIN hraci) as hra 
	WHERE NOT nat_join.id_hrace = hra.id_hrace AND nat_join.id_hry = hra.id_hry AND nat_join.prezdivka = 'JM6' AND hra.prezdivka = 'CoolMex';
-- Pro zadaného uživatele (pro ukázku si vyberte sami) chceme tři nejdražší hry, které vlastní, a jejich vydavatele.
SELECT nat_join.nazev, nat_join.cena, nat_join.nazev_vydavatele FROM (((hry NATURAL JOIN vlastni_hru) NATURAL JOIN hraci) NATURAL JOIN vydavatele) as nat_join 
			WHERE nat_join.prezdivka = 'JM6' ORDER BY nat_join.cena DESC limit 3;


--Pro zadaného uživatele (pro ukázku si vyberte sami) chceme všechny hry, které komentoval některý z jeho přátel, spolu s odpovídajícím komentářem a přezdívkou jeho autora.
SELECT nat_join2.nazev as nazev_hry, nat_join2.komentar, nat_join2.prezdivka
		FROM (hraci NATURAL JOIN ma_kamarada) as nat_join,
			((hry NATURAL JOIN hraci) NATURAL JOIN komentare) as nat_join2 
				WHERE nat_join.prezdivka = 'JM6' AND nat_join.id_kamarada = nat_join2.id_hrace;


