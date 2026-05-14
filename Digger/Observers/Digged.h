#include "GameObject.h"
#include "BaseObserver.h"


namespace dae
{
	class DigObserver : public Observer
	{
	private:
		GameObject* m_pDigGround{ nullptr };
	public:

		DigObserver(GameObject* digGround);
		virtual ~DigObserver() = default;
		DigObserver(const DigObserver& other) = delete;
		DigObserver(DigObserver&& other) = delete;
		DigObserver& operator=(const DigObserver& other) = delete;
		DigObserver& operator=(DigObserver&& other) = delete;

		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}