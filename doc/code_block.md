代码块：

- **main函数输入：**

```c++
 using namespace std;
int main(int argc, char **argv)
{
    cout<<"argc: "<<argc<<endl;
    for(int i=0;i<=argc;++i)
    {
        cout<<i<<"  ";
        cout<<argv[i]<<"   "<<endl;        
    }
    return 0;
}
```

