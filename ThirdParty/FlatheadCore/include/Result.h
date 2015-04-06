#pragma once

#include "API.h"
#include "Types.h"
#include "Function.h"
#include "Object.h"

namespace Flathead
{
	class FH_API Result
	{
	public:
		Result();
		~Result();

		inline bool IsString()		
		{ 
			return Type == ResultTypes::RESString;    
		}
		inline bool IsNumber()		
		{ 
			return Type == ResultTypes::RESNumber;    
		}
		inline bool IsBool()		
		{ 
			return Type == ResultTypes::RESBool;      
		}
		inline bool IsInt()			
		{ 
			return Type == ResultTypes::RESInteger;	
		}
		inline bool IsUndefined()	
		{ 
			return Type == ResultTypes::RESUndefined; 
		}
		inline bool IsObject()		
		{ 
			return Type == ResultTypes::RESObject;	
		}
		inline bool IsFunction()	
		{ 
			return Type == ResultTypes::RESFunction;	
		}

		inline bool Successful()	
		{ 
			return Type != ResultTypes::RESFailure;   
		}

		void Set();

		void Set(int value);
		void Set(double value);
		void Set(bool value);
		void Set(char *value, int length);

		void Set(Function &value);
		void Set(Object &value);

		void Fail(char *message);

		char *StringValue;
		int IntValue;
		double NumberValue;
		bool BoolValue;

		Function *FunctionValue;

		bool Initialized;

	private:
		void SetStringValue(char *value, size_t length);

		ResultTypes Type;
		bool Success;
	};
}