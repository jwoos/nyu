-- 1
SELECT itemid FROM items
	WHERE itemid NOT IN (
		SELECT itemid FROM madewith
			INNER JOIN ingredients ON madewith.ingredientid = ingredients.ingredientid
			WHERE ingredients.name = 'Cheese'
	);

-- 2
SELECT companyname FROM vendors
	WHERE (
		referredby IN (
			SELECT vendorid FROM vendors
				WHERE companyname = 'Veggies_R_Us'
		)
	) AND (
		vendorid IN (
			SELECT vendorid FROM ingredients
				WHERE foodgroup = 'Milk'
		)
	);

-- 3
SELECT name, price FROM items
	WHERE itemid IN (
		SELECT itemid FROM madewith
			WHERE ingredientid IN (
				SELECT ingredientid FROM ingredients
					WHERE vendorid IN (
						SELECT vendorid FROM vendors
							WHERE companyname = 'Veggies_R_Us'
					)
			)
	);

-- 4
SELECT DISTINCT items.name, items.price FROM items
	INNER JOIN madewith ON madewith.itemid = items.itemid
	INNER JOIN ingredients ON madewith.ingredientid = ingredients.ingredientid
	INNER JOIN vendors ON vendors.vendorid = ingredients.vendorid
	WHERE vendors.vendorid = 'VGRUS';

-- 5
SELECT name FROM ingredients
	WHERE vendorid NOT IN (
		SELECT vendorid FROM vendors
			WHERE companyname = 'Veggies_R_Us'
	);

-- 6
SELECT items.itemid, items.name FROM items
	INNER JOIN madewith ON items.itemid = madewith.itemid
	GROUP BY itemid
	HAVING COUNT(ingredientid) >= 3;

-- 7
SELECT vendorid, companyname FROM vendors as v1
	WHERE NOT EXISTS (
		SELECT * FROM vendors AS v2
			WHERE v2.referredby = v1.vendorid
	);

-- 8
SELECT mealid, name FROM meals AS m
	WHERE EXISTS (
		SELECT * FROM partof AS p
			INNER JOIN items ON items.itemid = p.itemid
			INNER JOIN madewith ON items.itemid = madewith.itemid
			INNER JOIN ingredients ON ingredients.ingredientid = madewith.ingredientid
			WHERE foodgroup = 'Milk' AND m.mealid = p.mealid
	);

-- 9
SELECT ingredientid FROM ingredients AS i
	INNER JOIN vendors AS v ON i.vendorid = v.vendorid
	WHERE v.companyname = 'Veggies_R_Us' AND i.ingredientid NOT IN (
		SELECT ingredientid FROM items as it
			INNER JOIN madewith AS m ON it.itemid = m.itemid
			WHERE it.name = 'Chicken Salad'
	);

-- 10
SELECT items.name, COUNT(madewith.ingredientid) FROM items
	LEFT OUTER JOIN madewith ON items.itemid = madewith.itemid
	GROUP BY items.itemid;
