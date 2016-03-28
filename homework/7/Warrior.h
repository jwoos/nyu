#include <string>

namespace WarriorCraft {
	class Noble;

	class Warrior {
		public:
			Warrior(const std::string& name, int strength);

			std::string getName() const;

			int getStrength() const;

			void setStrength(int newStrength);

			void runaway();

			void setNoble(Noble* noblePointer);

			Noble* getNoble() const;
		private:
			std::string name;
			int strength;
			Noble* noble;
	};
};
