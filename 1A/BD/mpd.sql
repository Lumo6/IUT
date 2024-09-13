DROP EVENT IF EXISTS CloturerNoteQuestionnaire;
DROP EVENT IF EXISTS CloturerQuestionnaire;
DROP FUNCTION IF EXISTS SuccesQuestionnaire;
DROP FUNCTION IF EXISTS NoteQuestionnaire;
DROP FUNCTION IF EXISTS SuccesQuestionnaire;
DROP PROCEDURE IF EXISTS Avancement;
DROP FUNCTION IF EXISTS PrctTermine;
DROP TRIGGER IF EXISTS TRIGGER_POSTS_APP_OR_FOR;
DROP TABLE IF EXISTS appartenirclasses;
DROP TABLE IF EXISTS repondre;
DROP TABLE IF EXISTS composer;
DROP TABLE IF EXISTS quest_apps;
DROP TABLE IF EXISTS reponses;
DROP TABLE IF EXISTS questions;
DROP TABLE IF EXISTS questionnaires;
DROP TABLE IF EXISTS posts;
DROP TABLE IF EXISTS threads;
DROP TABLE IF EXISTS formateurs;
DROP TABLE IF EXISTS apprenants;
DROP TABLE IF EXISTS classes;
DROP TABLE IF EXISTS domaines;

-- Création tables
CREATE TABLE DOMAINES (
    ID_DOMAINE INT,
    NOM VARCHAR(20) NOT NULL,
    CONSTRAINT Pk_id_domaine PRIMARY KEY(ID_DOMAINE)
);

CREATE TABLE CLASSES (
    id_classe INT,
    titre VARCHAR(20) NOT NULL,
    descrip TEXT NOT NULL,
    CONSTRAINT Pk_id_classe PRIMARY KEY (id_classe)
);
CREATE TABLE APPRENANTS (
    idApp INT,
    nomApp VARCHAR(55) NOT NULL,
    noteApp INT DEFAULT NULL,
    NoteConn INT DEFAULT NULL,
    CONSTRAINT PK_App PRIMARY KEY (idApp)
);

CREATE TABLE FORMATEURS (
    idFor INT,
    nomFor VARCHAR(55) NOT NULL,
    CONSTRAINT PK_App PRIMARY KEY (idFor)
);

CREATE TABLE THREADS (
    id_threads INT,
    date_crea DATE NOT NULL,
    nb_posts INT DEFAULT 1,
    nb_consult INT DEFAULT 0,
    domaine INT NOT NULL,
    CONSTRAINT Pk_id_threads PRIMARY KEY (id_threads),
    CONSTRAINT Fk_threads_domaine FOREIGN KEY (domaine) REFERENCES DOMAINES(id_domaine) 
);
    
CREATE TABLE POSTS (
    ID_POST INT,
    DATE_POST DATE NOT NULL,
    TITRE_POST VARCHAR(20) NOT NULL,
    TEXTE TEXT NOT NULL,
    THREADS INT,
    id_app INT,
    id_for INT,
    CONSTRAINT PK_ID_POST PRIMARY KEY (ID_POST),
    CONSTRAINT FK_posts_THREADS FOREIGN KEY (THREADS) REFERENCES THREADS(id_threads) ON UPDATE CASCADE,
    CONSTRAINT Fk_posts_ID_APP FOREIGN KEY (id_app) REFERENCES APPRENANTS(idApp) ON UPDATE CASCADE,
    CONSTRAINT Fk_posts_ID_FOR FOREIGN KEY (id_for) REFERENCES FORMATEURS(idFor) ON UPDATE CASCADE
    /*CONSTRAINT CHECK_app_for CHECK ((id_app IS NOT NULL AND id_for IS NULL) OR (id_app IS NULL AND id_for IS NOT NULL)) A Faire dans un trigger*/
);

CREATE TABLE QUESTIONNAIRES (
    ID_Q INT,
    NOM_Q VARCHAR(55) NOT NULL,
    DATE_Q DATE NOT NULL,
    DUREE_JOURS_Q INT DEFAULT NULL,
    DUREE_MINUTES_Q INT DEFAULT NULL,
    FORMATEUR INT,
    CONSTRAINT P_QUESTIONNAIRESK_Q PRIMARY KEY (ID_Q),
    CONSTRAINT Fk_QUESTIONNAIRES_id_formateur FOREIGN KEY (FORMATEUR) REFERENCES FORMATEURS(idFor) ON UPDATE CASCADE
);

