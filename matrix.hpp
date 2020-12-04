
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

	//Friends.
    template<class U>
    friend auto operator * (const Matrix<T> &mat, const U &x);

    template<class U>
    friend auto operator * (const U &x, const Matrix<T> &mat);

    template<class U,class V>
    friend auto operator * (const Matrix<U> &a, const Matrix<V> &b);

    template <class U, class V>
    friend auto operator + (const Matrix<U> &a, const Matrix<V> &b);

    template <class U, class V>
    friend auto operator - (const Matrix<U> &a, const Matrix<V> &b);


	private:
		// your private member variables here.
		int _n=0,_m=0;
		T *element;

	public:
		Matrix() = default;

		//构造函数
		Matrix(size_t n, size_t m, T _init = T()):_n(n),_m(m)
		{
			element=new T [n*m];
			for(int i=0;i<n;++i)
            {
			    for(int j=0;j<m;++j)
                {
			        element[i*m+j]=_init;
                }
            }
		}

		//类型转换......?
		//todo: Check this point.
		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T())
		{
            Matrix(sz.first,sz.second,_init);
		}

		//拷贝构造
		Matrix(const Matrix &Mat)
		{
			_n=Mat._n;
			_m=Mat._m;
			element=new T [_n*_m+1];
			for(int i=0;i<_n;i++)
            {
			    for(int j=0;j<_m;j++)
                {
			        element[j+i*_m]=Mat.element[j+i*_m];
                }
            }
		}
		
		template <class U>
		Matrix(const Matrix<U> &Mat)
		{
            _n=Mat._n;
            _m=Mat._m;
            element=new T [_n*_m+1];
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    element[j+i*_m]=T(Mat.element[j+i*_m]);
                }
            }
		}

		//todo: Complete this.
		Matrix &operator = (const Matrix &Mat)
		{
			
		}
		
		template <class U>
		Matrix &operator = (const Matrix<U> &Mat)
		{
			
		}

		//移动构造，接管参数的空间.
		Matrix(Matrix &&Mat) noexcept
		{
			_n=Mat._n;
			_m=Mat._m;
			element=Mat.element;
			Mat.element=nullptr;
		}
		
		Matrix &operator=(Matrix &&Mat) noexcept
		{
			if(&Mat==*this) return *this;
            delete [] element;
            _n=Mat._n;
            _m=Mat._m;
            element=Mat.element;
            Mat.element=nullptr;
            return *this;
		}

		//析构函数.
		~Matrix() { delete [] element; }

		//todo: Complete this.
		Matrix(std::initializer_list<std::initializer_list<T>> il)
		{
			
		}
		
	public:
		size_t rowLength() const { return _n; }
		
		size_t columnLength() const { return _m; }

		//Resize the Matrix.
		void resize(size_t n, size_t m, T _init = T())
		{
			if(n*m<_n*_m)
            {
			    T *temp;
			    temp=new T [n*m];
			    for(int i=0;i<n*m;++i) temp[i]=element[i];
                delete [] element;
                element=temp;
                _n=n;
                _m=m;
            }
			else if(n*m==_n*_m) {_n=n; _m=m;}
			else
            {
                T *temp;
                temp=new T [n*m];
                for(int i=0;i<_n*_m;++i) temp[i]=element[i];
                for(int i=_n*_m+1;i<n*m;++i) temp[i]=_init;
                delete [] element;
                element=temp;
                _n=n;
                _m=m;
            }

		}
		
		void resize(std::pair<size_t, size_t> sz, T _init = T())
		{
			resize({sz.first,sz.second},_init);
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
			        element[i*_m+j]=0;
                }
            }
			delete [] element;
			_n=0;
			_m=0;
		}
		
	public:
		const T &operator () (size_t i, size_t j) const
		{
			return element[i*_m+j];
		}
		
		T &operator () (size_t i, size_t j)
		{
			return element[i*_m+j];
		}
		
		Matrix<T> row(size_t i) const
		{
		    Matrix<T> temp_Mat(1,_m,0);
			for(int j=0;j<_m;++j)
            {
                temp_Mat.element[j]=element[i*_m+j];
            }
			return temp_Mat;
		}
		
		Matrix<T> column(size_t i) const
		{
			Matrix<T> temp_Mat(_n,1,0);
			for(int j=0;j<_n;++j)
            {
			    temp_Mat.element[j]=element[j*_m+i];
            }
			return temp_Mat;
		}
		
		
	public:
	    // 重载==.
		template <class U>
		bool operator == (const Matrix<U> &Mat) const
		{
			if(Mat._n!=_n || Mat._m!=_m) return false;
			for(int i=0;i<_n;i++)
            {
			    for(int j=0;j<_m;j++)
                {
			        if(Mat.element[j+i*_m]!=element[j+i*_m])  return false;
                }
            }
			return true;
		}

		// 重载!=.
		template <class U>
		bool operator != (const Matrix<U> &Mat) const
		{
			return !(Mat == *this);
		}

		//取反.
		Matrix operator - () const
		{
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    element[j+i*_m]=-element[j+i*_m];
                }
            }
            return *this;
		}

		template <class U>
		Matrix &operator += (const Matrix<U> &Mat)
		{
            Matrix<decltype(element[0]+Mat.element[0])> temp(_n,_m);
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    temp.element[j+i*_m]=element[j+i*_m]+Mat.element[j+i*_m];
                }
            }
            this->clear();
            *this=temp;
            return *this;
		}
		
		template <class U>
		Matrix &operator -= (const Matrix<U> &Mat)
		{
            Matrix<decltype(element[0]-Mat.element[0])> temp(_n,_m);
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    temp.element[j+i*_m]=element[j+i*_m]-Mat.element[j+i*_m];
                }
            }
            this->clear();
            *this=temp;
            return *this;
		}
		
		template <class U>
		Matrix &operator *= (const U &k)
		{
            Matrix<decltype(element[0]*k)> temp(_n,_m);
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    temp.element[j+i*_m]=element[j+i*_m]*k;
                }
            }
            this->clear();
            *this=temp;
            return *this;
		}
		
		Matrix tran() const
		{
            Matrix<T> output;
            output._n=_m;
            output._m=_n;
            for(int i=0;i<_n;++i)
            {
                for(int j=0;j<_m;++j)
                {
                    output.element[j][i]=element[i][j];
                }
            }
            return output;
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
            pointer p;
			
		public:
			difference_type operator-(const iterator &temp)
			{
				return p-temp.p;
			}
			
			iterator &operator+=(difference_type offset)
			{
			    this->p+=offset;
			    return *this;
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
				++p;
				return *this;
			}
			
			iterator operator++(int)
			{
				auto temp=*this;
				this->p++;
				return temp;
			}
			
			iterator &operator--()
			{
				--p;
				return *this;
			}
			
			iterator operator--(int)
			{
				auto temp=*this;
				this->p--;
				return temp;
			}
			
			reference operator*() const
			{
				return *p;
			}
			
			pointer operator->() const
			{
				return p;
			}
			
			bool operator==(const iterator &temp) const
			{
			    //todo
                return true;
			}
			
			bool operator!=(const iterator &temp) const
			{
                //todo
                return true;
			}
		};
		
		iterator begin()
		{
			iterator output;
			output.p=element;
			return output;
		}
		
		iterator end()
		{
			iterator temp;
			temp.p=&element[_m*_n-1];
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
	    T temp_t;
	    U temp_u;
        Matrix<decltype(temp_t*temp_u)> temp(mat.size());
        for(int i=0;i<mat.rowLength();++i)
        {
            for(int j=0;j<mat.columnLength();++j)
            {
                temp(i,j)=mat(i,j)*x;
            }
        }
        return temp;
	}

	//todo: Try to use iterator.
	template <class T, class U>
	auto operator * (const U &x, const Matrix<T> &mat)
	{
        T temp_t;
        U temp_u;
        Matrix<decltype(temp_t*temp_u)> temp(mat.size());
		for(int i=0;i<mat.rowLength();++i)
        {
		    for(int j=0;j<mat.columnLength();++j)
            {
                temp(i,j)=mat(i,j)*x;
            }
        }
        return temp;
	}
	
	template <class U, class V>
	auto operator * (const Matrix<U> &a, const Matrix<V> &b)
	{
//	    if(a.columnLength()!=b.rowLength()) printf("[Error]\n");
        Matrix<decltype(a(0,0)*b(0,0))> temp(a.rowLength(),b.columnLength());
        for(int i=0;i<temp.rowLength();++i)
        {
            for(int j=0;j<temp.columnLength();++j)
            {
                for(int k=0;k<a.columnLength();++k)
                {
                    temp(i,k)+=a(i,k)*b(k,j);
                }
            }
        }
        return temp;
	}
	
	template <class U, class V>
	auto operator + (const Matrix<U> &a, const Matrix<V> &b)
	{
//	    if(a.size()!=b.size()) printf("[Error]\n");
        Matrix<decltype(a(0,0)+b(0,0))> temp(a.size());
        for(int i=0;i<temp.rowLength();++i)
        {
            for(int j=0;j<temp.columnLength();++j)
            {
                temp(i,j)=a(i,j)+b(i,j);
            }
        }
        return temp;
	}
	
	template <class U, class V>
	auto operator - (const Matrix<U> &a, const Matrix<V> &b)
	{
//	    if(a.size()!=b.size()) printf("[Error]\n");
        Matrix<decltype(a(0,0)-b(0,0))> temp(a.size());
        for(int i=0;i<temp.rowLength();++i)
        {
            for(int j=0;j<temp.columnLength();++j)
            {
                temp(i,j)=a(i,j)-b(i,j);
            }
        }
        return temp;
	}
	
}

#endif //SJTU_MATRIX_HPP

//todo: 增加鲁棒性调试.
//todo: Learning the usage of iterator.