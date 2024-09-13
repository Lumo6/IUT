    DROP TABLE IF EXISTS ACQUERIR;
    DROP TABLE IF EXISTS EQUIVALOIR;
    DROP TABLE IF EXISTS Repondre;
    DROP TABLE IF EXISTS Composer;
    DROP TABLE IF EXISTS QUEST_APP;
    DROP TABLE IF EXISTS Reponses;
    DROP TABLE IF EXISTS Questions;
    DROP TABLE IF EXISTS Questionnaires;
    DROP TABLE IF EXISTS Competences;
    DROP TABLE IF EXISTS POSTS;
    DROP TABLE IF EXISTS Threads;
    DROP TABLE IF EXISTS FORMATEURS;
    DROP TABLE IF EXISTS Apprenants;
    DROP TABLE IF EXISTS Domaines;



    CREATE TABLE Domaines (
        idDomaine		INT,
        nomDomaine		VARCHAR(20) NOT NULL,
        CONSTRAINT Pk_id_domaine PRIMARY KEY(idDomaine)
    );


    CREATE TABLE Apprenants (
        idApp INT,
        nomApp VARCHAR(55) NOT NULL,
        noteApp 		FLOAT	 DEFAULT NULL,
        NoteConn 		FLOAT DEFAULT NULL,
        CONSTRAINT PK_App PRIMARY KEY (idApp)
    );


    CREATE TABLE Formateurs (
        idFor INT,
        nomFor VARCHAR(55) NOT NULL,
        CONSTRAINT PK_App PRIMARY KEY (idFor)
    );


    CREATE TABLE Threads (
        idThread		INT,
        dateCrea 		DATE NOT NULL,
        nbPosts 		INT DEFAULT 1,
        nbConsult 		INT DEFAULT 0,
        idDomaine 		INT NOT NULL,
        CONSTRAINT Pk_id_threads 		PRIMARY KEY (idThread),
        CONSTRAINT Fk_threads_domaine 	FOREIGN KEY (idDomaine) 
    REFERENCES Domaines(idDomaine) ON UPDATE CASCADE
    );


    CREATE TABLE POSTS (
        idPost 		INT,
        datePost 		DATE 		NOT NULL,
        titrePost 		VARCHAR(20) NOT NULL,
        textePost 		TEXT 		NOT NULL,
        idThread 		INT,
        idApp 			INT,
        idFor 		INT,
        CONSTRAINT PK_ID_POST PRIMARY KEY (idPost),
        CONSTRAINT FK_posts_THREADS FOREIGN KEY (idThread) 
                    REFERENCES Threads(idThread) ON UPDATE CASCADE,
        CONSTRAINT Fk_posts_ID_APP FOREIGN KEY (idApp) 
                    REFERENCES Apprenants(idApp) ON UPDATE CASCADE,
        CONSTRAINT Fk_posts_ID_FOR FOREIGN KEY (idFor) 
                    REFERENCES Formateurs(idFor) ON UPDATE CASCADE
        /*CONSTRAINT CHECK_app_for CHECK ((idApp  IS NOT NULL AND idFor IS NULL) OR (idApp IS NULL AND idFor  IS NOT NULL)) A Faire dans un trigger*/
    );

    CREATE TABLE Competences (
        id_comp INT UNIQUE,
        nomComp VARCHAR(55) UNIQUE,
        CONSTRAINT Pk_Competences PRIMARY KEY (id_comp)
    );

    CREATE TABLE Questionnaires (
        idQuest		INT,
        nomQuest 		VARCHAR(55) NOT NULL,
        dateQuest 		DATE NOT NULL,
        dureeQuest 		TIME DEFAULT NULL,
        idFor 		INT,
        id_comp INT,
        CONSTRAINT PK_QUESTIONNAIRES PRIMARY KEY (idQuest),
        CONSTRAINT Fk_QUESTIONNAIRES_For FOREIGN KEY (idFor) REFERENCES Formateurs(idFor) ON UPDATE CASCADE,
        CONSTRAINT Fk_QUESTIONNAIRES_comp FOREIGN KEY (id_comp) REFERENCES Competences(id_comp) ON UPDATE CASCADE
    );

    CREATE TABLE Questions (
        idQuestion 	INT,
        textQuestion 	TEXT NOT NULL,
        idDomaine 		INT,
        idFor 		INT,
        CONSTRAINT PK_QUESTIONS_ID_QUESTION PRIMARY KEY (idQuestion),
        CONSTRAINT Fk_QUESTIONS_id_domaine FOREIGN KEY (idDomaine) 
                REFERENCES Domaines(idDomaine) ON UPDATE CASCADE,
        CONSTRAINT Fk_QUESTIONS_id_formateur FOREIGN KEY (idFor) 
                REFERENCES Formateurs(idFor) ON UPDATE CASCADE
    );

    CREATE TABLE Reponses (
        idRep 		INT, 
        textRep 		TEXT NOT NULL,
        bonneRep 		INT NOT NULL,
        idQuestion 	INT,
        CONSTRAINT PK_idRep PRIMARY KEY (IDREP),
        CONSTRAINT Fk_question FOREIGN KEY (idQuestion) 
                REFERENCES Questions(idQuestion) ON UPDATE CASCADE
    );

    CREATE TABLE QUEST_APP (
        idQApp 			INT,
        appreciationQApp 		TEXT NOT NULL,
        noteQApp 			INT NOT NULL,
        dateQApp 			DATETIME NOT NULL,
        Termine 			BOOLEAN DEFAULT 0 NOT NULL CHECK (Termine IN (0,1)),
        idQuest 			INT,
        id_app 			INT,
        CONSTRAINT PK_QUEST_APPS_id_Q_app PRIMARY KEY (idQApp),
        CONSTRAINT FK_QUEST_APPS_id_questionnaire FOREIGN KEY (idQuest) 
                REFERENCES Questionnaires(idQuest) ON UPDATE CASCADE,
        CONSTRAINT FK_QUEST_APPS_ID_APP42 FOREIGN KEY (ID_APP) 
                REFERENCES Apprenants(idApp) ON UPDATE CASCADE
    );

    CREATE TABLE Composer (
        idQuestion 	INT,
        idQuest 		INT,

        CONSTRAINT PK_Composer_ID_QUESTION_QUESTIONNAIRE PRIMARY KEY (idQuestion, idQuest),
        CONSTRAINT Fk_Composer_ID_QUESTION FOREIGN KEY (idQuestion) REFERENCES Questions(idQuestion) ON UPDATE CASCADE,
        CONSTRAINT FK_Composer_ID_QUESTIONNAIRE FOREIGN KEY (idQuest) REFERENCES QUESTIONNAIRES(idQuest) ON UPDATE CASCADE
    );

    CREATE TABLE REPONDRE (
        idApp 		INT,
        idQApp 		INT,
        idRep 		INT,
        CONSTRAINT Pk_REPONDRE_ID_REP PRIMARY KEY (idApp,idQApp,idRep),
        CONSTRAINT FK_REPONDRE_ID_APP FOREIGN KEY (idApp) 
                REFERENCES APPRENANTS(idApp) ON UPDATE CASCADE,
        CONSTRAINT FK_REPONDRE_ID_QUESTION_APP FOREIGN KEY (idQApp) REFERENCES QUEST_APP(idQApp) ON UPDATE CASCADE,
        CONSTRAINT FK_REPONDRE_ID_REP FOREIGN KEY (idRep) REFERENCES REPONSES(idRep) ON UPDATE CASCADE
    );


    Create TABLE EQUIVALOIR (
        id_domaine INT,
        id_comp INT,
        CONSTRAINT Pk_EQUIVALOIR PRIMARY KEY (id_domaine,id_comp),
        CONSTRAINT FK_EQUIVALOIR_domaine FOREIGN KEY (id_domaine) REFERENCES Domaines(idDomaine) ON UPDATE CASCADE,
        CONSTRAINT FK_EQUIVALOIR_comp FOREIGN KEY (id_comp) REFERENCES Competences(id_comp) ON UPDATE CASCADE
    );

    CREATE TABLE ACQUERIR (
        id_comp INT,
        id_app INT,
        notecomp INT,
        CONSTRAINT PK_ACQUERIR PRIMARY KEY (id_comp,id_app),
        CONSTRAINT FK_ACQUERIR_app FOREIGN KEY (id_app) REFERENCES Apprenants(idApp) ON UPDATE CASCADE,
        CONSTRAINT FK_ACQUERIR_comp FOREIGN KEY (id_comp) REFERENCES Competences(id_comp) ON UPDATE CASCADE
    );

    INSERT INTO Competences (id_comp, nomComp)
