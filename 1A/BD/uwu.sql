/*Création de base */

DROP TABLE IF EXISTS ExamenQCM ;
CREATE TABLE IF NOT EXISTS ExamenQCM (
Theme VARCHAR(50) NOT NULL,
DateEx DATE NOT NULL ,
NomApp VARCHAR(50) NOT NULL,
Question1 VARCHAR(50),
Rep11 VARCHAR(50),
Rep12 VARCHAR(50),
Rep13 VARCHAR(50),
BonneRep1 TINYINT UNSIGNED
CHECK ( BonneRep1 IN (1,2,3) ) ,
ReppApp1 TINYINT UNSIGNED DEFAULT NULL
CHECK ( ReppApp1 IN (1,2,3) ),
Note1 FLOAT DEFAULT -1,
Coeff1 TINYINT UNSIGNED,
Question2 VARCHAR(50),
Rep21 VARCHAR(50),
Rep22 VARCHAR(50),
BonneRep2 TINYINT UNSIGNED
CHECK ( BonneRep2 IN (1,2) ) ,
ReppApp2 TINYINT UNSIGNED DEFAULT NULL
CHECK ( ReppApp1 IN (1,2) ),
Note2 FLOAT DEFAULT -1,
Coeff2 TINYINT UNSIGNED,
Termine BOOLEAN DEFAULT FALSE,
NoteApp FLOAT DEFAULT NULL
CHECK ((Termine=FALSE AND NoteApp IS NULL)
OR
(Termine=TRUE AND NoteApp IS NOT NULL)),
CONSTRAINT PK_ExamenQCM PRIMARY KEY(Theme, NomApp)
) ;

-- Remplissage de la table

INSERT INTO ExamenQCM VALUES ('QCM_SQL', '2022-01-18', 'Nom0', 'Le R de SGBDR signifie ', 'Relationnelle', 'Relative', 'Récréative', '1', '1', '4', '1', 'SQL est un ', 'Logiciel', 'Langage', '2', '1', '4', '1', FALSE, NULL);

INSERT INTO ExamenQCM VALUES ('QCM_SQL', '2022-01-18', 'Nom2', 'Le R de SGBDR signifie ', 'Relationnelle', 'Relative', 'Récréative', '1', '1', '4', '1', 'SQL est un ', 'Logiciel', 'Langage', '1', '1', '4', '1', FALSE, NULL);  

INSERT INTO ExamenQCM VALUES ('QCM_SQL', '2022-01-18', 'Nom3', 'Le R de SGBDR signifie ', 'Relationnelle', 'Relative', 'Récréative', '1', '1', '4', '1', 'SQL est un ', 'Logiciel', 'Langage', '1', '1', '4', '1', FALSE, NULL); 

INSERT INTO ExamenQCM
VALUES ('QCM_SQL', '2022-01-18', 'Nom4',
'Le R de SGBDR signifie ', 'Relationnelle', 'Relative', 'Récréative', '1', '1',
'4', '1',
'SQL est un ', 'Logiciel', 'Langage', '1', '1', '-1', '1',
TRUE, '10'); 

INSERT INTO ExamenQCM VALUES ('QCM_SQL', '2022-01-18', 'Nom6', 'Le R de SGBDR signifie ', 'Relationnelle', 'Relative', 'Récréative', '1', '1', '4', '1', 'SQL est un ', 'Logiciel', 'Langage', '1', '3', '-2', '1', FALSE, NULL); 

INSERT INTO ExamenQCM
VALUES ('QCM_SQL', '2022-01-18', 'Nom10',
'Le R de SGBDR signifie ', 'Relationnelle', 'Relative', 'Récréative', '1', '2',
'-2', '1',
'SQL est un ', 'Logiciel', 'Langage', '1', '2', '-2', '1',
FALSE, NULL); 

INSERT INTO ExamenQCM
VALUES ('QCM_SQL', '2022-01-18', 'Nom11',
'Le R de SGBDR signifie ','Relationnelle','Relative','Récréative', '1', '2','-2', '1',
'SQL est un ', 'Logiciel', 'Langage', '1', '2', '-2', '1',
TRUE, '-2'); 

-- Fonction 

DELIMITER $$
-- OR REPLACE ci dessous evite une erreur si la procédure existait deja
CREATE OR REPLACE PROCEDURE CalculNotesApp ( )
 BEGIN
