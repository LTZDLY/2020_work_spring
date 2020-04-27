#include "RectangleList.h"

StlList::RectangleList& StlList::RectangleList::Append(const Rectangle& new_rectangle)
{
	std::list<Rectangle>::iterator it = data_.begin();
	while (it != data_.end() && (*it) < new_rectangle)
	{
		it++;
	}
	data_.insert(it, new_rectangle);
	return *this;
}

Rectangle StlList::RectangleList::Pop(std::list<Rectangle>::size_type i)
{
	Rectangle temp = Rectangle();
	try
	{
		if (i <= 0 || i > data_.size())
		{
			throw std::out_of_range("Invalid position!\n");
		}
		std::list<Rectangle>::iterator it = data_.begin();
		i--;
		while (i)
		{
			it++;
			i--;
		}
		temp = *it;
		data_.erase(it);
	}
	catch (std::out_of_range err)
	{
		std::cerr << err.what();
	}
	return temp;
}

void StlList::RectangleList::Print()const
{
	std::list<Rectangle>::const_iterator it = data_.cend();
	it--;
	int count = 3;
	while (count)
	{
		std::cout << 4 - count << '\n';
		it->Print();
		count--;
		if (it == data_.cbegin() && count > 0)
		{
			std::cout << "Only " << data_.size() << " rectangle" << (data_.size() == 1 ? "" : "s") << " in list.\n";
			break;
		}
		if (it != data_.cbegin())
		{
			it--;
		}
	}
	if (data_.size() >= 3)
	{
		std::cout << data_.size() << " rectangle" << (data_.size() == 1 ? "" : "s") << " in list.\n";
	}
	std::cout << '\n';
}

HandMade::RectangleList::RectangleList()
{
	data_begin_ = new RecNode();
	data_begin_->next = NULL;
	data_begin_->pre = NULL;
	data_end_ = data_begin_;
	size_ = 1;
}

HandMade::RectangleList::RectangleList(const Rectangle& new_rectangle)
{
	data_begin_ = new RecNode();
	data_begin_->next = NULL;
	data_begin_->pre = NULL;
	data_begin_->rec = new_rectangle;
	data_end_ = data_begin_;
	size_ = 1;
}

HandMade::RectangleList::RectangleList(const RectangleList& rhs)
{
	data_begin_ = new RecNode();
	RecNode* rhs_elem = rhs.data_begin_;
	data_begin_->rec = rhs_elem->rec;
	data_end_ = data_begin_;
	size_ = 1;
	rhs_elem = rhs_elem->next;
	while (rhs_elem != NULL)
	{
		Append(rhs_elem->rec);
		rhs_elem = rhs_elem->next;
	}
}

HandMade::RectangleList& HandMade::RectangleList::operator=(const RectangleList& rhs)
{
	//拷贝右侧对象内容，防止自赋值
	RectangleList rhs_temp(rhs);
	//释放左侧对象动态分配的内存
	RecNode* crt = data_begin_;
	while (crt != data_end_)
	{
		RecNode* next = crt->next;
		delete crt;
		crt = next;
	}
	size_ = 0;
	delete crt;

	data_begin_ = new RecNode();
	RecNode* rhs_elem = rhs_temp.data_begin_;
	data_begin_->rec = rhs_elem->rec;
	data_end_ = data_begin_;
	size_ = 1;
	rhs_elem = rhs_elem->next;
	while (rhs_elem != NULL)
	{
		Append(rhs_elem->rec);
		rhs_elem = rhs_elem->next;
	}
	return *this;
}

HandMade::RectangleList& HandMade::RectangleList::Append(const Rectangle& new_rectangle)
{
	RecNode* crt = data_begin_;
	while (crt != NULL && crt->rec < new_rectangle)
	{
		crt = crt->next;
	}
	if (crt == data_begin_)
	{
		RecNode* new_node = new RecNode();
		new_node->rec = new_rectangle;
		new_node->next = data_begin_;
		new_node->pre = NULL;
		data_begin_->pre = new_node;
		data_begin_ = new_node;
	}
	else if (crt == NULL)
	{
		RecNode* new_node = new RecNode();
		new_node->rec = new_rectangle;
		new_node->pre = data_end_;
		new_node->next = NULL;
		data_end_->next = new_node;
		data_end_ = new_node;
	}
	else
	{
		RecNode* new_node = new RecNode();
		new_node->rec = new_rectangle;
		new_node->pre = crt->pre;
		new_node->next = crt;
		crt->pre->next = new_node;
		crt->pre = new_node;
	}
	size_++;
	return *this;
}

Rectangle HandMade::RectangleList::Pop(unsigned int i)
{
	Rectangle temp;
	try
	{
		if (i <= 0 || i > size_)
		{
			throw std::out_of_range("Invalid position!\n");
		}
		RecNode* crt = data_begin_;
		i--;
		while (i)
		{
			crt = crt->next;
			i--;
		}
		temp = crt->rec;
		if (crt == data_begin_)
		{
			data_begin_ = crt->next;
			data_begin_->pre = NULL;
		}
		else if (crt == data_end_)
		{
			data_end_ = crt->pre;
			data_end_->next = NULL;
		}
		else
		{
			crt->pre->next = crt->next;
			crt->next->pre = crt->pre;
		}
		delete crt;
		size_--;
	}
	catch (std::out_of_range err)
	{
		std::cerr << err.what();
	}
	
	return temp;
}

void HandMade::RectangleList::Print()const
{
	RecNode* crt = data_end_;
	int count = 3;
	while (count)
	{
		std::cout << 4 - count << '\n';
		crt->rec.Print();
		count--;
		if (crt == data_begin_ && count > 0)
		{
			std::cout << "Only " << size_ << " rectangle" << (size_ == 1 ? "" : "s") << " in list.\n";
			break;
		}
		if (crt != data_begin_)
		{
			crt = crt->pre;
		}
	}
	if (size_ >= 3)
	{
		std::cout << size_ << " rectangle" << (size_ == 1 ? "" : "s") << " in list.\n";
	}
	std::cout << '\n';
}

HandMade::RectangleList::~RectangleList()
{
	RecNode* crt = data_begin_;
	while (crt != data_end_)
	{
		RecNode* next = crt->next;
		delete crt;
		crt = next;
	}
	delete crt;
}
