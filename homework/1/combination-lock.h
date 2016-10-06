class CombinationLock {
	private:
		int* combination;

		bool state;
	public:
		CombinationLock(int, int, int);

		CombinationLock(int*);

		CombinationLock(const CombinationLock&) = delete;
	
		CombinationLock(CombinationLock&&) = delete;

		virtual ~CombinationLock();

		void open(int*);

		void changeCombo(int*, int*);
};
