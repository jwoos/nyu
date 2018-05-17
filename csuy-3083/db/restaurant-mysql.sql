-- Restaurant Schema, MySQL version
-- SQL:  Practical Guide for Developers
-- Michael J. Donahoo and Gregory D. Speegle
-- Copyright 2005

DROP DATABASE IF EXISTS restaurant;

CREATE DATABASE restaurant;

USE restaurant;

CREATE TABLE items (
  itemid CHAR(5) PRIMARY KEY, 
  name VARCHAR(30),
  price NUMERIC(5,2),
  -- MySQL DEFAULTs must be constants so DEFAULT CURRENT_DATE is illegal
  dateadded DATE
);

CREATE TABLE vendors (
  vendorid CHAR(5) NOT NULL,
  companyname VARCHAR(30) DEFAULT 'SECRET' NOT NULL,
  repfname VARCHAR(20) DEFAULT 'Mr. or Ms.',
  replname VARCHAR(20),
  referredby CHAR(5) NULL,
  UNIQUE (repfname, replname),
  PRIMARY KEY(vendorid),
  -- MySQL constraints cannot be deferred
  FOREIGN KEY(referredby) REFERENCES vendors(vendorid)
);

CREATE TABLE ingredients (
  ingredientid CHAR(5) PRIMARY KEY,
  name VARCHAR(30) NOT NULL,
  unit CHAR(10),
  unitprice NUMERIC(5,2),
  foodgroup CHAR(15) CHECK (foodgroup IN ('Milk', 'Meat', 'Bread', 
                                          'Fruit', 'Vegetable')),
  inventory INTEGER DEFAULT 0,
  vendorid CHAR(5),
  CHECK (unitprice * inventory <= 4000),
  -- MySQL constraints cannot be deferred
  FOREIGN KEY(vendorid) REFERENCES vendors(vendorid)
);

CREATE TABLE madewith (
  -- MySQL constraints cannot be deferred
  itemid CHAR(5) REFERENCES items(itemid),
  -- MySQL constraints cannot be deferred
  ingredientid CHAR(5) REFERENCES ingredients,
  quantity INTEGER DEFAULT 0 NOT NULL,
  PRIMARY KEY(itemid, ingredientid)
);

CREATE TABLE meals (
  mealid CHAR(5) NOT NULL,
  name CHAR(20) UNIQUE,
  PRIMARY KEY(mealid)
);

CREATE TABLE partof (
  mealid CHAR(5),
  itemid CHAR(5),
  quantity INTEGER,
  discount DECIMAL (2, 2) DEFAULT 0.00,
  PRIMARY KEY(mealid, itemid),
  FOREIGN KEY(mealid) REFERENCES meals(mealid),
  -- MySQL constraints cannot be deferred
  FOREIGN KEY(itemid) REFERENCES items(itemid)
);

CREATE TABLE ads (
  slogan VARCHAR(50)
);

CREATE VIEW menuitems AS
-- MySQL cannot CAST to NUMERIC(5,2)
(SELECT m.mealid AS menuitemid, m.name, SUM(price * (1 - discount)) AS price
 FROM meals m LEFT OUTER JOIN partof p ON m.mealid = p.mealid
              LEFT OUTER JOIN items i ON p.itemid = i.itemid
 GROUP BY m.mealid, m.name)
UNION
(SELECT itemid, name, price
 FROM items);

CREATE TABLE stores (
   storeid CHAR(5) NOT NULL,
   address VARCHAR(30),
   city VARCHAR(20),
   state CHAR(2),
   zip CHAR(10),
   manager VARCHAR(30),
   PRIMARY KEY(storeid)
);

CREATE TABLE orders (
   ordernumber INTEGER NOT NULL,
   linenumber INTEGER NOT NULL,
   storeid CHAR(5) NOT NULL,
   menuitemid CHAR(5),
   price NUMERIC(5,2),
   time TIMESTAMP,
   PRIMARY KEY(storeid, ordernumber, linenumber),
   FOREIGN KEY(storeid) REFERENCES stores(storeid)
);

INSERT INTO items VALUES ('CHKSD', 'Chicken Salad', 2.85, '1998-11-13');
INSERT INTO items VALUES ('FRTSD', 'Fruit Salad', 3.45, '2000-5-6');
INSERT INTO items VALUES ('GDNSD', 'Garden Salad', 0.99, '2001-3-2');
INSERT INTO items VALUES ('MILSD', 'Millennium Salad', NULL, '2002-8-16');
INSERT INTO items VALUES ('SODA', 'Soda', 0.99, '2003-2-6');
INSERT INTO items VALUES ('WATER', 'Water', 0, '2002-5-19');
INSERT INTO items VALUES ('FRPLT', 'Fruit Plate', 3.99, '2000-9-2');

