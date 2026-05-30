namespace dae
{
	class Bag;

	class BagState
	{
	public:
		explicit BagState(Bag* bag): m_pBag(bag) {}
		virtual ~BagState() = default;
		BagState(const BagState& other) = delete;
		BagState(BagState&& other) = delete;
		BagState& operator=(const BagState& other) = delete;
		BagState& operator=(BagState&& other) = delete;

		virtual std::unique_ptr<BagState> Update(float deltaTime) = 0;

	protected:
		Bag* m_pBag;
	};
}