
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
    template<class U,class V>
    friend auto operator * (const Matrix<U> &mat, const V &x);

    template<class U,class V>
    friend auto operator * (const U &x, const Matrix<V> &mat);

    template<class U,class V>
    friend auto operator * (const Matrix<U> &a, const Matrix<V> &b);

    template <class U, class V>
    friend auto operator + (const Matrix<U> &a, const Matrix<V> &b);

    template <class U, class V>
    friend auto operator - (const Matrix<U> &a, const Matrix<V> &b);


	private:
		// your private member variables here.
		int _n=0,_m=0;
		T *element=nullptr;

	public:
        static void throw_error()
        {
            throw std::invalid_argument("Error: Invalid input.");
        }

		Matrix() = default;

		//构造函数
		Matrix(size_t n, size_t m, T _init = T())
		{
		    _n=n;
		    _m=m;
		    if(n<0 || m<0) throw_error();
			if(n*m!=0) element=new T [n*m];
			for(int i=0;i<n;++i)
            {
			    for(int j=0;j<m;++j)
                {
			        element[i*m+j]=_init;
                }
            }
		}

		//类型转换......?
		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T())
		{
            Matrix(sz.first,sz.second,_init);
		}

		//拷贝构造
		Matrix(const Matrix &Mat)
		{
			_n=Mat._n;
			_m=Mat._m;
			if (_n*_m!=0) element=new T [_n*_m];
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
            _n=Mat.rowLength();
            _m=Mat.columnLength();
            if (_n*_m!=0) element=new T [_n*_m];
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    element[j+i*_m]=T(Mat(i,j));
                }
            }
		}

		Matrix &operator = (const Matrix &Mat)
		{
			if(&Mat==this) return *this;
            clear();
            _n=Mat._n;
            _m=Mat._m;
            if (_n*_m!=0) element=new T [_n*_m];
            for(int i=0;i<_n*_m;++i) element[i]=T(Mat.element[i]);
            return *this;
		}
		
		template <class U>
		Matrix &operator = (const Matrix<U> &Mat)
		{
			clear();
            _n=Mat.rowLength();
            _m=Mat.columnLength();
            if (_n*_m!=0) element=new T [_n*_m];
            for(int i=0;i<_n;++i)
            {
                for(int j=0;j<_m;++j) element[i*_m+j]=Mat(i,j);
            }
            return *this;
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
			if(&Mat==this) return *this;
            clear();
            _n=Mat._n;
            _m=Mat._m;
            element=Mat.element;
            Mat.element=nullptr;
            return *this;
		}

		//析构函数.
		~Matrix() { clear(); }


		Matrix(std::initializer_list<std::initializer_list<T>> il)
		{
            _n=il.size();
            _m=il.begin()->size();
            if(_n<1 || _m<1) throw_error();
            element=new T[_n*_m];
            int k=0;
            auto iti=il.begin();
            while(iti!=il.end())
            {
                auto itj=iti->begin();
                while(itj!=iti->end())
                {
                    if(iti->size()!=_m) throw_error();
                    element[k]=*itj;
                    ++itj;
                    ++k;
                }
                ++iti;
            }
		}
		
	public:
		size_t rowLength() const { return _n; }
		
		size_t columnLength() const { return _m; }

		//Resize the Matrix.
		void resize(size_t n, size_t m, T _init = T())
		{
		    if(n<1 || m<1) throw_error();
			if(n*m<_n*_m)
            {
			    T *temp;
			    temp=new T [n*m];
			    for(int i=0;i<n*m;++i) temp[i]=element[i];
                clear();
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
                clear();
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
		    if(element!=nullptr) { delete[] element; element=nullptr;}
			_n=0;
			_m=0;
		}
		
	public:
		const T &operator () (size_t i, size_t j) const
		{
		    if(i>=_n || j>=_m) throw_error();
			return element[i*_m+j];
		}
		
		T &operator () (size_t i, size_t j)
		{
            if(i>=_n || j>=_m) throw_error();
			return element[i*_m+j];
		}
		
		Matrix<T> row(size_t i) const
		{
            if(i>=_n || i<0) throw_error();
		    Matrix<T> temp_Mat(1,_m,0);
			for(int j=0;j<_m;++j)
            {
                temp_Mat.element[j]=element[i*_m+j];
            }
			return temp_Mat;
		}
		
		Matrix<T> column(size_t j) const
		{
            if(j>=_n || j<0) throw_error();
			Matrix<T> temp_Mat(_n,1,0);
			for(int i=0;i<_n;++i)
            {
			    temp_Mat.element[i]=element[i*_m+j];
            }
			return temp_Mat;
		}
		
		
	public:
	    // 重载==.
		template <class U>
		bool operator == (const Matrix<U> &Mat) const
		{
			if(Mat.rowLength()!=_n || Mat.columnLength()!=_m) return false;
			for(int i=0;i<_n;i++)
            {
			    for(int j=0;j<_m;j++)
                {
			        if(Mat(i,j)!=element[j+i*_m])  return false;
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
		    if(Mat.size()!=size()) throw_error();
            Matrix<decltype(element[0]+Mat.element[0])> temp(_n,_m);
            for(int i=0;i<_n;i++)
            {
                for(int j=0;j<_m;j++)
                {
                    temp.element[j+i*_m]=element[j+i*_m]+Mat.element[j+i*_m];
                }
            }
            clear();
            *this=temp;
            return *this;
		}
		
		template <class U>
		Matrix &operator -= (const Matrix<U> &Mat)
		{
            if(Mat.size()!=size()) throw_error();
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
            if (_n*_m!=0) output.element=new T [_n*_m];
            for(int i=0;i<_n;++i)
            {
                for(int j=0;j<_m;++j)
                {
                    output.element[j*_n+i]=element[i*_m+j];
                }
            }
            return output;
		}
		
	public: // iterator
		class iterator
		{
		//Friend.
		friend iterator Matrix::begin();
		friend iterator Matrix::end();
		friend std::pair<iterator, iterator> Matrix::subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r);

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
		    //To find the position.
            size_type pos_x=0,pos_y=0;

            //To define in which matrix.
			size_type left_=0,right_=0,up_=0,down_=0;
			Matrix *Mat;


		public:
			difference_type operator-(const iterator &temp)
			{
                if(temp.Mat!=Mat) throw_error();
                if(left_!=temp.left_ || right_!=temp.right_) throw_error();
                if(up_!=temp.up_ || down_!=temp.down_) throw_error();

                difference_type pos1=(pos_x-up_)*Mat->_m+(pos_y-left_);
                difference_type pos2;
                pos2=(temp.pos_x-temp.up_)*temp.Mat->_m+(temp.pos_y-temp.left_);
                return pos1-pos2;
			}
			
			iterator &operator+=(difference_type offset)
			{
			    pos_y+=offset;
			    while(pos_y>right_)
                {
			        pos_y-=(right_-left_+1);
			        ++pos_x;
                }
			    return *this;
			}
			
			iterator operator+(difference_type offset) const
			{
				iterator temp;
				temp=*this;
				temp+=offset;
				return temp;
			}
			
			iterator &operator-=(difference_type offset)
			{
                pos_y-=offset;
                while(pos_y<left_)
                {
                    pos_y+=(right_-left_+1);
                    --pos_x;
                }
                return *this;
			}
			
			iterator operator-(difference_type offset) const
			{
				iterator temp;
				temp=*this;
				temp-=offset;
				return temp;
			}
			
			iterator &operator++()
			{
				++pos_y;
				if(pos_y>right_) {pos_y=left_; ++pos_x;}
				return *this;
			}
			
			iterator operator++(int)
			{
				auto temp=*this;
                ++pos_y;
                if(pos_y>right_) {pos_y=left_; ++pos_x;}
				return temp;
			}
			
			iterator &operator--()
			{
				--pos_y;
				if(pos_y<left_) {pos_y=right_; --pos_x;}
				return *this;
			}
			
			iterator operator--(int)
			{
				auto temp=*this;
                --pos_y;
                if(pos_y<left_) {pos_y=right_; --pos_x;}
				return temp;
			}
			
			reference operator*() const
			{
                return Mat->element[pos_x*(right_-left_+1)+pos_y];
			}
			
			pointer operator->() const
			{
                pointer p;
                p=&Mat->element[pos_x*(right_-left_+1)+pos_y];
                return p;
			}
			
			bool operator==(const iterator &temp) const
			{
			    if(Mat!=temp.Mat) return false;
			    if(pos_x!=temp.pos_x || pos_y!=temp.pos_y) return false;
			    if(left_!=temp.left_ || right_!=temp.right_) return false;
			    if(up_!=temp.up_ || down_!=temp.down_) return false;
			    return true;
			}
			
			bool operator!=(const iterator &temp) const
			{
                return !(*this==temp);
			}
		};
		
		iterator begin()
		{
			iterator temp;
			temp.left_=0;
			temp.right_=_m;
			temp.up_=0;
			temp.down_=_n;
			temp.pos_x=0;
			temp.pos_y=0;
			temp.Mat=this;
			return temp;
		}
		
		iterator end()
		{
            iterator temp;
            temp.left_=0;
            temp.right_=_m;
            temp.up_=0;
            temp.down_=_n;
            temp.pos_x=_n-1;
            temp.pos_y=_m-1;
            temp.Mat=this;
            return temp;
		}
		
		std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r)
		{
			iterator temp1,temp2;
			temp1.left_=temp2.left_=temp1.pos_y=l.second;
			temp1.right_=temp2.right_=temp2.pos_y=r.second;
			temp1.up_=temp2.up_=temp1.pos_x=l.first;
			temp1.down_=temp2.down_=temp2.pos_x=r.first;
			temp1.Mat=temp2.Mat=this;
			return {temp1,temp2};
        }
	};
		
}

//
namespace sjtu
{
	template <class U, class V>
	auto operator * (const Matrix<U> &mat, const V &x)
	{
	    V temp_v;
	    U temp_u;
        Matrix<decltype(temp_v*temp_u)> temp(mat);

        for(int i=0;i<mat.rowLength();++i)
        {
            for(int j=0;j<mat.columnLength();++j)
            {
                temp(i,j)=mat(i,j)*x;
            }
        }
        return temp;
	}

	template <class U,class V>
	auto operator * (const U &x, const Matrix<V> &mat)
	{
        V temp_v;
        U temp_u;
        Matrix<decltype(temp_v*temp_u)> temp(mat);

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
	    if(a.columnLength()!=b.rowLength()) throw std::invalid_argument("Error: Multiplication input incorrect.");
	    U ua;
	    V vb;
        Matrix<decltype(ua*vb)> temp(a.rowLength(),b.columnLength());
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
        if(a.size()!=b.size()) throw std::invalid_argument("Error: Different size.");

        U ua;
        V vb;
        Matrix<decltype(ua+vb)> temp(a.size());

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
        if(a.size()!=b.size()) throw std::invalid_argument("Error: Different size.");
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