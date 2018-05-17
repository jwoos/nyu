-- student
INSERT INTO accounts (
	id,
	class,
	email,
	password
) VALUES (
	1,
	"student",
	"student1@test.site",
	"$2b$12$Ejcx.43PI8XcLVzTQPPxBeSxUfabYiYs2dQUhupjTm6iMk6sReWBe"
), (
	2,
	"student",
	"student2@test.site",
	"$2b$12$Ejcx.43PI8XcLVzTQPPxBeSxUfabYiYs2dQUhupjTm6iMk6sReWBe"
);

-- professor
INSERT INTO accounts (
	id,
	class,
	email,
	password
) VALUES (
	3,
	"professor",
	"professor1@test.site",
	"$2b$12$SQ3hxOnjj29/RM2Ua3CsKuYMmNpzUZo0ugw/oIYPqWIx7E8HVg0BC"
), (
	4,
	"professor",
	"professor2@test.site",
	"$2b$12$SQ3hxOnjj29/RM2Ua3CsKuYMmNpzUZo0ugw/oIYPqWIx7E8HVg0BC"
);
