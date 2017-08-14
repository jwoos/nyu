#include "text.hpp"

std::string testOnePlaintext(uint32_t index) {
	std::string text;

	switch (index) {
		case 1:
			text = "cabooses meltdowns bigmouth makework flippest neutralizers gipped mule antithetical imperials carom masochism honky retsina dullness adeste corsage saraband promenaders gestational mansuetude fig redress pregame borshts pardoner reforges refutations calendal moaning doggerel dendrology governs ribonucleic circumscriptions reassimilating machinize rebuilding mezcal fluoresced antepenults blacksmith constance furores chroniclers overlie hoers jabbing resigner quartics polishers mallow hovelling ch";
			break;

		case 2:
			text = "biorhythmic personalizing abjure greets rewashed heretic kashmir chores fiendishly combatting alliums lolly milder postpaid larry annuli codgers apostatizing scrim carillon rust grimly lignifying lycanthrope samisen founds millimeters pentagon humidification checkup hilts agonise crumbs rejected kangaroo forenoons grazable acidy duellist potent recyclability capture memorized psalmed meters decline deduced after oversolicitousness demoralizers ologist conscript cronyisms melodized girdles nonago";
			break;

		case 3:
			text = "banisters rejoices oxgall bloodstone fisticuff huguenot janitress assailed eggcup jerseyites fetas leipzig copiers pushiness fesse precociously modules navigates gaiters caldrons lisp humbly datum recite haphazardly dispassion calculability circularization intangibles impressionist jaggy ascribable overseen copses devolvement permutationists potations linesmen hematic fowler pridefully inversive malthus remainders multiplex petty hymnaries cubby donne ohioans avenues reverts glide photos antiaci";
			break;

		case 4:
			text = "deathful oxygenate cascade fashion fortifiers annelids co intimates cads expanse rusting quashing julienne hydrothermal defunctive permeation sabines hurries precalculates discourteously fooling pestles pellucid circlers hampshirites punchiest extremist cottonwood dadoes identifiers retail gyrations dusked opportunities ictus misjudge neighborly aulder larges predestinate bandstand angling billet drawbridge pantomimes propelled leaned gerontologists candying ingestive museum chlorites maryland s";
			break;

		case 5:
			text = "grovels abandons atrophying misdefines redeemed patrimonial repressions revealment recapitalizes dyspeptically invaders redounds concubine foetor lessoned rethreading derogatory orgasms mercerize exploratory coconuts retardant padlock expense lam cored lollygags mankind prologued economist scooter hefter babying acanthuses bullpens reappraisals lowercase abnormal delegated craters clodhopping heroism gunfighter disabilities coriander goring effloresced harassments damosels cryobiology brahmin ho";
			break;
	}

	return text;
}

std::map<char, std::vector<uint32_t>> getIdentifiers(uint32_t index) {
	std::map<char, std::vector<uint32_t>> m;

	switch (index) {
		case 1:
			m = {
				{'k', {30, 35, 113, 394}},
				{'q', {462}},
				{'v', {289, 432, 490}},
				{'z', {54, 346, 362}},
				{'j', {445}},
				{'b', {2, 19, 152, 212, 297, 351, 390, 447, 448}},
				{'x', {}}
			};
			break;

		case 2:
			m = {
				{'j', {28, 290}},
				{'k', {57, 263, 297}},
				{'x', {}},
				{'v', {417}},
				{'q', {}},
				{'b', {0, 27, 86, 285, 321, 354}},
				{'z', {21, 153, 319, 375, 443, 482}}
			};
			break;

		case 3:
			m = {
				{'x', {20, 426}},
				{'b', {0, 26, 187, 234, 264, 294, 296, 446, 447}},
				{'v', {154, 301, 318, 321, 391, 396, 465, 474}},
				{'q', {}},
				{'z', {103, 209, 250}},
				{'k', {}},
				{'j', {12, 56, 82, 283}}
			};
			break;

		case 4:
			m = {
				{'k', {304}},
				{'b', {144, 342, 375, 393, 404}},
				{'q', {89}},
				{'j', {98, 331}},
				{'v', {128, 470}},
				{'x', {10, 74, 245}},
				{'z', {}}
			};
			break;

		case 5:
			m = {
				{'v', {3, 74, 113}},
				{'z', {93, 193}},
				{'k', {233, 266}},
				{'j', {}},
				{'b', {9, 134, 306, 308, 325, 358, 419, 482, 490}},
				{'x', {197, 236}},
				{'q', {}}
			};
			break;
	}

	return m;
}
