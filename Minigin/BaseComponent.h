class GameObject;

class Component
{
private:
	GameObject* m_pOwner{};
	bool m_markedForDelete{ false };

public:

	const virtual void Render() {}
	virtual void Update() {}
	void MarkForDelete() { m_markedForDelete = true; }
	bool IsMarkedForDelete() const { return m_markedForDelete; }

	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

protected:
	explicit Component(GameObject* owner) : m_pOwner(owner) {}
	GameObject* GetOwner() const { return m_pOwner; }
};