CREATE TABLE QUESTIONS (
    id_question INT,
    question TEXT NOT NULL,
    domaine INT,
    formateur INT,
    CONSTRAINT PK_QUESTIONS_ID_QUESTION PRIMARY KEY (id_question),
    CONSTRAINT Fk_QUESTIONS_id_domaine FOREIGN KEY (domaine) REFERENCES DOMAINES(id_domaine) ON UPDATE CASCADE,
    CONSTRAINT Fk_QUESTIONS_id_formateur FOREIGN KEY (FORMATEUR) REFERENCES FORMATEURS(idFor) ON UPDATE CASCADE
);

CREATE TABLE REPONSES (
    idRep INT, 
    textRep TEXT NOT NULL,
    bonneRep INT NOT NULL,
    question INT,
    CONSTRAINT PK_idRep PRIMARY KEY (IDREP),
    CONSTRAINT Fk_question FOREIGN KEY (question) REFERENCES QUESTIONS(ID_QUESTION) ON UPDATE CASCADE
);

CREATE TABLE QUEST_APPS (
    id_Q_app INT,
    appreciation TEXT NOT NULL,
    noteAppQ INT NOT NULL,
    date_debut DATE NOT NULL,
    Termine BOOLEAN DEFAULT 0 NOT NULL CHECK (Termine IN (0,1)),
    id_questionnaire INT,
    id_app INT,
    CONSTRAINT PK_QUEST_APPS_id_Q_app PRIMARY KEY (id_Q_app),
    CONSTRAINT FK_QUEST_APPS_id_questionnaire FOREIGN KEY (id_questionnaire) REFERENCES QUESTIONNAIRES(id_Q) ON UPDATE CASCADE,
    CONSTRAINT FK_QUEST_APPS_ID_APP42 FOREIGN KEY (ID_APP) REFERENCES APPRENANTS(idApp) ON UPDATE CASCADE
);

CREATE TABLE COMPOSER (
    id_question INT,
    id_questionnaire INT,

    CONSTRAINT PK_Composer_ID_QUESTION_QUESTIONNAIRE PRIMARY KEY (ID_QUESTION, ID_QUESTIONNAIRE),
    CONSTRAINT Fk_Composer_ID_QUESTION FOREIGN KEY (ID_QUESTION) REFERENCES QUESTIONS(id_question) ON UPDATE CASCADE,
    CONSTRAINT FK_Composer_ID_QUESTIONNAIRE FOREIGN KEY (ID_QUESTIONNAIRE) REFERENCES QUESTIONNAIRES(ID_Q) ON UPDATE CASCADE
);

CREATE TABLE REPONDRE (
    ID_QUESTIONNAIRE INT,
    ID_APP INT,
    ID_QUESTION_APP INT,
    ID_REP INT,
    CONSTRAINT Pk_REPONDRE_ID_REP PRIMARY KEY (ID_QUESTIONNAIRE,ID_APP,ID_QUESTION_APP,ID_REP),
    CONSTRAINT FK_REPONDRE_ID_QUESTIONNAIRE FOREIGN KEY (ID_QUESTIONNAIRE) REFERENCES QUESTIONNAIRES(ID_Q) ON UPDATE CASCADE,
    CONSTRAINT FK_REPONDRE_ID_APP FOREIGN KEY (ID_APP) REFERENCES APPRENANTS(idApp) ON UPDATE CASCADE,
    CONSTRAINT FK_REPONDRE_ID_QUESTION_APP FOREIGN KEY (ID_QUESTION_APP) REFERENCES QUEST_APPS(id_Q_app) ON UPDATE CASCADE,
    CONSTRAINT FK_REPONDRE_ID_REP FOREIGN KEY (ID_REP) REFERENCES REPONSES(idRep) ON UPDATE CASCADE
);