VALUES (1, 'C1'),
       (2, 'C2');

INSERT INTO Domaines (idDomaine, nomDomaine)
VALUES (101, 'D101'),
       (102, 'D102'),
       (103, 'D103');

INSERT INTO EQUIVALOIR (id_domaine, id_comp)
VALUES (101, 1),
       (102, 1),
       (103, 2);

INSERT INTO formateurs (idFor,nomFor)
VALUES (1,'Sauvage');

INSERT INTO Questionnaires (idQuest, nomQuest, dateQuest, idFor, id_comp)
VALUES (100, 'E100', CURRENT_DATE, 1, 1),
       (101, 'E101', CURRENT_DATE, 1, 1),
       (110, 'E110', CURRENT_DATE, 1, 2),
       (111, 'E111', CURRENT_DATE, 1, 2),
       (112, 'E112', CURRENT_DATE, 1, 2),
       (113, 'E113', CURRENT_DATE, 1, 2);

INSERT INTO Questions (idQuestion, textQuestion, idDomaine, idFor)
VALUES (100, 'Question pour D101', 101, 1),
       (101, 'Question pour D102', 102, 1),
       (102, 'Question pour D101', 101, 1),
       (103, 'Question pour D101', 101, 1),
       (110, 'Question pour D103', 103, 1),
       (111, 'Question pour D103', 103, 1),
       (112, 'Question pour D103', 103, 1);

