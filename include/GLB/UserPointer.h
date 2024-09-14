#pragma once

#include <string>
#include <unordered_map>

#include "Export.h"
#include "Debug.h"

namespace glb {

	class GLB_API UserPointer
	{
	private:
		UserPointer() = delete;
	public:
		inline static void Set(const std::string& name, void* value);
		template <class T = void> 
		inline static T* Get(const std::string& name)
		{
			auto pointer = pointers.find(name);
			if (pointer == pointers.end())
			{
				GLBWarnH(UnknownUserPointer, "Cannot find user pointer '" << name << "'");
				return nullptr;
			}
			return (T*) pointer->second;
		}
		inline static void Delete(const std::string& name);
		inline static void DeleteAll();
		inline static bool Find(const std::string& name);

	private:
		static std::unordered_map <std::string, void*> pointers;
	};

	inline void glb::UserPointer::Set(const std::string& name, void* value)
	{
		pointers[name] = value;
	}

	inline void UserPointer::Delete(const std::string& name)
	{
		if (!Find(name))
		{
			GLBWarnL(UnknownUserPointer, "Cannot find user pointer '" << name << "'");
		}
		pointers.erase(name);
	}

	inline void UserPointer::DeleteAll()
	{
		pointers.clear();
	}

	inline bool UserPointer::Find(const std::string& name)
	{
		return pointers.find(name) != pointers.end();
	}
}