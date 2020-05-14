#pragma once
#include "Rectangle.h"
#include <list>

namespace StlList
{
	class RectangleList
	{
	private:
		std::list<Rectangle> data_;
	public:
		RectangleList() :data_(std::list<Rectangle>()) {}
		RectangleList(const Rectangle& new_rectangle) :
			data_(std::list<Rectangle>{new_rectangle}) {}
		RectangleList& Append(const Rectangle& new_rectangle);
		Rectangle Pop(std::list<Rectangle>::size_type i);
		void Print()const;
		~RectangleList() = default;
	};
}

namespace HandMade
{
	struct RecNode
	{
		Rectangle rec;
		RecNode* next;
		RecNode* pre;
	};
	
	class RectangleList
	{
	private:
		RecNode* data_begin_;
		RecNode* data_end_;
		unsigned int size_;
	public:
		RectangleList();
		RectangleList(const Rectangle& new_rectangle);
		RectangleList(const RectangleList& rhs);
		RectangleList& operator=(const RectangleList& rhs);
		RectangleList& Append(const Rectangle& new_rectangle);
		Rectangle Pop(unsigned int i);
		void Print()const;
		int Size()const { return size_; }
		~RectangleList();
	};
}