INSERT INTO vendors VALUES ('VGRUS', 'Veggies_R_Us', 'Candy', 'Corn', NULL);
INSERT INTO vendors VALUES ('DNDRY', 'Don''s Dairy', 'Marla', 'Milker', 'VGRUS');
INSERT INTO vendors VALUES ('FLVCR', 'Flavorful Creams', 'Sherman', 'Sherbert', 'VGRUS');
INSERT INTO vendors VALUES ('FRTFR', '"Fruit Eating" Friends', 'Gilbert', 'Grape', 'FLVCR');
INSERT INTO vendors VALUES ('EDDRS', 'Ed''s Dressings', 'Sam', 'Sauce', 'FRTFR');
INSERT INTO vendors VALUES ('SPWTR', 'Spring Water Supply', 'Gus', 'Hing', 'EDDRS');

INSERT INTO ingredients VALUES ('CHESE', 'Cheese', 'scoop', 0.03, 'Milk', 150, 'DNDRY');
INSERT INTO ingredients VALUES ('CHIKN', 'Chicken', 'strip', 0.45, 'Meat', 120, 'DNDRY');
INSERT INTO ingredients VALUES ('CRUTN', 'Crouton', 'piece', 0.01, 'Bread', 400, 'EDDRS');
INSERT INTO ingredients VALUES ('GRAPE', 'Grape', 'piece', 0.01, 'Fruit', 300, 'FRTFR');
INSERT INTO ingredients VALUES ('LETUS', 'Lettuce', 'bowl', 0.01, 'Vegetable', 200, 'VGRUS');
INSERT INTO ingredients VALUES ('PICKL', 'Pickle', 'slice', 0.04, 'Vegetable', 800, 'VGRUS');
INSERT INTO ingredients VALUES ('SCTDR', 'Secret Dressing', 'ounce', 0.03, NULL, 120, NULL);
INSERT INTO ingredients VALUES ('TOMTO', 'Tomato', 'slice', 0.03, 'Fruit', 15, 'VGRUS');
INSERT INTO ingredients VALUES ('WATER', 'Water', 'glass', 0.06, NULL, NULL, 'SPWTR');
INSERT INTO ingredients VALUES ('SODA', 'Soda', 'glass', 0.69, NULL, 5000, 'SPWTR');
INSERT INTO ingredients VALUES ('WTRML', 'Watermelon', 'piece', 0.02, 'Fruit', NULL, 'FRTFR');
INSERT INTO ingredients VALUES ('ORNG', 'Orange', 'slice', 0.05, 'Fruit', 10, 'FRTFR');

INSERT INTO madewith VALUES ('CHKSD', 'CHESE', 2);
INSERT INTO madewith VALUES ('CHKSD', 'CHIKN', 4);
INSERT INTO madewith VALUES ('CHKSD', 'LETUS', 1);
INSERT INTO madewith VALUES ('CHKSD', 'SCTDR', 1);
INSERT INTO madewith VALUES ('FRTSD', 'GRAPE', 10);
INSERT INTO madewith VALUES ('FRTSD', 'WTRML', 5);
INSERT INTO madewith VALUES ('GDNSD', 'LETUS', 4);
INSERT INTO madewith VALUES ('GDNSD', 'TOMTO', 8);
INSERT INTO madewith VALUES ('FRPLT', 'WTRML', 10);
INSERT INTO madewith VALUES ('FRPLT', 'GRAPE', 10);
INSERT INTO madewith VALUES ('FRPLT', 'CHESE', 10);
INSERT INTO madewith VALUES ('FRPLT', 'CRUTN', 10);
INSERT INTO madewith VALUES ('FRPLT', 'TOMTO', 8);
INSERT INTO madewith VALUES ('WATER', 'WATER', 1);
INSERT INTO madewith VALUES ('SODA', 'SODA', 1);
INSERT INTO madewith VALUES ('FRPLT', 'ORNG', 10);

INSERT INTO meals VALUES ('CKSDS', 'Chicken N Suds');
INSERT INTO meals VALUES ('VGNET', 'Vegan Eatin''');

INSERT INTO partof VALUES ('CKSDS', 'CHKSD', 1, 0.02);
INSERT INTO partof VALUES ('CKSDS', 'SODA', 1, 0.10);
INSERT INTO partof VALUES ('VGNET', 'GDNSD', 1, 0.03);
INSERT INTO partof VALUES ('VGNET', 'FRTSD', 1, 0.01);
INSERT INTO partof VALUES ('VGNET', 'WATER', 1, 0.00);

INSERT INTO ads VALUES ('Grazing in style');
INSERT INTO ads VALUES (NULL);
INSERT INTO ads VALUES ('Bovine friendly and heart smart');
INSERT INTO ads VALUES ('Where the grazin''s good');
INSERT INTO ads VALUES ('The grass is greener here');
INSERT INTO ads VALUES ('Welcome to the "other side"');

