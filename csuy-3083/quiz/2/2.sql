-- 1
SELECT DISTINCT itemid FROM madewith
	WHERE ingredientid != 'CHESE';

-- 2
SELECT companyname FROM vendors
	INNER JOIN ingredients ON vendors.referredby = ingredients.vendorid
	WHERE ingredients.foodgroup = 'Milk';

-- 3
SELECT itemid, price FROM items
	WHERE itemid IN (
		SELECT itemid FROM madewith
			WHERE ingredientid IN (
				SELECT ingredientid FROM ingredients WHERE vendorid = 'VGRUS'
			)
	);

-- 4
SELECT items.itemid, items.price FROM items
	INNER JOIN madewith ON madewith.itemid = items.itemid
	INNER JOIN ingredients ON madewith.ingredientid = ingredients.ingredientid
	WHERE vendorid = 'VGRUS';

-- 5
SELECT name FROM ingredients
	WHERE vendorid != 'VGRUS';

-- 6
SELECT itemid, name FROM items
	INNER JOIN madewith ON items.itemid = madewith.itemid
	GROUP BY itemid
	WHERE COUNT(ingredientid) >= 3;

SELECT items.itemid, items.name FROM items
	INNER JOIN madewith ON items.itemid = madewith.itemid
	GROUP BY itemid
	HAVING COUNT(ingredientid) >= 3;

-- 7
SELECT vendorid, companyname FROM vendors
	WHERE vendorid NOT IN (
		SELECT referredby FROM vendors
	);

-- 8
SELECT mealid, name FROM meals
	WHERE mealid IN (
		SELECT mealid FROM partof
			INNER JOIN items on partof.itemid = items.itemid
			WHERE items.ingredientid IN (
				SELECT ingredientid FROM ingredients
					WHERE foodgroup = 'Milk'
			)
	);

SELECT mealid, name FROM meals
	WHERE mealid IN (
		SELECT mealid FROM partof
			INNER JOIN items on partof.itemid = items.itemid
			INNER JOIN madewith ON items.itemid = madewith.itemid
			WHERE madewith.ingredientid IN (
				SELECT ingredientid FROM ingredients
					WHERE foodgroup = 'Milk'
			)
	);

-- 9
SELECT ingredientid FROM ingredients
	WHERE vendorid = 'VGRUS' AND ingredientid NOT IN (
		SELECT ingredientid FROM madewith
			WHERE itemid != 'CHKSD'
	);

-- 10
SELECT items.name, COUNT(madewith.ingredientid) FROM items
	INNER JOIN madewith ON items.itemid = madewith.itemid
	GROUP BY items.itemid;
