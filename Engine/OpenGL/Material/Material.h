#pragma once

namespace StarEngine
{
	class Material
	{
	public:

		Material();

		virtual ~Material();

	public:

		inline std::string const& GetName() const { return _Name; }

	public:

		inline VOID SetName(std::string const& Name) { _Name = Name; }

	private:

		std::string _Name = "";
	};
}