CREATE TABLE APPARTENIRCLASSES (
    id_Class INT,
    idApp INT,    
    CONSTRAINT PK_AppartenirClass_idClass_AC PRIMARY KEY (id_Class,idApp),
    CONSTRAINT FK_AppartenirClass_idClass_Class FOREIGN KEY (id_Class) REFERENCES CLASSES(id_classe),
    CONSTRAINT FK_AppartenirClass_idApp_App FOREIGN KEY (idApp) REFERENCES APPRENANTS(idApp)
);

-- Création fonctions
DELIMITER $$
CREATE FUNCTION PrctTermine(id_Q_app INT)
RETURNS FLOAT 
BEGIN
    DECLARE Pourc FLOAT; 
    DECLARE REP INT;
    DECLARE TOTAL INT;
    SET REP = (SELECT COUNT(DISTINCT ID_QUESTION_APP) FROM Repondre
                NATURAL JOIN QUEST_APPS
                INNER JOIN REPONSES ON idRep = id_rep
                WHERE ID_QUESTION_APP = id_Q_app);
    SET TOTAL = (SELECT COUNT(DISTINCT id_question) FROM Composer
                INNER JOIN QUESTIONNAIRES ON ID_Q = ID_QUESTIONNAIRE
                INNER JOIN QUEST_APPS ON id_questionnaire = id_Q
                WHERE ID_QUESTION_APP = id_Q_app);
    
    IF TOTAL > 0 THEN
        SET Pourc = (REP / TOTAL) * 100; 
    ELSE
        SET Pourc = 0; 
    END IF;
    RETURN Pourc;
END $$
DELIMITER ;



-- penser à mettre les DECLARE au DEBUT PUTAIN NATH --

DELIMITER $$
CREATE PROCEDURE Avancement (IN IdQuest INT, OUT NbQuestionsRestantes INT, OUT TempsRestant TIME)
BEGIN

    DECLARE DateQ DATETIME;
    DECLARE TempsEcoule TIME;
   
    SELECT COUNT(DISTINCT id_question) INTO NbQuestionsRestantes
    FROM Composer
    INNER JOIN QUESTIONNAIRES ON ID_Q = ID_QUESTIONNAIRE
    LEFT JOIN Repondre ON id_question = ID_QUESTION_APP
    WHERE ID_Q = IdQuest AND id_rep IS NULL;

    SELECT Duree_Q INTO TempsRestant
    FROM QUESTIONNAIRES
    WHERE ID_Q = IdQuest; 
    
    SELECT Date_Q INTO DateQ
    FROM QUESTIONNAIRES
    WHERE ID_Q = IdQuest;
    
    SET TempsEcoule = TIMEDIFF(CURRENT_TIMESTAMP(), DateQ);
    
    SET TempsRestant = TIMEDIFF(TempsRestant, TempsEcoule);
   
END $$
DELIMITER ;

DELIMITER $$
CREATE FUNCTION SuccesQuestionnaire(IdQuest INT)
RETURNS INT
BEGIN
    DECLARE NB INT;
    SET NB = (SELECT COUNT(DISTINCT ID_APP) FROM REPONDRE);
    RETURN NB;
END $$
DELIMITER ;


DELIMITER $$
CREATE FUNCTION NoteQuestionnaire(ID_Q_APP_Select INT)
RETURNS INT
BEGIN
    DECLARE Note INT;
    SET Note = (SELECT noteAppQ FROM QUEST_APPS 
    WHERE ID_Q_APP = ID_Q_APP_Select);
    RETURN Note;
END $$
DELIMITER ;

