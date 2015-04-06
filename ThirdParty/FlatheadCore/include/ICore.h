namespace Flathead
{
	class ICore
	{
		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;
	};
}