INSERT INTO Composer (idQuestion, idQuest)
VALUES (102, 101),
       (103, 101),
       (100, 100),
       (101, 100),
       (110, 110),
       (111, 111),
       (112, 112),
       (110, 113),
       (111, 113),
       (112, 113);


DELIMITER $$
CREATE OR REPLACE PROCEDURE AffecterCompetenceApprenant (IN idApp INT, IN idComp INT)
BEGIN
    DECLARE moy INT;
    DECLARE nbnote INT;
    DECLARE notemin INT;
    
    SET moy = (SELECT AVG(noteQApp)
    FROM QUEST_APP
    WHERE id_app = idApp AND idQuest IN (SELECT idQuest FROM Questionnaires WHERE id_comp = idComp));

    SET nbnote = (SELECT COUNT(*)
    FROM QUEST_APP
    WHERE id_app = idApp AND idQuest IN (SELECT idQuest FROM Questionnaires WHERE id_comp = idComp));

    SET notemin = (SELECT MIN(noteAppQ)
    FROM QUEST_APP
    WHERE id_app = idApp AND idQuest IN (SELECT idQuest FROM Questionnaires WHERE id_comp = idComp));

    IF ((nbnote = 2 AND moy >=12) OR (nbnote = 3 AND moy >=10 AND notemin >= 8) OR (nbnote >= 4 AND moy >=10))
    THEN INSERT INTO ACQUERIR(id_comp,id_app,notecomp)
         VALUES (idcomp,idApp,moy);
   
END $$
DELIMITER ;

DELIMITER $$
CREATE OR REPLACE PROCEDURE AffecterCompetenceApprenant (IN idApp INT, In idComp INT)
BEGIN
	DECLARE moy INT;
    DECLARE nbnote INT;
    DECLARE notemin INT;
    
    SET moy = (SELECT AVG(noteAPPQ)
               FROM quest_app
               WHERE id_app = idApp AND idQuest IN (SELECT idQuest FROM questionnaires WHERE id_comp = idComp));
    
    SET nbnote = (SELECT COUNT(*)
               FROM quest_app
               WHERE id_app = idApp AND idQuest IN (SELECT idQuest FROM questionnaires WHERE id_comp = idComp));
               
    (SELECT MIN(noteAPPQ)
               FROM quest_app
               WHERE id_app = idApp AND idQuest IN (SELECT idQuest FROM questionnaires WHERE id_comp = idComp));
               
	IF((nbnote = 2 AND moy >= 12) OR (nbnote = 3 AND moy >= 10 AND notemin >= 8) OR (nbnote = 4 AND moy >= 10))
    THEN (INSERT INTO acquerir(id_comp,id_app,notecomp)
    VALUES (idcomp,idApp,moy);)
    
END $$
DELIMITER ;



SELECT MAX(SELECT AVG(notecomp) FROM acquerir GROUP BY id_app),
    MAX(SELECT COUNT(notecomp) FROM acquerir GROUP BY id_app),
    MIN(SELECT AVG(notecomp) FROM acquerir GROUP BY id_app) 
FROM acquerir


(SELECT competences.nomComp, AVG(quest_app.noteQApp) AS moy
FROM competences
JOIN questionnaires ON competences.id_comp = questionnaires.id_comp
JOIN quest_app ON questionnaires.idQuest = quest_app.idQuest
GROUP BY competences.nomComp
ORDER BY moy DESC LIMIT 1)
UNION
(SELECT competences.nomComp, COUNT(quest_app.noteQApp) AS nbnote
FROM competences
JOIN questionnaires ON competences.id_comp = questionnaires.id_comp
JOIN quest_app ON questionnaires.idQuest = quest_app.idQuest
GROUP BY competences.nomComp
ORDER BY nbnote DESC LIMIT 1)
UNION
(SELECT competences.nomComp, AVG(quest_app.noteQApp) AS moy
FROM competences
JOIN questionnaires ON c.id_comp = questionnaires.id_comp
JOIN quest_app ON questionnaires.idQuest = quest_app.idQuest
GROUP BY competences.nomComp
ORDER BY moy ASC
LIMIT 1;)