INSERT INTO stores VALUES ('FIRST','1111 Main St.','Waco','TX','76798','Jeff Donahoo');
INSERT INTO stores VALUES ('#2STR','2222 2nd Ave.','Waco','TX','76798-7356','Greg Speegle');
INSERT INTO stores VALUES ('NDSTR','3333 3rd St.','Fargo','ND','58106','Jeff Speegle');
INSERT INTO stores VALUES ('CASTR','4444 4th Blvd','San Francsico','CA','94101-4150','Greg Donahoo');
INSERT INTO stores VALUES ('NWSTR',null,null,'TX',null,'Man Ager');

INSERT INTO orders VALUES (1,1,'FIRST','FRTSD',3.45,'2005-01-26 13:46:04.188');
INSERT INTO orders VALUES (1,2,'FIRST','WATER',0.0,'2005-01-26 13:46:19.188');
INSERT INTO orders VALUES (1,3,'FIRST','WATER',0.0,'2005-01-26 13:46:34.188');
INSERT INTO orders VALUES (2,1,'FIRST','CHKSD',2.85,'2005-01-26 13:47:49.188');
INSERT INTO orders VALUES (3,1,'FIRST','SODA ',0.99,'2005-01-26 13:49:04.188');
INSERT INTO orders VALUES (3,2,'FIRST','FRPLT',3.99,'2005-01-26 13:49:19.188');
INSERT INTO orders VALUES (3,3,'FIRST','VGNET',4.38,'2005-01-26 13:49:34.188');
INSERT INTO orders VALUES (1,1,'#2STR','CKSDS',3.68,'2005-01-26 14:02:04.188');
INSERT INTO orders VALUES (1,2,'#2STR','CHKSD',2.85,'2005-01-26 14:02:19.188');
INSERT INTO orders VALUES (1,3,'#2STR','SODA ',0.99,'2005-01-26 14:02:34.188');
INSERT INTO orders VALUES (1,4,'#2STR','GDNSD',0.99,'2005-01-26 14:02:49.188');
INSERT INTO orders VALUES (2,1,'#2STR','CHKSD',2.85,'2005-01-26 14:04:04.188');
INSERT INTO orders VALUES (2,2,'#2STR','SODA ',0.99,'2005-01-26 14:04:19.188');
INSERT INTO orders VALUES (3,1,'#2STR','CHKSD',2.85,'2005-01-26 14:05:34.188');
INSERT INTO orders VALUES (3,2,'#2STR','FRPLT',3.99,'2005-01-26 14:05:49.188');
INSERT INTO orders VALUES (3,3,'#2STR','GDNSD',0.99,'2005-01-26 14:06:04.188');
INSERT INTO orders VALUES (1,1,'NDSTR','WATER',0.0,'2005-01-26 14:14:04.188');
INSERT INTO orders VALUES (1,2,'NDSTR','FRPLT',3.99,'2005-01-26 14:14:19.188');
INSERT INTO orders VALUES (2,1,'NDSTR','GDNSD',0.99,'2005-01-26 14:15:34.188');
INSERT INTO orders VALUES (3,1,'NDSTR','VGNET',4.38,'2005-01-26 14:16:49.188');
INSERT INTO orders VALUES (3,2,'NDSTR','FRPLT',3.99,'2005-01-26 14:17:04.188');
INSERT INTO orders VALUES (3,3,'NDSTR','FRTSD',3.45,'2005-01-26 14:17:19.188');
INSERT INTO orders VALUES (3,4,'NDSTR','SODA ',0.99,'2005-01-26 14:17:34.188');
INSERT INTO orders VALUES (1,1,'CASTR','CHKSD',2.85,'2005-01-26 14:22:04.188');
INSERT INTO orders VALUES (1,2,'CASTR','GDNSD',0.99,'2005-01-26 14:22:19.188');
INSERT INTO orders VALUES (2,1,'CASTR','SODA ',0.99,'2005-01-26 14:23:34.188');
INSERT INTO orders VALUES (2,2,'CASTR','FRTSD',3.45,'2005-01-26 14:23:49.188');
INSERT INTO orders VALUES (2,3,'CASTR','SODA ',0.99,'2005-01-26 14:24:04.188');
INSERT INTO orders VALUES (2,4,'CASTR','VGNET',4.38,'2005-01-26 14:24:19.188');
INSERT INTO orders VALUES (3,1,'CASTR','VGNET',4.38,'2005-01-26 14:25:34.188');
INSERT INTO orders VALUES (3,2,'CASTR','FRPLT',3.99,'2005-01-26 14:25:49.188');
INSERT INTO orders VALUES (3,3,'CASTR','FRTSD',3.45,'2005-01-26 14:26:04.188');
INSERT INTO orders VALUES (3,4,'CASTR','WATER',0.0,'2005-01-26 14:26:19.188');
INSERT INTO orders VALUES (3,5,'CASTR','CHKSD',2.85,'2005-01-26 14:26:34.188');