-- Mettre NULL pour toutes les notes des examens en cours.
UPDATE ExamenQCM
SET NoteApp = NULL
WHERE examenqcm.Termine= FALSE ;
-- calculer la note de l’apprenant pour tous les examens terminés.
UPDATE ExamenQCM
SET NoteApp = (Note1 * Coeff1 + Note2 * Coeff2 ) / ( Coeff1 + Coeff2 ) 
WHERE Termine = TRUE ;
 END $$
DELIMITER ; 

DROP FUNCTION IF EXISTS NbExemansEnCours ;
DELIMITER $$
CREATE FUNCTION NbExemansEnCours()
RETURNS TINYINT
BEGIN
 DECLARE nb TINYINT;
 SELECT COUNT(IDexamen) INTO nb
 FROM examenqcm
 WHERE termine = FALSE;
 RETURN nb;
 END$$
DELIMITER ; 

 DROP FUNCTION IF EXISTS NbExemansEnCoursPour; DELIMITER $$
CREATE FUNCTION NbExemansEnCoursPour(nom VARCHAR(50)) RETURNS TINYINT BEGIN
 DECLARE nb TINYINT;
 SELECT COUNT(IDexamen ) INTO nb 
 FROM examenqcm 
 WHERE termine = FALSE 
 AND examenqcm.NomApp = nom;
 RETURN nb;
 END$$
DELIMITER ;;
 RETURN nb;
 END$$
DELIMITER ; 

DROP FUNCTION IF EXISTS MoyenneExamensTermines; DELIMITER $$ CREATE FUNCTION MoyenneExamensTermines() BEGIN
 DECLARE moy FLOAT;
 SELECT AVG(NoteApp) INTO moy
FROM examenqcm
WHERE termine = TRUE;
 RETURN 

DELIMITER $$ CREATE OR REPLACE FUNCTION MoyenneExamensTerminesPour(nom VARCHAR(50)) RETURNS FLOAT BEGIN
 DECLARE moy FLOAT;
 SELECT AVG(NoteApp) INTO moy
FROM examenqcm
WHERE termine = TRUE AND examenqcm.NomApp = nom;  RETURN moy;
 END $$
DELIMITER ; 

DROP FUNCTION IF EXISTS ValidationExamen;
DELIMITER $$
CREATE FUNCTION ValidationExamen (note FLOAT ) RETURNS VARCHAR(20) BEGIN
 DECLARE res VARCHAR(20);
 IF (examenqcm.Termine = FALSE) THEN
SET res = "Examen en cours ..." ;
Else
IF (note>10) THEN
SET res = "Examen VALIDE" ;
 ELSE SET res= "EXAMEN ECHOUE";
 END IF ;
 END IF ;
 RETURN res;
END$$
DELIMITER ;

-- TRIGGER

DROP EVENT IF EXISTS ActualiserNoteChaqueJour;
DELIMITER $$
CREATE EVENT ActualiserNoteChaqueJour
 ON SCHEDULE EVERY 1 DAY
 DO
BEGIN

    UPDATE ExamenQCM
    SET NoteApp = NULL
    WHERE Termine = FALSE ; 

    UPDATE ExamenQCM
    SET Note1 = CASE
        WHEN BonneRep1=ReppApp1 THEN 4
        WHEN ReppApp1=NULL THEN -1
        ELSE -2
    END ,
    Note2 = CASE
        WHEN BonneRep2=ReppApp2 THEN 4
        WHEN ReppApp2=NULL THEN -1
        ELSE -2
    END ; 

    UPDATE ExamenQCM
    SET NoteApp = note1*Coeff1+Note2*Coeff2/(Coeff1+Coeff2)
    WHERE termine=TRUE;

END $$
DELIMITER ; 




DROP trigger IF EXISTS Trigger_VerifDate;
DELIMITER $$
CREATE TRIGGER Trigger_VerifDate
 BEFORE INSERT
 ON examenqcm FOR EACH ROW
Begin
IF (NEW.DateEx NOT BETWEEN '2023-09-01' AND '2024-06-30')
THEN
 SIGNAL SQLSTATE '45000'
 SET MESSAGE_TEXT = 'La date doit être comprise dans l''année scolaire'; END IF ;
END$$
DELIMITER ; 

DROP trigger IF EXISTS Trigger_VerifReponse2;
DELIMITER $$
CREATE TRIGGER Trigger_VerifReponse2
 BEFORE INSERT
 ON examenqcm FOR EACH ROW
