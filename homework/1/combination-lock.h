class CombinationLock {
	private:
		int* combination;

		bool state;
	public:
		CombinationLock(int* combinationArr);

		CombinationLock(const CombinationLock& original);

		virtual ~CombinationLock();

		void open(int* combination);

		void changeCombo(int* combinationArr, int* newCombination);
};
