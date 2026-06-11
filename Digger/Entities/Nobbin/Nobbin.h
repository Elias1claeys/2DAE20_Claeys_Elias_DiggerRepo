#include "Core/GameObject.h"

namespace dae
{
	class Nobbin : public Component
	{
	public:
		Nobbin(GameObject* owner);
		virtual ~Nobbin() = default;
		Nobbin(const Nobbin& other) = delete;
		Nobbin(Nobbin&& other) = delete;
		Nobbin& operator=(const Nobbin& other) = delete;
		Nobbin& operator=(Nobbin&& other) = delete;

		void Update() override;

	private:

		float m_Time{ 0 };
		int m_TextureAct{ 0 };
	};
}