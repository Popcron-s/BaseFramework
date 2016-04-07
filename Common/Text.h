#pragma once

extern "C"{
	typedef class _Text{
	private:
		char* str;
		unsigned int length;

		int LengthCompare(_Text*);
		int SizeCompare(_Text*);

	public:
		_Text();
		_Text(const char* text);
		~_Text();

		//operator const char*() const;
		operator char*() const;
		const unsigned int GetLength();

		const char* operator =(const char* text);
	
		bool operator ==(_Text& text);
		bool operator !=(_Text& text);
		bool operator < (_Text& text);
		bool operator <=(_Text& text);
		bool operator > (_Text& text);
		bool operator >=(_Text& text);

		bool operator ==(const char* text);
		bool operator !=(const char* text);
		bool operator < (const char* text);
		bool operator <=(const char* text);
		bool operator > (const char* text);
		bool operator >=(const char* text);
		// +
		char* Search(const char* text, const char type);

	}TEXT;
}