DELIMITER $$
CREATE OR REPLACE PROCEDURE CalculNotesApp (IN idApp INT,OUT NoteConn INT, OUT noteApp INT)
BEGIN
    DECLARE SNoteConn INT;
    DECLARE SNoteApp INT;
    DECLARE NBNoteApp INT;
    DECLARE NBNoteConn INT;
    SET SNoteConn = (SELECT SUM(noteAppQ) FROM QUEST_APPS INNER JOIN QUESTIONNAIRES ON id_Q = ID_QUESTIONNAIRE WHERE DUREE_Q <> 240);
    SET SNoteApp = (SELECT SUM(noteAppQ) FROM QUEST_APPS INNER JOIN QUESTIONNAIRES ON id_Q = ID_QUESTIONNAIRE WHERE DUREE_Q = 240);
    SET NBNoteApp = (SELECT COUNT(noteAppQ) FROM QUEST_APPS INNER JOIN QUESTIONNAIRES ON id_Q = ID_QUESTIONNAIRE WHERE DUREE_Q <> 240);
    SET NBNoteConn = (SELECT COUNT(noteAppQ) FROM QUEST_APPS INNER JOIN QUESTIONNAIRES ON id_Q = ID_QUESTIONNAIRE WHERE DUREE_Q = 240);
    SET NoteConn = SNoteConn / NBNoteConn;
    SET noteApp = SNoteConn / NBNoteApp;
END $$
DELIMITER ;

DELIMITER $$
CREATE EVENT CloturerQuestionnaire
    ON SCHEDULE AT CURRENT_TIMESTAMP + INTERVAL  1 HOUR
    DO
    BEGIN
        UPDATE QUEST_APPS AS qa
        JOIN QUESTIONNAIRES AS quest ON quest.ID_Q = qa.id_questionnaire
        SET qa.Termine =  1
        WHERE CURRENT_DATE() >= DATE_ADD(qa.date_debut, INTERVAL quest.DUREE_MINUTES_Q MINUTE);
    END $$
DELIMITER ;


 --- ca marche pu
 
DELIMITER $$ 
CREATE EVENT CloturerNoteQuestionnaire
    ON SCHEDULE EVERY 1 HOUR 
    DO
        IF termine = 1 THEN
            SELECT CalculNotesApp();
END $$
DELIMITER;


























DROP TRIGGER IF EXISTS VerifierInsertionReponse;
DELIMITER $$
CREATE TRIGGER VerifierInsertionReponse
BEFORE INSERT ON REPONSES
FOR EACH ROW
BEGIN
    DECLARE id_Q_app_check INT;
    DECLARE Termine_check INT;
    DECLARE pourc FLOAT;

    SET id_Q_app_check = (SELECT id_questionnaire FROM QUEST_APPS WHERE id_Q_app = NEW.question);

    IF id_Q_app_check IS NOT NULL THEN 
        SELECT Termine INTO Termine_check FROM QUEST_APPS WHERE id_Q_app = id_Q_app_check;
        IF Termine_check = 0 THEN
            SET Pourc = PrctTermine(id_Q_app_check);
            IF Pourc = 100 THEN
                UPDATE QUEST_APPS SET Termine = 1 WHERE id_Q_app = id_Q_app_check;
                IF (SELECT DUREE_JOURS_Q FROM QUESTIONNAIRES WHERE id_Q_app_check = id_questionnaire) <> 30 THEN
                    CALL NoteQuestionnaire(id_Q_app_check);
                END IF;
            END IF;
        END IF;
    END IF;

END$$
DELIMITER ;



-- Nath la galère, mais V2 cette fois ci --

--help? obviously marche pas
CREATE OR REPLACE FUNCTION VerifierMiseAJourReponse()
DELIMITER $$    DECLARE questionnaire_type VARCHAR(50)
    DECLARE questionnaire_termine BOOLEAN
    DECLARE date_actuelle TIMESTAMP
    DECLARE questionnaire_id INT
    
BEGIN
    SELECT IdQuestApp, termine INTO id_Q
    FROM Questionnaire
    WHERE IdQuestApp = NEW.IdQuestApp

    IF questionnaire_id IS NULL THEN
        RAISE EXCEPTION 'Non fait par apprenant'
    END IF

    IF DUREE_JOURS_Q IS NULL AND DUREE_MINUTES_Q IS NULL THEN
        RAISE EXCEPTION 'Examen: modifications impossibles'
    END IF

    IF termine = 1 THEN 
        RAISE EXCEPTION 'Questionnaire terminé'
    END IF

    SELECT NOW() INTO date_actuelle
    IF NEW.DateFin < date_actuelle THEN
        UPDATE Questionnaire
        SET termine = 1
        WHERE IdQuestApp = NEW.IdQuestApp
    END IF
    INSERT INTO Notes (IdQuestApp, Note)
    VALUES (NEW.IdQuestApp, NoteQuestionnaire(NEW.IdQuestApp))
  RETURN 1
