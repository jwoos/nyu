-- Patient Schema, MySQL Version
-- SQL:  Practical Guide for Developers
-- Michael J. Donahoo and Gregory D. Speegle
-- Copyright 2005

DROP DATABASE IF EXISTS patient;

CREATE DATABASE patient;

USE patient;

CREATE TABLE physician (
  physicianid INTEGER PRIMARY KEY,
  name CHAR(30) NOT NULL,
  salary NUMERIC(8, 2) CHECK (salary >= 0)
);

CREATE TABLE patient (
  patientid INTEGER PRIMARY KEY AUTO_INCREMENT,
  firstname VARCHAR(30),
  lastname VARCHAR(30),
  gender CHAR(1) CHECK (gender IN ('M', 'F')),
  primaryphysician INTEGER,
  birthday DATE,
  insurance INTEGER,
  FOREIGN KEY(primaryphysician) REFERENCES physician(physicianid)
);

CREATE TABLE insurance (
  cardholder INTEGER PRIMARY KEY,
  company VARCHAR(50) NOT NULL,
  copay NUMERIC(5,2) CHECK (copay >= 0),
  FOREIGN KEY(cardholder) REFERENCES patient(patientid)
);

ALTER TABLE patient ADD FOREIGN KEY (insurance) REFERENCES insurance(cardholder);

-- A patient may only visit once per day.  The visit designates a primary physician
CREATE TABLE visits (
  patientid INTEGER,
  visitdate DATE,
  physicianid INTEGER,
  PRIMARY KEY(patientid, visitdate),
  FOREIGN KEY(patientid) REFERENCES patient(patientid),
  FOREIGN KEY(physicianid) REFERENCES physician(physicianid)
);

CREATE TABLE medicalprocedure (
  procedureid CHAR(5) PRIMARY KEY,  -- ID of procedure
  name VARCHAR(30),   -- Name of procedure
  followup CHAR(5),   -- ID of follow up procedure
  risk CHAR(20) CHECK (risk IN ('Minimal', 'Moderate', 'High', 'Certain Death')),
  price NUMERIC(5,2) CHECK (price >= 0),  -- Cost for receiving procedure
  FOREIGN KEY(followup) REFERENCES medicalprocedure(procedureid)
);

-- A medical procedure may only be conducted during a patient visit, and then it may
-- only be conducted once.
CREATE TABLE conducts (
  patientid INTEGER,   -- ID of patient receiving medical procedure
  visitdate DATE,      -- Date of visit that includes this procedure
  procedureid CHAR(5), -- ID of procedure patient received
  physicianid INTEGER, -- ID of physician conducting procedure
  charge NUMERIC(5,2), -- Actual charge for procedure
  PRIMARY KEY(patientid, visitdate, procedureid),
  FOREIGN KEY(patientid, visitdate) REFERENCES visits(patientid, visitdate),
  FOREIGN KEY(physicianid) REFERENCES physician(physicianid),
  FOREIGN KEY(procedureid) REFERENCES medicalprocedure(procedureid)
);

INSERT INTO physician VALUES (1, 'Edward Scalpelhands', 100000);
INSERT INTO physician VALUES (2, 'Ann Ethesiologist', 134000);
INSERT INTO physician VALUES (3, 'Jane Doe', 123000);
INSERT INTO physician VALUES (4, 'Neal Natology', 167000);

INSERT INTO patient VALUES (1, 'Jane', 'Doe', 'F', 1, '1972-08-23', NULL);
INSERT INTO patient VALUES (2, 'Jack', 'Doe', 'M', 1, '1971-02-24', NULL);
INSERT INTO patient VALUES (3, 'Jack', 'Doe Jr.', 'M', 1, '1998-11-13', NULL);
INSERT INTO patient VALUES (4, 'Earl', 'Jackson', 'M', NULL, '1956-01-01', NULL);
INSERT INTO patient VALUES (5, 'Fred', 'Smith', 'M', 3, NULL, NULL);
INSERT INTO patient VALUES (6, 'Sara', 'Smith', 'F', 2, '1967-08-09', NULL);
INSERT INTO patient VALUES (7, 'Pat', 'Rosenberg', NULL, 3, '1970-05-17', NULL);
INSERT INTO patient VALUES (8, 'George', 'Jones', 'M', 3, '1965-11-23', NULL);
INSERT INTO patient VALUES (9, 'Melissa ', 'Franklin', 'F', 3, '1962-05-17', NULL);

INSERT INTO insurance VALUES (2, 'Nopay', 20);
INSERT INTO insurance VALUES (5, 'Till Death', 25);
INSERT INTO insurance VALUES (7, 'Exclaim Insurers', 15);
INSERT INTO insurance VALUES (9, 'Copay Surprise', NULL);

UPDATE patient SET insurance = 2 WHERE patientid IN (1, 2, 3);
UPDATE patient SET insurance = 5 WHERE patientid IN (5, 6);
UPDATE patient SET insurance = 7 WHERE patientid IN (7);
UPDATE patient SET insurance = 9 WHERE patientid IN (8, 9);

INSERT INTO visits VALUES (3, '2005-04-05', 1);
INSERT INTO visits VALUES (3, '2005-04-26', 1);
INSERT INTO visits VALUES (2, '2004-12-15', 1);
INSERT INTO visits VALUES (5, '2004-11-25', 3);
INSERT INTO visits VALUES (4, '2005-01-18', 2);
INSERT INTO visits VALUES (7, '2004-10-12', 3);
INSERT INTO visits VALUES (8, '2005-01-02', 2);

INSERT INTO medicalprocedure VALUES ('BNDAD', 'Bandage', NULL, 'Minimal', 25);
INSERT INTO medicalprocedure VALUES ('RMSTC', 'Remove Stitches', NULL, 'Moderate', 100);
INSERT INTO medicalprocedure VALUES ('STICH', 'Stitch', 'RMSTC', 'Moderate', 50);
INSERT INTO medicalprocedure VALUES ('DRUGS', 'Medicate', NULL, 'High', 15);
INSERT INTO medicalprocedure VALUES ('RDPBF', 'Reduce % Body Fat for $', NULL, 'Certain Death', NULL);

INSERT INTO conducts VALUES (3, '2005-04-05', 'STICH', 1, 45);
INSERT INTO conducts VALUES (3, '2005-04-05', 'DRUGS', 1, 12);
INSERT INTO conducts VALUES (3, '2005-04-26', 'RMSTC', 3, 60);
INSERT INTO conducts VALUES (2, '2004-12-15', 'DRUGS', 1, 10);
INSERT INTO conducts VALUES (5, '2004-11-25', 'STICH', 3, 50);
INSERT INTO conducts VALUES (4, '2005-01-18', 'RMSTC', 2, 110);
INSERT INTO conducts VALUES (7, '2004-10-12', 'DRUGS', 3, 12);
