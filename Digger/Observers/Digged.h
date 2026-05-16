#include "Core/GameObject.h"
#include "Event/Observer.h"


namespace dae
{
	class Dig : public Observer
	{
	private:
		GameObject* m_pDigGround{ nullptr };
	public:

		Dig(GameObject* digGround);
		virtual ~Dig() = default;
		Dig(const Dig& other) = delete;
		Dig(Dig&& other) = delete;
		Dig& operator=(const Dig& other) = delete;
		Dig& operator=(Dig&& other) = delete;

		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}