END $$
DELIMITER ;

CREATE TRIGGER VerifierMiseAJourReponseTrigger
BEFORE INSERT ON Repondre
FOR EACH ROW
EXECUTE FUNCTION VerifierMiseAJourReponse();


-- Ne pas regarder car nul

DELIMITER $$ 
CREATE TRIGGER TRIGGER_POSTS_APP_OR_FOR
    BEFORE INSERT ON POSTS
    FOR EACH ROW
    BEGIN
        IF (NEW.id_app IS NOT NULL AND NEW.id_for IS NOT NULL) THEN
            SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Il est impossible que le post soit créé par un apprenant et un formateur ! Soit l\'un soit l\'autre mais pas les deux !';
        END IF;
    END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS PROCEDURE_DUREE_QUESTIONNAIRE;
DELIMITER //
CREATE PROCEDURE PROCEDURE_DUREE_QUESTIONNAIRE()
BEGIN
    DECLARE date_questionnaire DATE;
    SELECT DATE_Q INTO date_questionnaire FROM Questionnaires;
    IF CURRENT_DATE() < date_questionnaire THEN
        SIGNAL SQLSTATE '45000';
    END IF;
END//
DELIMITER ;

CREATE PROCEDURE PROCEDURE_FERMETURE_QUESTIONNAIRE()
BEGIN
    UPDATE QUEST_APPS
    SET TERMINE = 1 
    JOIN REPONDRE AS REP ON REP.ID_QUESTION_APP = QUEST_APPS.ID_Q_APP 
    JOIN QUESTIONNAIRES AS Q ON Q.ID_Q = REP.ID_QUESTIONNAIRE
    WHERE (DATE_DEB + Q.DATE_Q) >= CURRENT_DATE();

    UPDATE QUEST_APPS
    SET TERMINE = 1 
    WHERE PRCTTERMINE(ID_Q_APP) = 100;

END $$
DELIMITER;


-- vues 
DROP VIEW IF EXISTS VueStatsApprenant;

CREATE VIEW VueStatsApprenant AS 
SELECT 
    apprenants.idApp,
    COUNT(CASE WHEN quest_apps.Termine = TRUE THEN quest_apps.id_Q_app END) AS nb_questionnaires_realises,
    COUNT(CASE WHEN quest_apps.Termine = FALSE THEN quest_apps.id_Q_app END) AS nb_questionnaires_en_cours,
    (COUNT(CASE WHEN reponses.bonneRep = TRUE THEN reponses.idRep END) / COUNT(repondre.ID_REP)) * 100 AS pourcentage_bonnes_reponses,
    AVG(quest_apps.noteAppQ) AS note_moyenne
FROM 
    apprenants
LEFT JOIN 
    quest_apps ON apprenants.idApp = quest_apps.id_app
LEFT JOIN 
    repondre ON apprenants.idApp = repondre.ID_APP
LEFT JOIN 
    reponses ON repondre.ID_REP = reponses.idRep
GROUP BY 
    apprenants.idApp;


DROP VIEW IF EXISTS
    VueStatsQuestionnaire;
CREATE VIEW VueStatsQuestionnaire AS SELECT
    questionnaires.ID_Q,
    questionnaires.NOM_Q,
    CASE
        WHEN questionnaires.DUREE_Q = 0 THEN "QCM" 
        ELSE "Examen"
    END AS "Type de questionnaire",
    COUNT(CASE WHEN quest_apps.Termine = 1 THEN 1 END AS "Apprenant ayant terminé"),
    COUNT (CASE WHEN quest_apps.Termine = 1 THEN 2  END AS "Apprenant en cours")

    
JOIN quest_apps ON questionnaires.ID_Q = quest_apps.id_Q_app
JOIN apprenants ON quest_apps.id_app = apprenants.idApp
GROUP BY
    questionnaires.ID_Q,
    






/*Donner les threads qui sont vieux de plus d'un mois avec un nombre nombre de consultation inférieur à 10 pour pouvoir les supprimées */

SELECT 