Begin
IF (NEW.ReppApp2 NOT IN (1,2))
THEN
 SIGNAL SQLSTATE '45000'
 SET MESSAGE_TEXT = 'La bonne réponse proposée à la question 2 ne fait pas partie des réponses possibles (1 ou 2) ';
END IF ;
END$$
DELIMITER ; 

DROP trigger IF EXISTS Trigger_CalculDesNotes;
DELIMITER $$
CREATE TRIGGER Trigger_CalculDesNotes
 BEFORE INSERT
 ON examenqcm FOR EACH ROW
Begin
IF NEW.Termine = FALSE
    THEN SET NEW.NoteApp = NULL ;
    ELSE IF (NEW.ReppApp1 IS NULL)
            THEN SET NEW.Note1 = -1 ;
        ELSEIF (NEW.ReppApp1 = NEW.BonneRep1)
            THEN SET New.note1 = 4;
        ELSE
            SET New.note1 = -2;
 END IF ;

SET NEW.Note2 = CASE
                WHEN NEW.ReppApp2 IS NULL THEN -1
                WHEN NEW.ReppApp2 = BonneRep2 THEN 4
                ELSE -2
 END ;
 SET NEW.NoteApp = note1*Coeff1+Note2*Coeff2/(Coeff1+Coeff2) ;
END IF ;
END$$
DELIMITER ; 

DROP FUNCTION IF EXISTS Supp10;
DELIMITER $$
CREATE FUNCTION Supp10 () RETURNS VARCHAR(2000)
BEGIN
    DECLARE unNom VARCHAR(255);
    DECLARE is_done INTEGER DEFAULT 0;
    DECLARE tousLesNoms VARCHAR(2000) DEFAULT '';
    DECLARE nbEtudiants INTEGER DEFAULT 0;

    DECLARE nom_etudiant CURSOR FOR
        SELECT NomApp FROM examenqcm WHERE examenqcm.NoteApp > 4;

    DECLARE CONTINUE HANDLER FOR NOT FOUND SET is_done = 1;

    OPEN nom_etudiant;

    boucle_lecture: LOOP
        FETCH nom_etudiant INTO unNom;
        IF is_done = 1 THEN
            LEAVE boucle_lecture;
        END IF;
        SET tousLesNoms = CONCAT(tousLesNoms, ';', unNom);
        SET nbEtudiants = nbEtudiants + 1;
    END LOOP boucle_lecture;

    CLOSE nom_etudiant;

    SET tousLesNoms = CONCAT('Voici les noms de ceux qui ont plus de 10 : ', tousLesNoms);

    RETURN tousLesNoms;
END$$
DELIMITER ;

SELECT Supp10();

DELIMITER $$
CREATE OR REPLACE PROCEDURE Pourcentage(IN nom VARCHAR(20), OUT prctExamTermines FLOAT, OUT prctBonnesReponses FLOAT)
BEGIN
    DECLARE nbE TINYINT;
    DECLARE nbET TINYINT;
    DECLARE nbRep1 TINYINT;
    DECLARE nbRep2 TINYINT;
    DECLARE nbExam CURSOR
    FOR
        SELECT 
            COUNT(*) AS nbE,
            SUM(CASE 
                WHEN e.Termine = 1 THEN 1
                ELSE 0
            END) AS nbET,
            SUM(CASE
                   WHEN e.ReppApp1 = e.BonneRep1 AND termine=TRUE THEN 1
                   ELSE 0
                   END) AS nbRep1,
            SUM(CASE
                   WHEN e.ReppApp2 = e.BonneRep2 AND termine=TRUE THEN 1
                   ELSE 0
                   END) AS nbRep2
        FROM examenqcm AS e
        WHERE e.NomApp = nom;
    OPEN nbExam;
    FETCH nbExam INTO nbE, nbET, nbRep1, nbRep2;
    SET prctExamTermines = nbET/nbE;
    SET prctBonnesReponses = (nbRep1+nbRep2) / (nbET*2);
END $$
DELIMITER ;

CALL Pourcentage("test3", @nbE, @nbR);
SELECT @nbE, @nbR;

DROP TRIGGER IF EXISTS Trigger_NotMore2QCM;
DELIMITER $$
CREATE TRIGGER Trigger_NotMore2QCM
BEFORE INSERT ON examenqcm FOR EACH ROW
BEGIN
    DECLARE nbExamensEnCours TINYINT;
    SET nbExamensEnCours = NbExemansEnCoursPour(NEW.NomAPP);
    IF nbExamensEnCours >= 2 THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Trop de QCMs';
    END IF;
END$$
DELIMITER ;