namespace dae
{
	class GameObject;
	class Event;

	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void OnNotify(GameObject* gameObject, Event event) = 0;
	};
}
