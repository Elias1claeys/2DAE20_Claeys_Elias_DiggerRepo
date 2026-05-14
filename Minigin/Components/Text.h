#include "Minigin/GameObject.h"

namespace dae
{
	class Font;

	class Text : public Component
	{
	private:
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		std::shared_ptr<Font> m_font{};
		std::shared_ptr<Texture2D> m_textTexture{};

	public:

		void Update() override;
		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

		Text(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255,255,255,255 });
		virtual ~Text() = default;
		Text(const Text& other) = delete;
		Text(Text&& other) = delete;
		Text& operator=(const Text& other) = delete;
		Text& operator=(Text&& other) = delete;
	};
}