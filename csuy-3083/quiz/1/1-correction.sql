-- 1
SELECT repfname FROM vendors
	WHERE repfname LIKE 'S%';

-- 2
SELECT name, unitprice, unit FROM ingredients
	WHERE unitprice > 0.40 OR unit = 'glass';

-- 3
SELECT name, price FROM items
	WHERE (name LIKE 'F%' OR name LIKE 'S%') AND price < 3.50;

-- 4
SELECT itemid, price FROM items
	WHERE price BETWEEN 2.50 AND 3.50;

SELECT itemid, price FROM items
	WHERE price >= 2.50 AND price <= 3.50;

-- 5
SELECT itemid, price FROM items
	WHERE price NOT BETWEEN 2.50 AND 3.50;

SELECT itemid, price FROM items
	WHERE price < 2.50 AND price > 3.50;

-- 6
SELECT vendorid, replname FROM vendors
	WHERE replname IN ('Corn', 'Sherbert');

SELECT vendorid, replname FROM vendors
	WHERE replname = 'Corn' OR replname = 'Sherbert';

-- 7
SELECT vendorid, companyname FROM vendors
	WHERE referredby IS NULL;

-- 8
SELECT ingredientid, foodgroup, inventory FROM ingredients
	WHERE foodgroup = 'Fruit' OR NOT inventory <= 200;

-- 9
SELECT DISTINCT foodgroup, vendorid FROM ingredients;

-- 10
SELECT itemid, price FROM items
	WHERE EXTRACT(YEAR FROM dateadded) >= 2001
	ORDER BY price DESC;
