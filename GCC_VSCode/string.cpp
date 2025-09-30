#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

namespace Pxind
{
    class string
    {
        public:
            typedef char* iterator;
            typedef const char* const_iterator;
            static const size_t npos = -1;

            iterator begin()
            {
                return _str;
            }

            iterator end()
            {
                return _str + _size;
            }

            //默认构造函数
            string(char* str = "")
            :_size(strlen(str))
            ,_capacity(_size+1)
            {
                _str = new char[_capacity];
                memcpy(_str,str,_capacity);
            }

            //拷贝构造函数
            string(const string& s)
            {
                _size = s._size;
                _capacity = s._capacity;
                _str = new char[_capacity];
                strcpy(_str,s._str);
            }

            //获取string大小
            size_t size() const
            {
                return _size;
            }

            //获取string容量
            size_t capacity() const
            {
                return _capacity;
            }

            char& operator[](size_t i)
            {
                assert(i<_size);

                return _str[i];
            }

            string& push_back(char str)
            {
                if(_size == _capacity)
                {
                    _capacity *= 2;
                    char* newstr = new char[_capacity];
                    strcpy(newstr,_str);
                    delete[] _str;
                    _str = nullptr;
                    _str = newstr;
                }
                _str[_size++] = str;
                _str[_size] = '\0';

                return *this;
            }

            string& append(char* pstr)
            {
                if(_size+strlen(pstr)>_capacity)
                {
                    _capacity = _size+strlen(pstr)+1;
                    char* newstr = new char[_capacity];
                    strcpy(newstr,_str);
                    delete[] _str;
                    _str = nullptr;
                    _str = newstr;
                }

                strcpy(_str+_size,pstr);
                _size+=strlen(pstr);
                return *this;
            }

            string& insert(size_t pos,char* pstr)
            {}

            void resize(size_t n,char ch)
            {}

            string& erase(size_t pos,size_t len = npos)
            {}

            string& insert(size_t pos,char ch)
            {
                pos--;
                if(_size == _capacity)
                {
                    _capacity *= 2;
                    char* newstr = new char[_capacity];
                    strcpy(newstr,_str);
                    delete[] _str;
                    _str = nullptr;
                    _str = newstr;
                }
                assert(pos<_size);
                char* _newstr;
                _newstr = new char[_size - pos + 1];

                strcpy(_newstr,_str+pos);
                _str[pos] = ch;
                strcpy(_str+pos+1,_newstr);
                _size++;

                delete[] _newstr;
                _newstr = nullptr;

                return *this;
            }

            size_t find(char ch,size_t pos=0)
            {
                size_t retPos = 0;
                
                auto it = this->begin()+pos;
                while(it!=this->end())
                {
                    if(*it==ch)
                    {
                        return retPos;
                    }
                    it++;
                    retPos++;
                }
                
                return npos;
            }

            size_t find(char* pstr,size_t pos = 0)
            {
                size_t retPos = pos;
                int str_size = strlen(pstr);
                auto it = this->begin()+pos;
                //两层循环
                while(it!=this->end())
                {
                    if(*it==*pstr)
                    {
                        int i =1;
                        while(--str_size)
                        {
                            if(*(pstr+i)!=*(it+i))
                                break;
                            i++;
                        }
                        if(str_size==0)
                            return retPos;
                        str_size = strlen(pstr);
                    }
                    it++;
                    retPos++;
                }
                return npos;
            }

            char* substr(size_t beginPos,int lenth)
            {
                char* retStr = new char[lenth+1];
                int i = 0;
                while(i!=lenth)
                {
                    retStr[i] = _str[beginPos+i];
                    i++;
                }
                retStr[lenth] = '\0';

                return retStr;
            }

            bool operator<(string& s)
            {

            }

            friend ostream& operator<<(ostream& out, const string& s)
            {
                for(size_t i = 0; i < s._size; i++)
                {
                    out << s._str[i];
                }
                return out;
            }

            friend istream& operator>>(istream& in, string& s) 
            {
                char buf[1024] = {0};
                in >> buf;
                s._size = strlen(buf);
                if(s._size >= s._capacity)
                {
                    delete[] s._str;
                    s._capacity = s._size + 1;
                    s._str = new char[s._capacity];
                }
                strcpy(s._str, buf);

                return in;
            }

            const char* c_str()
            {
                return _str;
            }

            //析构函数
            ~string()
            {
                delete[] _str;
                _str = nullptr;
                _size = _capacity = 0;
            }

        private:
            char* _str;
            size_t _size;
            size_t _capacity;
    };
}

using namespace Pxind;
void test1()
{
    Pxind::string s2("ello ");
    s2.append("worl");
    s2.push_back('d');
    s2.insert(1,'h');

    cout<<s2.substr(s2.find("llo"),3)<<endl;
}

int main()
{
    test1();
    return 0;
}
