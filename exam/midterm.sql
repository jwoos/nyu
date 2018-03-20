-- 1
SELECT name, inventory FROM ingredients
	WHERE inventory >= 10;

-- 2
SELECT name FROM items
	WHERE EXTRACT(YEAR FROM dateadded) >= 2001
	ORDER BY price DESC;

-- 3
SELECT COUNT(DISTINCT foodgroup) AS foodgroup_count, COUNT(*) AS ing_count FROM ingredients
	WHERE foodgroup IS NOT NULL;

-- 4
SELECT referredby, COUNT(referredby) AS refercount FROM vendors
	GROUP BY referredby
	WHERE referredby IS NOT NULL AND refercount > 1;

SELECT referredby, COUNT(referredby) AS refercount FROM vendors
	WHERE referredby IS NOT NULL
	GROUP BY referredby
	HAVING COUNT(referredby) > 1;

-- 5
SELECT storeid, MAX(item_count) FROM (
	SELECT storeid, COUNT(linenumber) AS item_count FROM orders
		GROUP BY ordernumber, storeid
		HAVING SUM(price) > 20
);

SELECT storeid, MAX(item_count) FROM (
	SELECT storeid, COUNT(linenumber) AS item_count FROM orders
		GROUP BY ordernumber, storeid
		HAVING SUM(price) > 20
) AS sub
	GROUP BY storeid;

-- 6
SELECT vendorid FROM vendors WHERE vendorid NOT IN (
	SELECT DISTINCT vendorid FROM ingredients
		WHERE vendorid IS NOT NULL
);

-- 7
SELECT ingredients.name FROM ingredients
	INNER JOIN vendors ON vendors.vendorid = ingredients.vendorid
	WHERE vendors.companyname = 'Veggies_R_Us';

-- 8
SELECT ingredients.name FROM ingredients
	INNER JOIN vendors ON vendors.vendorid = ingredients.vendorid
	WHERE vendors.companyname = 'Veggies_R_Us' AND
		ingredients.ingredientid NOT IN (
			SELECT madewith.ingredientid FROM madewith
				INNER JOIN items ON items.itemid = madewith.itemid
				WHERE items.name = 'Chicken Salad'
		);

-- 9
DELETE FROM ingredients
	WHERE vendorid IN (
		SELECT ingredients.vendorid FROM ingredients
			INNER JOIN vendors On vendors.vendorid = ingredients.vendorid
			WHERE vendors.companyname = "Don's Dairy"
	);

DELETE FROM ingredients
	WHERE vendorid IN (
		SELECT vendorid FROM vendors
			WHERE companyname = "Don's Dairy"
	);

-- 10
DELETE FROM items
	WHERE itemid NOT IN (
		SELECT items.itemid FROM items
			INNER JOIN madewith ON items.itemid = madewith.itemid
	);

DELETE FROM items
	WHERE itemid NOT IN (
		SELECT itemid FROM madewith
	);

-- 11
CREATE TABLE voters (
	id INT,
	birth_date DATE,
	first_name TINYTEXT,
	last_name TINYTEXT,

	PRIMARY KEY(id)
);

CREATE TABLE parties (
	id INT,
	name TINYTEXT,
	description TINYTEXT,

	PRIMARY KEY(id)
);

CREATE TABLE positions (
	id INT,
	name TINYTEXT,
	description TINYTEXT,

	PRIMARY KEY(id)
);

CREATE TABLE candidates (
	id INT,
	party INT,
	position INT,
	first_name TINYTEXT,
	last_name TINYTEXT,

	PRIMARY KEY(id),
	FOREIGN KEY(party) REFERENCES parties(id),
	FOREIGN KEY(position) REFERENCES positions(id)
);

CREATE TABLE polls (
	id INT,
	voter_id INT,
	candidate_id INT,
	poll_date DATE,

	PRIMARY KEY(id),
	UNIQUE(voter_id, poll_date),
	FOREIGN KEY(voter_id) REFERENCES voters(id),
	FOREIGN KEY(candidate_id) REFERENCES candidates(id)
);
