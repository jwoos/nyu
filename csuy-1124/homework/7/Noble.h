#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft {
	class Warrior;

	class Noble {
		friend std::ostream& operator<<(std::ostream& output, const Noble& noble);
		public:
			Noble(const std::string& name);

			std::string getName() const;

			void hire(Warrior& aWarrior);

			void fire(Warrior& aWarrior);

			float getArmyStrength() const;

			void setArmyStrength(float ratio);

			void battle(Noble& enemy);

			int removeWarrior(Warrior& aWarrior);
		private:
			std::string name;
			std::vector<Warrior*> army;
	};
};
