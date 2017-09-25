#pragma once
//��visual studio��������궨�����Ӵ���������uninitialize_copy������
#define _SCL_SECURE_NO_WARNINGS

#include <memory>
#include <utility>
#include <initializer_list>

//�������ƺͱ�׼������ظ�������ʹ���Լ���namespace
namespace dsa
{
	template<typename T>
	class Vector
	{
	public:
		//����Ĭ�Ϲ���Ŀ�vector�����ǲ������ڴ�
		Vector() : elements(nullptr), firstFree(nullptr), cap(nullptr) {}
		//��T��Ĭ�Ϲ��캯����ʼ��һ����n��TԪ�ص�vector
		Vector(std::size_t n);
		//ʹ�ó�ʼ���б���ʼ��һ��vector
		Vector(const std::initializer_list<T> &li);

		//��������Ϳ�����ֵ
		Vector(const Vector<T> &v);
		Vector<T>& operator=(const Vector<T> &rhs);

		~Vector();

		T* begin() const { return elements; }
		T* end() const { return firstFree; }
		std::size_t size() const { return firstFree - elements; }
		std::size_t capacity() const { return cap - elements; }
		bool empty() const { return elements == firstFree; }

		void push_back(const T &e);
		void pop_back();

		void reserve(std::size_t);
		void resize(std::size_t);

	private:
		T *elements;
		T *firstFree;
		T *cap;

		//ʹ��allocator�������ڴ沢����vector�е�Ԫ��
		//allocator���Խ��ڴ�������������룬�Ӷ�����������Ĺ��춯�������Դ���˷�
		static std::allocator<T> alloc;

		//������������ܺ�����ʵ���ڴ�ķ����Լ�Ԫ�صĸ���
		//��Ϊ�ڿ�������ʱ��Ҫ�õ������Ա��������ظ�
		std::pair<T*, T*> allocAndCopy(const T* b, const T *e);

		//���ڸ�ֵ�������ж���Ҫ�ͷ���Դ���������ǽ��ͷ���Դ�����񽻸������Լ�����Ĺ��ܺ���
		//�Դ������������ظ�
		void free();

		void checkAndAlloc();
		void reallocate(std::size_t newCapacity);
	};
	
} //namespace dsa end

#include "Vector_inline.h"