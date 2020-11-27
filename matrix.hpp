
#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>

using std::size_t;

namespace sjtu
{
	
	template <class T>
	class Matrix
	{
	private:
		// your private member variables here.
		int _n=0,_m=0;
		T *_element;

	public:
		Matrix() = default;

		//构造函数
		//todo: Find the meaning of "T _init = T()".
		Matrix(size_t n, size_t m, T _init = T()):_n(n),_m(m)
		{
			_element=new T [n*m];
			for(int i=0;i<n;++i)
            {
			    for(int j=0;j<m;++j)
                {
			        _element[i*m+j]=_init;
                }
            }
		}

		//类型转换......?
		//todo: Check this point.
		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T()):Matrix(sz.first,sz.second,_init)
		{
//			_element=new T [_n*_m+1];
//			for(int i=1;i<=_n;++i)
//            {
//			    for(int j=1;j<=_m;++j)
//                {
//			        _element[i*_m+j]=_init;
//                }
//            }
		}

		//拷贝构造
		Matrix(const Matrix &Mat)
		{
			_n=Mat._n;
			_m=Mat._m;
			_element=new T [_n*_m+1];
			for(int i=0;i<_n;i++)
            {
			    for(int j=0;j<_m;j++)
                {
			        _element[j+i*_m]=Mat._element[j+i*_m];
                }
            }
		}
		
		template <class U>
		Matrix(const Matrix<U> &Mat)
		{
			
		}
		
		Matrix &operator = (const Matrix &Mat)
		{
			
		}
		
		template <class U>
		Matrix &operator=(const Matrix<U> &Mat)
		{
			
		}

		//移动构造，接管参数的空间.
		Matrix(Matrix &&Mat) noexcept
		{
			_n=Mat._n;
			_m=Mat._m;
			_element=Mat._element;
			Mat._element=nullptr;
		}
		
		Matrix &operator=(Matrix &&Mat) noexcept
		{
			
		}

		//析构函数.
		~Matrix() { delete [] _element; }
		
		Matrix(std::initializer_list<std::initializer_list<T>> il)
		{
			
		}
		
	public:
		size_t rowLength() const { return _n; }
		
		size_t columnLength() const { return _m; }
		
		void resize(size_t n, size_t m, T _init = T())
		{
			
		}
		
		void resize(std::pair<size_t, size_t> sz, T _init = T())
		{
			
		}
		
		std::pair<size_t, size_t> size() const
		{
			return {_n,_m};
		};

		//回收.
		void clear()
		{
			for(int i=0;i<_n;++i)
            {
			    for(int j=0;j<_m;++j)
                {
			        _element[i*_m+j]=0;
                }
            }
			delete [] _element;
			_n=0;
			_m=0;
		}
		
	public:
		const T &operator()(size_t i, size_t j) const
		{
			
		}
		
		T &operator()(size_t i, size_t j)
		{
			
		}
		
		Matrix<T> row(size_t i) const
		{
			
		}
		
		Matrix<T> column(size_t i) const
		{
			
		}
		
		
	public:
	    // ==重载.
		template <class U>
		bool operator == (const Matrix<U> &Mat) const
		{
			if(Mat._n!=_n || Mat._m!=_m) return false;
			for(int i=0;i<_n;i++)
            {
			    for(int j=0;j<_m;j++)
                {
			        if(Mat._element[j+i*_m]!=_element[j+i*_m])  return false;
                }
            }
			return true;
		}

		// !=重载.
		template <class U>
		bool operator != (const Matrix<U> &Mat) const
		{
			return !(Mat == *this);
		}

		//取反.
		//todo: If the class isn't the integer.
		Matrix operator - () const
		{
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    _element[j+i*_m]=-_element[j+i*_m];
                }
            }
		}

		template <class U>
		Matrix &operator += (const Matrix<U> &Mat)
		{
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    _element[j+i*_m]+=Mat._element[j+i*_m];
                }
            }
		}
		
		template <class U>
		Matrix &operator -= (const Matrix<U> &Mat)
		{
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    _element[j+i*_m]-=Mat._element[j+i*_m];
                }
            }
		}
		
		template <class U>
		Matrix &operator *= (const U &k)
		{
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    _element[j+i*_m]*=k;
                }
            }
		}
		
		Matrix tran() const
		{

		}
		
	public: // iterator
		class iterator
		{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type        = T;
			using pointer           = T *;
			using reference         = T &;
			using size_type         = size_t;
			using difference_type   = std::ptrdiff_t;
			
			iterator() = default;
			
			iterator(const iterator &) = default;
			
			iterator &operator=(const iterator &) = default;
			
		private:

			
		public:
			difference_type operator-(const iterator &Mat)
			{
				
			}
			
			iterator &operator+=(difference_type offset)
			{
				
			}
			
			iterator operator+(difference_type offset) const
			{
				
			}
			
			iterator &operator-=(difference_type offset)
			{
				
			}
			
			iterator operator-(difference_type offset) const
			{
				
			}
			
			iterator &operator++()
			{
				
			}
			
			iterator operator++(int)
			{
				
			}
			
			iterator &operator--()
			{
				
			}
			
			iterator operator--(int)
			{
				
			}
			
			reference operator*() const
			{
				
			}
			
			pointer operator->() const
			{
				
			}
			
			bool operator==(const iterator &Mat) const
			{
				
			}
			
			bool operator!=(const iterator &Mat) const
			{
				
			}
		};
		
		iterator begin()
		{
			
		}
		
		iterator end()
		{
			
		}
		
		std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r)
		{
			
        }
	};
		
}

//
namespace sjtu
{
	template <class T, class U>
	auto operator * (const Matrix<T> &mat, const U &x)
	{
		
	}
	
	template <class T, class U>
	auto operator * (const U &x, const Matrix<T> &mat)
	{
		
	}
	
	template <class U, class V>
	auto operator * (const Matrix<U> &a, const Matrix<V> &b)
	{
		
	}
	
	template <class U, class V>
	auto operator + (const Matrix<U> &a, const Matrix<V> &b)
	{
		
	}
	
	template <class U, class V>
	auto operator - (const Matrix<U> &a, const Matrix<V> &b)
	{
		
	}
	
}

#endif //SJTU_MATRIX_HPP

//todo: 增加鲁棒性调试.